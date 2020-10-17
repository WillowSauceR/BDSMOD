#include "预编译头.h"
#include "结构体.hpp"
using namespace std;

THook(bool,
	"?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	void* _this, void* bs, Actor* a3, const Vec3 pos, float a5, bool a6, bool a7, float a8, bool a9) {
	//cout <<a6<<endl<<a5<<endl;
	if (a6 != 0 || a5 != 3)return original(_this, bs, a3, pos, a5, a6, a7, a8, a9);
	else {
		const int id = a3->getEntityTypeId();
		//cout << id << endl;
		if (id == 2849) {
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

