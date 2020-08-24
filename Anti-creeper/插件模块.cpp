#include "预编译头.h"
#include "bdxcore.h"
#include "BDS内容.hpp"
using namespace std;

THook(bool,
	"?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	void* _this, BlockSource* bs, Actor* a3, const Vec3 pos, float a5, bool a6, bool a7, float a8, bool a9) {
	//cout <<a6<<endl<<a5<<endl;
	if (a6 != 0 || a5 != 3) { return original(_this, bs, a3, pos, a5, a6, a7, a8, a9); }
	else {
		const int id = a3->gettypeid();
		//cout << id << endl;
		if (id == 2849) {
			std::cout << u8"已拦截位于(" << (int)pos.x << "," << (int)pos.y << "," << (int)pos.z << ")" << u8"的爆炸破坏~" << std::endl;
			return original(_this, bs, a3, pos, a5, a6, 0, a8, a9);
		}
		else {
			return original(_this, bs, a3, pos, a5, a6, a7, a8, a9);
		}
	}
}
void init() {
	std::cout<<u8"[插件]防苦力怕插件已装载~"<<std::endl;
}

void exit() {
	// 此处填写插件卸载时的操作
}

