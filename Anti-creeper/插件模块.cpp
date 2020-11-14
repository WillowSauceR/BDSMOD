#include "../预编译头.h"
struct Vec3 {
	float x, y, z;
};
THook(explode, bool, "?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	void* _this, void* bs, /*Actor*/void* a3, const Vec3 pos, float a5, bool a6, bool a7, float a8, bool a9) {
	if (a3) {
		if (SYMCALL<int>("?getEntityTypeId@Actor@@UEBA?AW4ActorType@@XZ", a3) == 2849)
			return original(_this, bs, a3, pos, a5, a6, 0, a8, a9);
	}
	return original(_this, bs, a3, pos, a5, a6, a7, a8, a9);
}
void init() {
	std::cout << u8"[插件]防苦力怕插件已装载~" << std::endl;
}
int __stdcall DllMain(HINSTANCE__* hModule, unsigned long res, void* lpReserved) {
	if (res == 1)init();
	return 1;
}