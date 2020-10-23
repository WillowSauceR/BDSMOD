#pragma once
using namespace std;

struct BlockLegacy {
	string getBlockName() {
		return *(string*)((__int64)this + 112);
	}
	// ªÒ»°∑ΩøÈID∫≈
	auto getBlockItemID() const {			// IDA VanillaItems::initCreativeItemsCallback Item::beginCreativeGroup "itemGroup.name.planks"
		short v3 = *(short*)((VA)this + 268);
		if (v3 < 0x100) {
			return v3;
		}
		return (short)(255 - v3);
	}

};
struct Block {
	BlockLegacy* getBlockLegacy() {
		return SYMCALL<BlockLegacy*>( "?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ",
			this);
	}
};
struct BlockPos {
	int x, y, z;
};
struct BlockSource {
	Block* getBlock(BlockPos* bp) {
		return SYMCALL<Block*>("?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z",
			this, bp);
	}
};