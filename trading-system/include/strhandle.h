#ifndef STRHANDLE_H_
#define STRHANDLE_H_

#include <string>
#include <vector>

void StringSplit(const std::string& s, std::vector< std::string >& tokens, const std::string& delimiters = " ");

// Y-M-D H:M:S
std::string TimeType1();
// Y-M-D
std::string TimeType2();
// 生成计算器计算式
std::string Array2Expr(const std::vector< double >& array);

// pring symbol num times
void PrintSymbolEqual(int num);
void PrintSymbolHorizontal(int num);
void PrintSymbolStar(int num);

void PrintUserTitle();
void PrintItemTitle();
void PrintOrderTitle();
#endif  // STRHANDLE_H_