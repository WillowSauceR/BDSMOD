#pragma once
struct Vec3 {
	float x;
	float y;
	float z;
};
struct Actor {
	std::string* getname() {
		return SymCall("?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			std::string*,Actor*)(this);
	}
	int gettypeid() {
		return SymCall("?getEntityTypeId@Actor@@UEBA?AW4ActorType@@XZ",
			int, Actor*)(this);
	}
};
struct Block {

};
struct BlockSource {

};
struct BlockLegacy {};