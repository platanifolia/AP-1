#include "strhandle.h"

#include <ctime>

using std::string;
using std::vector;

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