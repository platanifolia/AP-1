#include "usergengral.h"

#include <iostream>
#include <fstream>

#include "strhandle.h"
#include "shoppingcart.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::ofstream;
using std::string;
using std::to_string;

UserGeneral::UserGeneral()
{
    sdb_ = nullptr;
    nowuserid_ = "";
}

UserGeneral::UserGeneral(SimpleDataBase *sdb, const std::string &nowuserid)
{
    sdb_ = sdb;
    nowuserid_ = nowuserid;
}

void UserGeneral::UserGeneralView()
{
    while (true)
    {
        cout << "\n"
             << string(55, '=') << endl;
        cout << "1.我是买家  2.我是卖家  3.个人信息管理  4.注销登录" << endl;
        cout << string(55, '=') << endl;
        cout << "请输入您的选择：";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            BuyerView();
            break;
        }
        case 2:
        {
            SellerView();
            break;
        }
        case 3:
        {
            UserInfoView();
            break;
        }
        case 4:
            return;
        default:
        {
            cerr << "输入错误，请重新输入！" << endl;
            break;
        }
        }
    }
}

void UserGeneral::BuyerView()
{
    while (true)
    {
        cout << "\n"
             << string(100, '=') << endl;
        cout << "1.查看商品列表  2.购买商品  3.搜索商品  4.查看历史订单  5.查看商品详细信息  6.进入购物车  7.返回用户主界面" << endl;
        cout << string(100, '=') << endl;
        int choice;
        cout << "请输入您的选择：";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "\n"
                 << string(60, '*') << endl;
            cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            BuyerViewItem();
            cout << string(60, '*') << endl;
            break;
        }
        case 2:
        {
            string itemid;
            int buynumber;
            cout << "请输入您要购买的商品ID：";
            cin >> itemid;
            cout << "请输入您要购买的商品数量：";
            cin >> buynumber;
            if (Purchase(itemid, buynumber))
            {
                cout << "购买成功！" << endl;
            }
            else
            {
                cout << "购买失败！" << endl;
            }
            break;
        }
        case 3:
        {
            string search;
            cout << "请输入您要搜索的商品名称：";
            cin >> search;
            cout << "\n"
                 << string(60, '*') << endl;
            cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            SearchItem(search);
            cout << string(60, '*') << endl;
            break;
        }
        case 4:
        {
            cout << "\n";
            cout << string(60, '*') << endl;
            cout << "订单ID  商品ID  交易单价  数量  交易时间  卖家ID  买家ID" << endl;
            BuyerViewOrder();
            cout << string(60, '*') << endl;
            break;
        }
        case 5:
        {
            string itemid;
            cout << "请输入您要查看的商品ID：";
            cin >> itemid;
            sdb_->ViewItemDetail(itemid);
            break;
        }
        case 6:
        {
            ShoppingCart sc(sdb_);
            sc.CartInterface(this->nowuserid_);
            break;
        }
        case 7:
            return;
        default:
        {
            cerr << "输入错误，请重新输入！" << endl;
            break;
        }
        }
    }
}

void UserGeneral::SellerView()
{
    while (true)
    {
        cout << "\n"
             << string(100, '=') << endl;
        cout << "1.发布商品  2.查看发布商品  3.修改商品信息  4.下架商品  5.查看历史订单  6.返回用户主界面" << endl;
        cout << string(100, '=') << endl;
        cout << nowuserid_ << endl;
        int choice;
        cout << "请输入您的选择：";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string itemname;
            string itemprice;
            string itemnumber;
            string itemdescription;
            cout << "请输入商品名称：";
            cin >> itemname;
            cout << "请输入商品价格：";
            cin >> itemprice;
            cout << "请输入商品数量：";
            cin >> itemnumber;
            cout << "请输入商品描述：";
            cin >> itemdescription;
            cout << "\n";
            cout << "请确认已输入的商品信息：" << endl;
            cout << string(30, '-') << endl;
            cout << "商品名称：" << itemname << endl;
            cout << "商品价格：" << itemprice << endl;
            cout << "商品数量：" << itemnumber << endl;
            cout << "商品描述：" << itemdescription << endl;
            cout << string(30, '-') << endl;
            cout << "\n";
            cout << "是否确认发布？(y/n)：";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                if (PostItem(itemname, itemprice, itemnumber, itemdescription))
                {
                    cout << "发布成功！" << endl;
                }
                else
                {
                    cout << "发布失败！" << endl;
                }
            }
            else
            {
                cout << "取消发布商品" << endl;
            }
            break;
        }
        case 2:
        {
            cout << "\n"
                 << string(55, '*') << endl;
            cout << "商品ID  名称  价格  数量  描述  卖家ID  上架时间  商品状态" << endl;
            SellerViewItem();
            cout << string(55, '*') << endl;
            break;
        }
        case 3:
        {
            string itemid;
            int modifychoice;
            string modifydata;
            cout << "请输入需要修改的商品编号：";
            cin >> itemid;
            cout << "请输入您的选择(1.价格2.描述)：";
            cin >> modifychoice;
            switch (modifychoice)
            {
            case 1:
            {
                cout << "请输入新的价格：";
                cin >> modifydata;
                if (ModifyItem(itemid, modifychoice, modifydata))
                {
                    cout << "修改成功！" << endl;
                }
                else
                {
                    cout << "修改失败！" << endl;
                }
                break;
            }
            case 2:
            {
                cout << "请输入新的描述：";
                cin >> modifydata;
                if (ModifyItem(itemid, modifychoice, modifydata))
                {
                    cout << "修改成功！" << endl;
                }
                else
                {
                    cout << "修改失败！" << endl;
                }
                break;
            }
            default:
            {
                cerr << "输入错误，请重新输入！" << endl;
                break;
            }
            }
        }
        case 4:
        {
            string itemid;
            cout << "请输入需要下架的商品编号：";
            cin >> itemid;
            if (sdb_->GerItemSellerid(itemid) != nowuserid_)
            {
                cout << "您无权下架该商品！" << endl;
                break;
            }
            cout << string(60, '*') << endl;
            cout << "商品ID  名称  价格  数量  描述  卖家ID  上架时间  商品状态" << endl;
            User::ViewItem(itemid);
            cout << string(60, '*') << endl;
            cout << "是否确认下架？(y/n)：";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                if (User::OffShelf(itemid))
                {
                    cout << "下架成功！" << endl;
                }
                else
                {
                    cout << "下架失败！" << endl;
                }
            }
            else
            {
                cout << "取消下架商品" << endl;
            }
            break;
        }
        case 5:
        {
            cout << "\n";
            cout << string(60, '*') << endl;
            cout << "订单ID  商品ID  交易单价  数量  交易时间  卖家ID  买家ID" << endl;
            SellerViewOrder();
            cout << string(60, '*') << endl;
            break;
        }
        case 6:
            return;
        default:
        {
            cerr << "输入错误，请重新输入！" << endl;
            break;
        }
        }
    }
}

void UserGeneral::UserInfoView()
{
    while (true)
    {
        cout << "\n"
             << string(60, '=') << endl;
        cout << "1.查看信息  2.修改信息  3.充值  4.返回用户主界面" << endl;
        cout << string(60, '=') << endl;
        int choice;
        cout << "请输入您的选择：";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            ViewUserDetail();
            break;
        }
        case 2:
        {
            int choice;
            string newdata;
            cout << "请输入修改属性(1.用户名  2.联系方式  3.地址)：";
            cin >> choice;
            cout << "请输入新的信息：";
            cin >> newdata;
            if (ModifyUserInfo(choice, newdata))
            {
                cout << "修改成功！" << endl;
            }
            else
            {
                cout << "修改失败！" << endl;
            }
            break;
        }
        case 3:
        {
            double money;
            cout << "请输入充值金额：";
            cin >> money;
            Recharge(money);
            break;
        }
        case 4:
            return;
        default:
        {
            cerr << "输入错误，请重新输入！" << endl;
            break;
        }
        }
    }
}

bool UserGeneral::PostItem(const std::string &itemname, const std::string &itemprice,
                           const std::string &itemnumber, const std::string &itemdescription)
{
    string itemdata = "(" + sdb_->GetNewItemid() + "," + itemname + "," + itemprice + "," + itemnumber + "," + itemdescription + "," + this->nowuserid_ + "," + TimeType2() + "," + "onSale" + ")";
    sdb_->ParseSql("INSERT INTO commodity VALUES " + itemdata);
    return true;
}

void UserGeneral::SellerViewItem()
{
    sdb_->ParseSql("SELECT * FROM commodity WHERE sellerID CONTAINS " + this->nowuserid_);
    return;
}

bool UserGeneral::ModifyItem(const std::string &itemid, int modifychoice, const std::string &modifydata)
{
    switch (modifychoice)
    {
    case 1:
    {
        sdb_->ParseSql("UPDATE commodity SET price=" + modifydata + " WHERE commodityID=" + itemid);
        return true;
    }
    case 2:
    {
        sdb_->ParseSql("UPDATE commodity SET description=" + modifydata + " WHERE commodityID=" + itemid);
        return true;
    }
    default:
    {
        cerr << "输入错误，请重新输入！" << endl;
        return false;
    }
    }
}

void UserGeneral::SellerViewOrder()
{
    sdb_->ParseSql("SELECT * FROM order WHERE sellerID CONTAINS " + this->nowuserid_);
    return;
}

void UserGeneral::BuyerViewItem()
{
    sdb_->ParseSql("SELECT * FROM commodity WHERE state CONTAINS onSale");
    return;
}

void UserGeneral::SearchItem(const string &itemname)
{
    sdb_->ParseSql("SELECT * FROM commodity WHERE commodityName CONTAINS " + itemname);
    return;
}

void UserGeneral::BuyerViewOrder()
{
    sdb_->ParseSql("SELECT * FROM order WHERE buyerID CONTAINS" + this->nowuserid_);
    return;
}

bool UserGeneral::Purchase(const string &itemid, int buynumber)
{
    int itemnumber = sdb_->GetItemNumber(itemid);
    double unitprice = sdb_->GetItemPrice(itemid);
    double nowmoney = sdb_->FindUserBalance(this->nowuserid_);
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
                sdb_->ParseSql("UPDATE user SET balance=" + to_string(nowmoney - buynumber * unitprice) + " WHERE userID=" + this->nowuserid_);
                sdb_->ParseSql("UPDATE user SET balance=" + to_string(sellermoney + buynumber * unitprice) + " WHERE userID=" + sellerid);
                sdb_->ParseSql("INSERT INTO order VALUES (" + sdb_->GetNewOrderid() + "," + itemid + "," + to_string(unitprice) + "," + to_string(buynumber) + "," + TimeType2() + "," + sellerid + "," + this->nowuserid_ + ")");
                if (itemnumber == buynumber)
                    sdb_->ParseSql("UPDATE commodity SET state=removed WHERE commodityID=" + itemid);
                return true;
            }
            else
            {
                cerr << "余额不足！" << endl;
                cout << "需要进行充值吗？(y/n):";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    double money;
                    cout << "请输入充值金额：";
                    cin >> money;
                    Recharge(money);
                    return false;
                }
                else
                {
                    return false;
                }
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

bool UserGeneral::ModifyUserInfo(int choice, const string &modifydata)
{
    if (choice == 1)
    {
        sdb_->ParseSql("UPDATE user SET userName=" + modifydata + " WHERE userID=" + this->nowuserid_);
        return true;
    }
    else if (choice == 2)
    {
        sdb_->ParseSql("UPDATE user SET phoneNumber=" + modifydata + " WHERE userID=" + this->nowuserid_);
        return true;
    }
    else if (choice == 3)
    {
        sdb_->ParseSql("UPDATE user SET address=" + modifydata + " WHERE userID=" + this->nowuserid_);
        return true;
    }
    else
    {
        return false;
    }
}

bool UserGeneral::Recharge(double money)
{
    double nowmoney = sdb_->FindUserBalance(this->nowuserid_);
    sdb_->ParseSql("UPDATE user SET balance=" + to_string(nowmoney + money) + " WHERE userID=" + this->nowuserid_);
    ofstream outfile("data/recharge.txt", ios::app);
    outfile << this->nowuserid_ << " " << money << " " << TimeType2() << endl;
    outfile.close();
    return true;
}

void UserGeneral::ViewUserDetail()
{
    cout << string(60, '*') << endl;
    cout << "用户名：" << sdb_->FindUsername(this->nowuserid_) << endl;
    cout << "联系方式: " << sdb_->FindUserPhone(this->nowuserid_) << endl;
    cout << "地址：" << sdb_->FindUserAddress(this->nowuserid_) << endl;
    cout << "余额：" << sdb_->CalculateBalance(this->nowuserid_) << endl;
    cout << string(60, '*') << endl;
    return;
}