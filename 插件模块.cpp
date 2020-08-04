#include "预编译头.h"
#include "bdxcore.h"
#include "BDS内容.hpp"
#pragma comment(lib, "BDXCORE.lib")

THook(bool,
	"?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	void* _this, void* a2, Actor* a3, const Vec3 a4, float a5, bool a6, bool a7, float a8, bool a9) {
	__int64 id=a3->gettypeid();
	if (id == 2849) {
		std::cout << u8"已拦截位于(" << a4.x << "," << a4.y << "," << a4.z << ")" << u8"的爆炸破坏~" << std::endl;
		return original(_this, a2, a3, a4, a5, a6, 0, a8, a9);
	}
	else {
		return original(_this, a2, a3, a4, a5, a6, a7, a8, a9);
	}
};
void init() {
	std::cout<<u8"[插件]防苦力怕插件已装载~"<<std::endl;
}

void exit() {
	// 此处填写插件卸载时的操作
}

