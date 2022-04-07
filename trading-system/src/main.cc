#include <iostream>

#include "interface.h"
#include "simpledatabase.h"
// include for test, delete following later
// #include "strhandle.h"
// #include <vector>
// #include "calculator.h"
// #include "utfwidth.h"

#ifdef _WIN32
extern "C" __declspec(dllimport) int __stdcall SetConsoleOutputCP(unsigned wCodePageID);
#endif

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(65001);
#endif
	SimpleDataBase sdb;
	InterFace fin(&sdb);
	fin.FirstView();
	return 0;
}