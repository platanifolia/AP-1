#include <iostream>

#include "interface.h"
#include "simpledatabase.h"
// #include "utfwidth.h"
// include for test, delete following later
// #include "strhandle.h"
// #include <vector>
// #include "calculator.h"

#ifdef _WIN32
extern "C" __declspec(dllimport) int __stdcall SetConsoleOutputCP(unsigned wCodePageID);
#endif

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(65001);
#endif
	// std::string str("测试abcｶｷｸｹｺ");
	// std::cout << std::right << setw_u8(20, str) << str << std::endl;
	SimpleDataBase sdb;
	InterFace test(&sdb);
	test.FirstView();
	return 0;
}