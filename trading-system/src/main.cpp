#include <iostream>

#include "ui.h"
#include "calculator.h"
#include "simpledatabase.h"

// include for test, delete following later
#include "strhandle.h"
#include <vector>

int main()
{
	SimpleDataBase sdb;
	sdb.ParseSql("SELECT * FROM commodity WHERE sellerID CONTAINS U001");
	// InterFace test;
	// test.FirstView();
	// std::cout << "Hello World!" << std::endl;
	// std::vector<std::string> tokenstest;
	// std::string test = "UPDATE user SET password=123456 WHERE username=test";
	// StringSplit(test, tokenstest, " ");
	// for(std::string i:tokenstest)
	// {
	// 	std::cout << i << std::endl;
	// }
	// sdb.print("user");
	return 0;
}