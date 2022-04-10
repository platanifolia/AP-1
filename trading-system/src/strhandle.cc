#include "strhandle.h"

#include <ctime>
#include <iostream>

#include "utfwidth.h"

using std::cout;
using std::endl;
using std::left;
using std::string;
using std::to_string;
using std::vector;

void StringSplit(const string& s, vector< string >& tokens, const string& delimiters /* = " "*/) {
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos     = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiters, pos);
        pos     = s.find_first_of(delimiters, lastPos);
    }
}

string TimeType1() {
    time_t t = time(0);
    char   tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    string ret(tmp);
    return ret;
}

string TimeType2() {
    time_t t = time(0);
    char   tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&t));
    string ret(tmp);
    return ret;
}

string Array2Expr(const vector< double >& array) {
    string ret;
    for (double i : array) {
        if (i >= 0) {
            ret += " + " + to_string(i);
        }
        else {
            ret += " - " + to_string(-i);
        }
    }
    if (ret[1] == '+')
        ret.erase(0, 3);
    ret = "(" + ret + ")";
    return ret;
}

void PrintSymbolEqual(int num) {
    for (int i = 0; i < num; ++i) {
        cout << "=";
    }
    cout << endl;
}

void PrintSymbolHorizontal(int num) {
    for (int i = 0; i < num; ++i) {
        cout << "-";
    }
    cout << endl;
}

void PrintSymbolStar(int num) {
    for (int i = 0; i < num; ++i) {
        cout << "*";
    }
    cout << endl;
}

void PrintUserTitle() {
    cout << left << setw_u8(8, "用户ID") << "用户ID";
    cout << left << setw_u8(10, "用户名") << "用户名";
    cout << left << setw_u8(18, "用户密码") << "用户密码";
    cout << left << setw_u8(15, "联系方式") << "联系方式";
    cout << left << setw_u8(15, "地址") << "地址";
    cout << left << setw_u8(8, "账户余额") << "账户余额";
    cout << left << setw_u8(8, "账户状态") << "账户状态";
    cout << endl;
}

void PrintItemTitle() {
    cout << left << setw_u8(8, "商品ID") << "商品ID";
    cout << left << setw_u8(15, "商品名") << "商品名";
    cout << left << setw_u8(12, "商品价格") << "商品价格";
    cout << left << setw_u8(12, "商品库存") << "商品库存";
    cout << left << setw_u8(20, "商品描述") << "商品描述";
    cout << left << setw_u8(8, "卖家ID") << "卖家ID";
    cout << left << setw_u8(15, "上架时间") << "上架时间";
    cout << left << setw_u8(8, "商品状态") << "商品状态";
    cout << endl;
}

void PrintOrderTitle() {
    cout << left << setw_u8(8, "订单ID") << "订单ID";
    cout << left << setw_u8(8, "商品ID") << "商品ID";
    cout << left << setw_u8(12, "交易单价") << "交易单价";
    cout << left << setw_u8(12, "交易数量") << "交易数量";
    cout << left << setw_u8(15, "交易时间") << "交易时间";
    cout << left << setw_u8(8, "卖家ID") << "卖家ID";
    cout << left << setw_u8(8, "买家ID") << "买家ID";
    cout << endl;
}