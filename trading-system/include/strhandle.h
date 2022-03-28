#ifndef STRHANDLE_H_
#define STRHANDLE_H_

#include<string>
#include<vector>

void StringSplit(const std::string& s, std::vector<std::string>& tokens, const std::string& delimiters = " ");

// Y-M-D H:M:S
std::string TimeType1();
// Y-M-D
std::string TimeType2();

std::string Array2Expr(const std::vector<double>& array);
#endif // STRHANDLE_H_