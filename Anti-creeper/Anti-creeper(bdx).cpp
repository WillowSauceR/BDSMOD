#include "预编译头.h"
#include "BDS内容.hpp"

THook(bool,
	"?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	void* _this, void* a2, Actor* a3, Vec3 a4, float a5, bool a6, bool a7,float a8,bool a9) {
	if (a6 != 0 || a5 != 3) { return original(_this, a2, a3, a4, a5, a6, a7,a8,a9); }
	else {
		const int id = a3->getEntityTypeId();
		if (id == 2849) {
			std::cout << u8"已拦截位于:" << a4.toString() << u8"的爆炸破坏~" << std::endl;
			return original(_this, a2, a3, a4, a5, a6, 0,a8,a9);
		}
		else {
			return original(_this, a2, a3, a4, a5, a6, a7,a8,a9);
		}
	}
}
void init() {
	std::cout<<u8"[插件]反苦力怕插件加载成功~"<<std::endl;
}

void exit() {
	// 此处填写插件卸载时的操作
}

