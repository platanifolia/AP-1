#include "useradmin.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

UserAdmin::UserAdmin()
{
    sdb_ = nullptr;
}

UserAdmin::UserAdmin(SimpleDataBase *sdb)
{
    sdb_ = sdb;
}

void UserAdmin::AdminView()
{
    while (true)
    {
        cout << string(122, '=') << endl;
        cout << "1.查看所有商品 2.搜索商品  3.下架商品  4.查看所有订单  5.查看所有用户  6.封禁用户  7.注销" << endl;
        cout << string(122, '=') << endl;
        cout << "请输入您的选择：";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            sdb_->ParseSql("SELECT * FROM commodity");
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            return;
        }
        default:
        {
            cout << "似乎输入错误指令?请检查" << endl;
            break;
        }
        }
    }
}