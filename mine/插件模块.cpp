#include "../Ԥ����ͷ.h"
#include "�ṹ��.hpp"
#define ARDUINOJSON_ENABLE_STD_STREAM 1
#include "ArduinoJson.h"
#include <fstream>
#include <time.h>
using std::string;

#define cout(...) std::cout<<__VA_ARGS__<<std::endl
int weight[16];
string name[16];
int num = 0;
int len = 0;
// Һ������
SYMHOOK(solidify, char, "?solidify@LiquidBlock@@IEBA_NAEAVBlockSource@@AEBVBlockPos@@1@Z",
	void* _this, BlockSource* bs, BlockPos* bp1, BlockPos* bp2) {
	char result = original(_this, bs, bp1, bp2);
	if (result) {
		if (bs->getBlock(bp1)->getBlockLegacy()->getBlockItemID() == 4) {
			int randVal = rand() % num;
			for (int i = 0; i < len; i++) {
				if (randVal < weight[i]) {
					((bool(*)(BlockSource*, BlockPos*, Block&, int, long long))GetServerSymbol("?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z"))
						(bs, bp1, **(Block**)GetServerSymbol(("?m" + name[i] + "@VanillaBlocks@@3PEBVBlock@@EB").c_str()), 3, 0i64);
					break;
				}
				randVal -= weight[i];
			}
		}
	}
	return result;
}
void init() {
	srand((unsigned)time(0));
	StaticJsonDocument<1024> r;
	ifstream ifs("mine.json");
	if (ifs.is_open()) {
		if (deserializeJson(r, ifs)) { cout(u8"[mine] json��ʽ����!");}
		for (auto e : r.as<JsonObject>()) {
			name[len] = e.key().c_str();
			weight[len] = e.value();
			num += weight[len];
			len++;
		}
		for (int i = 0; i < len; i++)
			cout("[mine]" << name[i] << u8"���ɸ���Ϊ" << (double)weight[i] * 100 / (double)num << '%');
		cout(u8"[mine]ˢ����������~");
	}
	else {
		cout(u8"[mine]bad file mine.json");
	}
	ifs.close();
}
int __stdcall DllMain(HINSTANCE__* hModule, unsigned long res, void* lpReserved) {
	if (res == 1)init();
	return 1;
}