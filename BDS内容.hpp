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
	__int64 gettypeid() {
		return SymCall("?getEntityTypeId@Actor@@UEBA?AW4ActorType@@XZ",
			__int64, Actor*)(this);
	}
};
struct Mob : Actor {

};
struct Player : Mob {

};