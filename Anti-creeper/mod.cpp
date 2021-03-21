#include "../pch.h"
#include "mod.h"
struct Vec3 {
	float x, y, z;
}pos;
Hook(explode, bool, "?explode@Level@@UEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	void* _this, void* bs, /*Actor*/void* a3, const Vec3 pos, float a5, bool a6, bool a7, float a8, bool a9) {
	if (a3) {
		if (SYMCALL<int>("?getEntityTypeId@Actor@@UEBA?AW4ActorType@@XZ", a3) == 2849)
			std::cout << u8"[Anti-Creeprer]已拦截位于: " << pos.x << " " << pos.y << " " << pos.z << u8" 的爆炸破坏" << std::endl;
			a7 = 0;
	}
	return original(_this, bs, a3, pos, a5, a6, a7, a8, a9);
}
BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
	if (reason == 1) {
		puts(u8"[Anti-Creeprer]防苦力怕插件已装载~");
	}
	return TRUE;
}
