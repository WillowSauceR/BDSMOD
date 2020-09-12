#pragma once
//-----------------------
// 结构体定义
//-----------------------
#include "bdxcore.h"
using namespace std;
// 玩家坐标结构体
struct Vec3 {
	float x,y,z;
};
struct BlockLegacy {
	string getBlockName() {
		return *(string*)((__int64)this + 112);
	}
	// 获取方块ID号
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
		return SymCall("?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ",
			BlockLegacy*, Block*)(this);
	}
};
struct BlockPos {
	int x, y, z;
};
struct BlockSource {
	Block* getBlock(BlockPos* bp) {
		return SymCall("?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z",
			Block*, BlockSource*, BlockPos*)(this, bp);
	}
};
struct Actor {
	// 获取生物名称信息
	string getNameTag() {
		return SymCall("?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			string&, Actor*)(this);
	}
	// 获取生物当前所处维度ID
	int getDimensionId() {
		int dimensionId;
		SymCall("?getDimensionId@Actor@@UEBA?AV?$AutomaticID@VDimension@@H@@XZ",
			int&, Actor*, int*)(this, &dimensionId);
		return dimensionId;
	}
	// 获取生物当前所在坐标
	Vec3* getPos() {
		return SymCall("?getPos@Actor@@UEBAAEBVVec3@@XZ",
			Vec3*, Actor*)(this);
	}

};
struct Mob : Actor {

};
struct Player : Mob {

};
struct ItemStackBase {
	VA vtable;
	VA mItem;
	VA mUserData;
	VA mBlock;
	short mAuxValue;
	char mCount;
	char mValid;
	char unk[4]{ 0 };
	VA mPickupTime;
	char mShowPickUp;
	char unk2[7]{ 0 };
	std::vector<VA*> mCanPlaceOn;
	VA mCanPlaceOnHash;
	std::vector<VA*> mCanDestroy;
	VA mCanDestroyHash;
	VA mBlockingTick;
	ItemStackBase* mChargedItem;
	VA uk;
public:
	/*VA save() {
		VA* cp = new VA[8]{ 0 };
		return SymCall(VA, MSSYM_MD5_e02d5851c93a43bfe24a4396ecb87cde, this, cp);
	}*/
#if (COMMERCIAL)
	Json::Value toJson() {
		VA t = save();
		Json::Value jv = (*(Tag**)t)->toJson();
		(*(Tag**)t)->clearAll();
		*(VA*)t = 0;
		delete (VA*)t;
		return jv;
	}
	void fromJson(Json::Value& jv) {
		VA t = Tag::fromJson(jv);
		SymCall(VA, MSSYM_B1QA7fromTagB1AA9ItemStackB2AAA2SAB1QA3AV1B1AE15AEBVCompoundTagB3AAAA1Z, this, *(VA*)t);
		(*(Tag**)t)->clearAll();
		*(VA*)t = 0;
		delete (VA*)t;
	}
	void fromTag(VA t) {
		SymCall(VA, MSSYM_B1QA7fromTagB1AA9ItemStackB2AAA2SAB1QA3AV1B1AE15AEBVCompoundTagB3AAAA1Z, this, t);
	}
#endif
	/*bool getFromId(short id, short aux, char count) {
		memcpy(this, SYM_POINT(void, MSSYM_B1QA5EMPTYB1UA4ITEMB1AA9ItemStackB2AAA32V1B1AA1B), 0x90);
		bool ret = SymCall(bool, MSSYM_B2QUA7setItemB1AE13ItemStackBaseB2AAA4IEAAB1UA2NHB1AA1Z, this, id);
		mCount = count;
		mAuxValue = aux;
		mValid = true;
		return ret;
	}*/
};
struct ItemStack : ItemStackBase {
	// 取物品ID
	short getId() {
		return SymCall("?getId@ItemStackBase@@QEBAFXZ",
			short,ItemStack*)(this);
	}
	// 取物品特殊值
	short getAuxValue() {
		return SymCall("?getAuxValue@ItemStackBase@@QEBAFXZ",
			short,ItemStack*)(this);
	}
	// 取物品名称
	std::string getName() {
		std::string str;
		SymCall("?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			__int64,ItemStack*,string*)(this, &str);
		return str;
	}
	// 取容器内数量
	int getStackSize() {			// IDA ContainerModel::networkUpdateItem
		return *((char*)this + 34);
	}
	// 判断是否空容器
	/*bool isNull() {
		return SymCall(bool,
			MSSYM_B1QA6isNullB1AE13ItemStackBaseB2AAA4QEBAB1UA3NXZ,
			this);
	}*/
};
