#pragma once
using namespace std;

struct BlockSource {};
struct Block {};
struct BlockLegacy{};
struct BlockPos {
	int x, y, z;
	//string pos(){return "(" + to_string(x) + "," + to_string(y) + "," + to_string(z) + ")";}
};
