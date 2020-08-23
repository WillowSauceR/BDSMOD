#include "预编译头.h"
#include "BDS内容.hpp"
#include "bdxcore.h"
#include "JSON/CJsonObject.hpp"
#include <fstream>
#include <streambuf>
#pragma warning(disable:4996)
using namespace std;

//声明
//neb::CJsonObject block;
int weight[16];
string name[16];
int num = 0;
int len;

//选择方块
Block& selectblock(string name) {
	name = "?m" + name + "@VanillaBlocks@@3PEBVBlock@@EB";
	char* sym = new char[name.length() + 1];
	strcpy_s(sym, name.length() + 1, name.c_str());
	return **(Block**)SYM(sym);
}
THook(char, "?solidify@LiquidBlock@@IEBA_NAEAVBlockSource@@AEBVBlockPos@@1@Z",
	void* _this, BlockSource* bs, BlockPos* bp1, BlockPos* bp2) {
	char result = original(_this, bs, bp1, bp2);
	if (result) {
		Block* block = SymCall("?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z",
			Block*, BlockSource*, BlockPos*)(bs, bp1);
		BlockLegacy* blockleg = SymCall("?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ",
			BlockLegacy*, Block*)(block);
		string blockname = *(string*)((__int64)blockleg + 112);
		if (blockname == "minecraft:cobblestone" ) {
			int randVal = rand() % num;
			for (int i = 0; i < len; i++)
			{
				if (randVal < weight[i])
				{
					SymCall("?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z",
						bool, BlockSource*, BlockPos*, Block&, int, __int64*)(bs, bp1, selectblock(name[i]), 3, 0i64);
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
	std::ifstream file("mine.json");
	std::string e((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	neb::CJsonObject je(e);
	len = je["block"].GetArraySize();
	if (len != je["weight"].GetArraySize())
		cout << u8"[mine]数组长度不一致!" << endl;
	for (int i = 0; i < len; i++) {
		je["block"].Get(i, name[i]);
	}
	for (int i = 0; i < len; i++) {
		je["weight"].Get(i, weight[i]);
		num += weight[i];
	}
	for (int i = 0; i < len; i++) {
		cout << "[mine]" << name[i] << u8"生成概率为" << (double)weight[i] * 100 / (double)num << '%' << endl;
	}
	cout << je.ToFormattedString() << endl;
	cout << u8"[插件]刷矿机加载完成~" << endl;
}