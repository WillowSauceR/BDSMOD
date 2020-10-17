#pragma once
struct Vec3 {
	float x,y,z;
};
struct Actor {
	std::string* getNameTag() {
		return SYMCALL(std::string*, "?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", this);
	}
	int getEntityTypeId() {
		return SYMCALL(int, "?getEntityTypeId@Actor@@UEBA?AW4ActorType@@XZ", this);
	}
};