#include "Ԥ����ͷ.h"
#include "bdxcore.h"
#include "BDS����.hpp"
#pragma comment(lib, "BDXCORE.lib")

THook(bool,
	"?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	void* _this, void* a2, Actor* a3, const Vec3 a4, float a5, bool a6, bool a7, float a8, bool a9) {
	__int64 id=a3->gettypeid();
	if (id == 2849) {
		std::cout << u8"������λ��(" << a4.x << "," << a4.y << "," << a4.z << ")" << u8"�ı�ը�ƻ�~" << std::endl;
		return original(_this, a2, a3, a4, a5, a6, 0, a8, a9);
	}
	else {
		return original(_this, a2, a3, a4, a5, a6, a7, a8, a9);
	}
};
void init() {
	std::cout<<u8"[���]�������²����װ��~"<<std::endl;
}

void exit() {
	// �˴���д���ж��ʱ�Ĳ���
}

