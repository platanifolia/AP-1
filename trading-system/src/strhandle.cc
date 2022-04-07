#include "strhandle.h"

#include <ctime>
#include <iostream>

using std::string;
using std::vector;
using std::to_string;
using std::cout;
using std::endl;

void StringSplit(const string &s, vector<string> &tokens, const string &delimiters/* = " "*/)
{
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

string TimeType1()
{
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    string ret(tmp);
    return ret;
}

string TimeType2()
{
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&t));
    string ret(tmp);
    return ret;
}

string Array2Expr(const vector<double> &array)
{
    string ret;
    for(double i : array)
    {
        if(i >= 0)
        {
            ret += " + " + to_string(i);
        }
        else
        {
            ret += " - " + to_string(-i);
        }
    }
    if(ret[1] == '+')
        ret.erase(0, 3);
    ret = "(" + ret + ")";
    return ret;
}

void PrintSymbolEqual(int num)
{
    for(int i = 0; i < num; ++i)
    {
        cout << "=";
    }
    cout << endl;
}

void PrintSymbolHorizontal(int num)
{
    for(int i = 0; i < num; ++i)
    {
        cout << "-";
    }
    cout << endl;
}

void PrintSymbolStar(int num)
{
    for(int i = 0; i < num; ++i)
    {
        cout << "*";
    }
    cout << endl;
}