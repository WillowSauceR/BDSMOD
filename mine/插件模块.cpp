#include "Ԥ����ͷ.h"
#include "�ṹ��.hpp"
#include "json/json.h"
#include <fstream>
#include <time.h>
#pragma warning(disable:4996)
using namespace std;

int weight[16];
string name[16];
int num = 0;
int len = 0;
#define cout(...) cout<<__VA_ARGS__<<endl
// ѡ�񷽿�
inline Block& selectblock(string name) {
	return **(Block**)SYM(("?m" + name + "@VanillaBlocks@@3PEBVBlock@@EB").c_str());
}// Һ������
THook(char, "?solidify@LiquidBlock@@IEBA_NAEAVBlockSource@@AEBVBlockPos@@1@Z",
	void* _this, BlockSource* bs, BlockPos* bp1, BlockPos* bp2) {
	char result = original(_this, bs, bp1, bp2);
	if (result) {
		short bid = bs->getBlock(bp1)->getBlockLegacy()->getBlockItemID();
		if (bid == 4) {
			int randVal = rand() % num;
			for (int i = 0; i < len; i++) {
				if (randVal < weight[i]) {
					SymCall(bool, "?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z",
						BlockSource*, BlockPos*, Block&, int, __int64*)(bs, bp1, selectblock(name[i]), 3, 0i64);
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
	Json::Reader reader;
	Json::Value jv;
	// ���ļ�����
	ifstream ifs("mine.json", ios::binary);
	if (reader.parse(ifs, jv)) {
		for (auto e : jv.getMemberNames()) {
			name[len] = e;
			weight[len] = jv[e].asInt();
			num += weight[len];
			len++;
		}
		for (int i = 0; i < len; i++)
			cout("[mine]" << name[i] << u8"���ɸ���Ϊ" << (double)weight[i] * 100 / (double)num << '%');
	}
	else cout(u8"�ļ���ʧ��!");
	ifs.close();
	cout(u8"[���]ˢ����������~");
}
