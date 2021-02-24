#include "../pch.h"
#include "Json.h"
#include "BDS.hpp"
#pragma warning(disable:4996)
unordered_map<string, int> blocks;
int num = 0;
// 液体流动
Hook(solidify, char, "?solidify@LiquidBlock@@IEBA_NAEAVBlockSource@@AEBVBlockPos@@1@Z",
	VA _this, BlockSource* bs, BlockPos* bp1, BlockPos* bp2) {
	char result = original(_this, bs, bp1, bp2);
	if (result) {
		if (bs->getBlock(bp1)->getBlockLegacy()->getBlockItemID() == 4) {
			int randVal = rand() % num;
			for (auto& p : blocks) {
				if (randVal < p.second) {
					SYMCALL<bool>("?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z",
						bs, bp1, *(Block**)SYM(("?m" + p.first + "@VanillaBlocks@@3PEBVBlock@@EB").c_str()), 3, 0i64);
					break;
				}
				randVal -= p.second;
			}
		}
	}
	return result;
}
BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
	if (reason == 1) {
		srand((unsigned)time(0));
		ifstream ifs("mine.json");
		if (ifs.is_open()) {
			string str{ istreambuf_iterator<char>(ifs),istreambuf_iterator<char>() };
			Json j;
			if ((bool)j.fromString(str))
				puts(u8"[mine]Json格式错误");
			for (auto o : j.asObject()) {
				blocks[o.first] = o.second.asInt();
				num += o.second.asInt();
			}
			for (auto& p : blocks)
				printf(u8"[mine] %s 生成概率为 %f %%\n", p.first.c_str(), (double)p.second * 100 / (double)num);
		}
		else {
			puts(u8"[mine]can't find file mine.json");
			return 1;
		}
		ifs.close();
	}
	return 1;
}