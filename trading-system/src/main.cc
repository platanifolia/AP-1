#include <iostream>

#include "interface.h"
// #include "calculator.h"
#include "simpledatabase.h"

// include for test, delete following later
// #include "strhandle.h"
// #include <vector>

int main()
{
	SimpleDataBase sdb;
	InterFace test(&sdb);
	test.FirstView();
	return 0;
}