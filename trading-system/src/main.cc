#include <iostream>

#include "interface.h"
#include "calculator.h"
#include "simpledatabase.h"

// include for test, delete following later
// #include "strhandle.h"
#include <vector>

int main()
{
	SimpleDataBase sdb;
	// sdb.ParseSql("SELECT * FROM commodity WHERE sellerID CONTAINS U001");
	// Evaluator test("((4 * 3 + 2) / (6.4 - 2.4) - 10) * (6.4 - 7.2) + (-2) * 4");
	// cout << test.Calculate() << endl;
	InterFace test(&sdb);
	test.FirstView();
	// sdb.ParseSql("SELECT * FROM commodity");
	return 0;
}