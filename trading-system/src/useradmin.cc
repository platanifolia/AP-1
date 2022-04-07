#include "useradmin.h"

#include <iostream>
#include <string>

#include "strhandle.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
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
        cout << endl;
        PrintSymbolEqual(94);
        cout << "1.查看所有商品  2.搜索商品  3.下架商品  4.查看所有订单  5.查看所有用户  6.用户状态切换  7.注销" << endl;
        PrintSymbolEqual(94);
        cout << "请输入您的选择：";
        string input;
        int choice;
        getline(cin, input);
        if (input.length() != 1)
        {
            cout << "输入错误，请重新输入" << endl;
            continue;
        }
        choice = stoi(input);
        switch (choice)
        {
        case 1:
        {
            cout << endl;
            PrintSymbolStar(100);
            PrintItemTitle();
            User::ViewItem();
            PrintSymbolStar(100);
            cout << endl;
            break;
        }
        case 2:
        {
            string search;
            cout << "请输入您要搜索的商品名称：";
            getline(cin, search);
            cout << endl;
            PrintSymbolStar(100);
            SearchItem(search);
            PrintSymbolStar(100);
            cout << endl;
            break;
        }
        case 3:
        {
            cout << "请输入要下架的商品ID：";
            string itemid;
            getline(cin, itemid);
            cout << endl;
            PrintSymbolStar(100);
            PrintItemTitle();
            User::ViewItem(itemid);
            PrintSymbolStar(100);
            cout << endl;
            cout << "确认要下架这件商品吗？(Y/N):";
            string choice;
            getline(cin, choice);
            if (choice == "Y" || choice == "y")
                User::OffShelf(itemid);
            break;
        }
        case 4:
        {
            cout << endl;
            PrintSymbolStar(60);
            // cout << "订单ID  商品ID  交易单价  数量  交易时间  卖家ID  买家ID" << endl;
            PrintOrderTitle();
            User::ViewOrder();
            PrintSymbolStar(60);
            cout << endl;
            break;
        }
        case 5:
        {
            cout << endl;
            PrintSymbolStar(90);
            // cout << "用户ID  用户名  联系方式  地址  钱包余额  用户状态" << endl;
            PrintUserTitle();
            ViewUser();
            PrintSymbolStar(90);
            cout << endl;
            break;
        }
        case 6:
        {
            cout << "请输入要切换状态的用户ID：";
            string userid;
            getline(cin, userid);
            cout << endl;
            PrintSymbolStar(90);
            PrintUserTitle();
            User::ViewUser(userid);
            PrintSymbolStar(90);
            cout << endl;
            cout << "确认要变更这个用户吗？(Y/N):";
            string choice;
            getline(cin, choice);
            if (choice == "Y" || choice == "y")
            {
                SwitchUserStatus(userid);
            }
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

void UserAdmin::SearchItem(const string &itemname)
{
    sdb_->ParseSql("SELECT * FROM commodity WHERE commodityName CONTAINS " + itemname);
    return;
}

bool UserAdmin::SwitchUserStatus(const string &userid)
{
    if(sdb_->UserNotBan(userid))
    {
        sdb_->ParseSql("UPDATE user SET userState=封禁 WHERE userID=" + userid);
        return true;
    }
    else
    {
        sdb_->ParseSql("UPDATE user SET userState=正常 WHERE userID=" + userid);
        return true;
    }
    return false;
}