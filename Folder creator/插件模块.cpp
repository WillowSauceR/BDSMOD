#include "../预编译头.h"
#include <filesystem>
using std::string,std::cout,std::endl;
using namespace std::filesystem;
static const VA STD_COUT_HANDLE = *(VA*)GetServerSymbol("__imp_?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A");

// 命令输出
static void logout(string str) {
	SYMCALL<VA>( "??$_Insert_string@DU?$char_traits@D@std@@_K@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@0@AEAV10@QEBD_K@Z",
		STD_COUT_HANDLE, str.c_str(), str.length());
}
// 指令输出
SYMHOOK(_logout,VA, "??$_Insert_string@DU?$char_traits@D@std@@_K@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@0@AEAV10@QEBD_K@Z",
	VA handle, char* str, VA size) {
	if (handle == STD_COUT_HANDLE) {
		if (*str == '*') {
			str[strlen(str) - 1] = '\0';
			path path = str + 1;
			create_directories(path);
			return 0;
		}
	}
	return original(handle, str, size);
};
void init() {
	cout << u8"[插件]文件夹创建加载成功~" << endl;
}
int __stdcall DllMain(HINSTANCE__* hModule, unsigned long res, void* lpReserved) {
	if (res == 1)init();
	return 1;
}