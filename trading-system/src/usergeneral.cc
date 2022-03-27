#include "usergengral.h"

#include <iostream>

#include "strhandle.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

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
             << string(30, '=') << endl;
        cout << "1.我是买家  2.我是卖家  3.个人信息管理  4.注销登录" << endl;
        cout << string(30, '=') << endl;
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
            break;
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
             << string(30, '=') << endl;
        cout << "1.查看商品列表  2.购买商品  3.搜索商品  4.查看历史订单  5.查看商品详细信息  6.返回用户主界面" << endl;
        cout << string(30, '=') << endl;
        int choice;
        cout << "请输入您的选择：";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "\n"
                 << string(30, '*') << endl;
            cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            BuyerViewItem();
            cout << string(30, '*') << endl;
            break;
        }
        case 2:
            break;
        case 3:
        {
            string search;
            cout << "请输入您要搜索的商品名称：";
            cin >> search;
            cout << "\n"
                 << string(30, '*') << endl;
            cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            SearchItem(search);
            cout << string(30, '*') << endl;
            break;
        }
        case 4:
        {
            cout << "\n";
            cout << string(30, '*') << endl;
            cout << "订单ID  商品ID  交易单价  数量  交易时间  卖家ID  买家ID" << endl;
            BuyerViewOrder();
            cout << string(30, '*') << endl;
            break;
        }
        case 5:
            break;
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

void UserGeneral::SellerView()
{
    while (true)
    {
        cout << "\n"
             << string(30, '=') << endl;
        cout << "1.发布商品  2.查看发布商品  3.修改商品信息  4.下架商品  5.查看历史订单  6.返回用户主界面" << endl;
        cout << string(30, '=') << endl;
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
                 << string(30, '*') << endl;
            cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            SellerViewItem();
            cout << string(30, '*') << endl;
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
            if (sdb_->GetItemOwner(itemid) != nowuserid_)
            {
                cout << "您无权下架该商品！" << endl;
                break;
            }
            cout << string(30, '*') << endl;
            cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            User::ViewItem(itemid);
            cout << string(30, '*') << endl;
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
            cout << string(30, '*') << endl;
            cout << "订单ID  商品ID  交易单价  数量  交易时间  卖家ID  买家ID" << endl;
            SellerViewOrder();
            cout << string(30, '*') << endl;
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
             << string(30, '=') << endl;
        cout << "1.查看信息  2.修改信息  3.充值  4.返回用户主界面" << endl;
        cout << string(30, '=') << endl;
        int choice;
        cout << "请输入您的选择：";
        cin >> choice;
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
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