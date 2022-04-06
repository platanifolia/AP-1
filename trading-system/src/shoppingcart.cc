#include "shoppingcart.h"

#include <iostream>
#include <fstream>

#include "strhandle.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::to_string;

ShoppingCart::ShoppingCart()
{
    sdb_ = nullptr;
    ofstream cartfile("data/cart.txt", ios::app);
    cartfile.close();
}

ShoppingCart::ShoppingCart(SimpleDataBase *sdb)
{
    sdb_ = sdb;
    ofstream cartfile("data/cart.txt", ios::app);
    cartfile.close();
}

bool ShoppingCart::LoadShoppingCart()
{
    ifstream cartfile("data/cart.txt");
    if (!cartfile)
    {
        cout << "Open cart.txt failed!" << endl;
        return false;
    }
    string line;
    while (getline(cartfile, line))
    {
        string userid = line.substr(0, line.find(' '));
        line = line.substr(line.find(' ') + 1);
        string itemid = line.substr(0, line.find(' '));
        line = line.substr(line.find(' ') + 1);
        int number = stoi(line);
        shoppingcart_[userid][itemid] = number;
    }
    cartfile.close();
    return true;
}

bool ShoppingCart::SaveShoppingCart()
{
    ofstream cartfile("data/cart.txt", ios::trunc);
    if (!cartfile)
    {
        cout << "Open cart.txt failed!" << endl;
        return false;
    }
    for (auto &user : shoppingcart_)
    {
        for (auto &item : user.second)
        {
            cartfile << user.first << " ";
            cartfile << item.first << " " << item.second << endl;
        }
    }
    cartfile.close();
    return true;
}

bool ShoppingCart::UpdateShoppingCart(const string &userid, const string &itemid, int number)
{
    if (shoppingcart_.find(userid) == shoppingcart_.end())
    {
        shoppingcart_[userid][itemid] = number;
    }
    else
    {
        if (shoppingcart_[userid].find(itemid) == shoppingcart_[userid].end())
        {
            shoppingcart_[userid][itemid] = number;
        }
        else
        {
            shoppingcart_[userid][itemid] += number;
        }
    }
    return SaveShoppingCart();
}

void ShoppingCart::ViewShoppingCart(const string &userid)
{
    cout << "User " << userid << "'s shopping cart:" << endl;
    if (shoppingcart_.find(userid) == shoppingcart_.end())
    {
        cout << "Shopping cart is empty!" << endl;
        return;
    }
    for (auto &item : shoppingcart_[userid])
    {
        cout << item.first << " " << item.second << endl;
    }
}

double ShoppingCart::TotalPrice(const string &userid)
{
    double totalprice = 0;
    if (shoppingcart_.find(userid) == shoppingcart_.end())
    {
        return totalprice;
    }
    for (auto &item : shoppingcart_[userid])
    {
        totalprice += sdb_->GetItemPrice(item.first) * item.second;
    }
    return totalprice;
}

bool ShoppingCart::BuyItem(const string &userid, const string &itemid, int buynumber)
{
    int itemnumber = sdb_->GetItemNumber(itemid);
    double unitprice = sdb_->GetItemPrice(itemid);
    double nowmoney = sdb_->FindUserBalance(userid);
    string sellerid = sdb_->GerItemSellerid(itemid);
    double sellermoney = sdb_->FindUserBalance(sellerid);
    // item exist
    if (unitprice > 0)
    {
        if (itemnumber >= buynumber)
        {
            if (nowmoney >= buynumber * unitprice)
            {
                sdb_->ParseSql("UPDATE commodity SET number=" + to_string(itemnumber - buynumber) + " WHERE commodityID=" + itemid);
                sdb_->ParseSql("UPDATE user SET balance=" + to_string(nowmoney - buynumber * unitprice) + " WHERE userID=" + userid);
                sdb_->ParseSql("UPDATE user SET balance=" + to_string(sellermoney + buynumber * unitprice) + " WHERE userID=" + sellerid);
                sdb_->ParseSql("INSERT INTO order VALUES (" + sdb_->GetNewOrderid() + "," + itemid + "," + to_string(unitprice) + "," + to_string(buynumber) + "," + TimeType2() + "," + sellerid + "," + userid + ")");
                if (itemnumber == buynumber)
                    sdb_->ParseSql("UPDATE commodity SET state=removed WHERE commodityID=" + itemid);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            cerr << "库存不足！" << endl;
            return false;
        }
    }
    else
    {
        cerr << "商品不存在！" << endl;
        return false;
    }
}

bool ShoppingCart::BuyAll(const string &userid)
{
    if (shoppingcart_.find(userid) == shoppingcart_.end())
    {
        cerr << "购物车为空！" << endl;
        return false;
    }
    for (auto &item : shoppingcart_[userid])
    {
        // TOFIX:
        if (!BuyItem(userid, item.first, item.second))
            return false;
        shoppingcart_[userid].erase(item.first);
    }
    return true;
}

void ShoppingCart::CartInterface(const string &userid)
{
    cout << string(50, '-') << endl;
    cout << "1.查看购物车  2.添加商品  3.结算  4.退出购物车" << endl;
    cout << string(50, '-') << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        ViewShoppingCart(userid);
        break;
    }
    case 2:
    {
        string itemid;
        int number;
        cout << "请输入商品编号：" << endl;
        cin >> itemid;
        cout << "请输入购买数量：" << endl;
        cin >> number;
        UpdateShoppingCart(userid, itemid, number);
        break;
    }
    case 3:
    {
        if (BuyAll(userid))
        {
            cout << "购买成功！" << endl;
            SaveShoppingCart();
        }
        else
        {
            cout << "购买失败！" << endl;
        }
        break;
    }
    case 4:
    {
        return;
    }
    default:
    {
        cerr << "输入错误！" << endl;
        break;
    }
    }
}