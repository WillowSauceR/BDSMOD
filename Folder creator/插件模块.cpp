#include "预编译头.h"
#include "BDS内容.hpp"
#include <iostream>
#include <string>
#include <io.h>
#include <direct.h>
constexpr char PATH_DELIMITER = '\\';

static const VA STD_COUT_HANDLE = SYM_OBJECT(VA,
	MSSYM_B2UUA3impB2UQA4coutB1AA3stdB2AAA23VB2QDA5basicB1UA7ostreamB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB3AAAA11B1AA1A);
static void logout(std::string cmdout) {
	SYMCALL(VA, MSSYM_MD5_b5f2f0a753fc527db19ac8199ae8f740, STD_COUT_HANDLE, cmdout.c_str(), cmdout.length());
}
void cf(const std::string f) {
	std::string f_builder;
	std::string sub;
	sub.reserve(f.size());
	for (std::_String_const_iterator it = f.begin(); it != f.end(); ++it) {
		const char c = *it;
		sub.push_back(c);
		if (c == PATH_DELIMITER || it == f.end() - 1) {
			f_builder.append(sub);
			if (-1== ::_access(f_builder.c_str(), 0)) {
				if (0 != ::_mkdir(f_builder.c_str())) {
					logout(u8"[INFO] 文件夹 "+f+u8" 创建失败(一次只能创建一层文件夹)\n");
				}
				else{logout(u8"[INFO] 文件夹 "+f+u8" 创建成功\n");}
			}
			else{logout(u8"[INFO] 文件夹 "+f+u8" 已存在\n");}
			sub.clear();
		}
	}
}
/* 服务器后台指令输出*/
THook(VA,
	MSSYM_MD5_b5f2f0a753fc527db19ac8199ae8f740,
	VA handle, char* str, VA size) {
	if (handle == STD_COUT_HANDLE) {
		std::string s = str;
		int a = (int)s.find("cf ");
		std::string A = s.replace(0, 3, "");
		std::string path = A.replace(A.find("\n"), 1, "");
		if (a == 0) {
			cf(path);
			return 0;
		}
	}
	return original(handle, str, size);
};

void init() {
	std::cout << u8"[插件]文件夹创建加载成功~" << std::endl;
}

void exit() {
}