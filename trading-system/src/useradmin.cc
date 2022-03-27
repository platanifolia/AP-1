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
        cout << "1.查看所有商品  2.搜索商品  3.下架商品  4.查看所有订单  5.查看所有用户  6.封禁用户  7.注销" << endl;
        cout << string(122, '=') << endl;
        cout << "请输入您的选择：";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "\n"
                 << string(30, '*') << endl;
            cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            User::ViewItem();
            cout << "\n"
                 << string(30, '*') << endl;
            break;
        }
        case 2:
        {
            string search;
            cout << "请输入您要搜索的商品名称：";
            cin >> search;
            cout << "\n"
                 << string(30, '*') << endl;
            SearchItem(search);
            cout << "\n"
                 << string(30, '*') << endl;
            break;
        }
        case 3:
        {
            cout << "请输入要下架的商品ID：";
            string itemid;
            cin >> itemid;
            cout << "\n"
                 << string(30, '*') << endl;
            User::ViewItem(itemid);
            cout << "\n"
                 << string(30, '*') << endl;
            cout << "确认要下架这件商品吗？(Y/N):";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                User::OffShelf(itemid);
                cout << "下架成功！" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "\n"
                 << string(30, '*') << endl;
            cout << "订单ID  商品ID  交易单价  数量  交易时间  卖家ID  买家ID" << endl;
            User::ViewOrder();
            cout << "\n"
                 << string(30, '*') << endl;
            break;
        }
        case 5:
        {
            cout << "\n"
                 << string(30, '*') << endl;
            cout << "用户ID  用户名  联系方式  地址  钱包余额  用户状态" << endl;
            ViewUser();
            cout << "\n"
                 << string(30, '*') << endl;
            break;
        }
        case 6:
        {
            cout << "请输入要封禁的用户ID：";
            string userid;
            cin >> userid;
            cout << "\n"
                 << string(30, '*') << endl;
            User::ViewUser(userid);
            cout << "\n"
                 << string(30, '*') << endl;
            cout << "确认要封禁这个用户吗？(Y/N):";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                BanUser(userid);
                cout << "封禁成功！" << endl;
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

bool UserAdmin::BanUser(const string &userid)
{
    sdb_->ParseSql("UPDATE user SET userState=inactive WHERE userID=" + userid);
    return true;
}