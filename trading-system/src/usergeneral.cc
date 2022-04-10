#include "usergengral.h"

#include <fstream>
#include <iostream>
#include <regex>

#include "shoppingcart.h"
#include "strhandle.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ios;
using std::ofstream;
using std::regex;
using std::regex_match;
using std::string;
using std::to_string;

UserGeneral::UserGeneral() {
    sdb_       = nullptr;
    nowuserid_ = "";
}

UserGeneral::UserGeneral(SimpleDataBase* sdb, const std::string& nowuserid) {
    sdb_       = sdb;
    nowuserid_ = nowuserid;
}

void UserGeneral::UserGeneralView() {
    while (true) {
        cout << endl;
        PrintSymbolEqual(50);
        cout << "1.我是买家  2.我是卖家  3.个人信息管理  4.注销登录" << endl;
        PrintSymbolEqual(50);
        cout << "请输入您的选择：";
        string input;
        getline(cin, input);
        if (input.length() != 1) {
            cout << "输入错误，请重新输入" << endl;
            continue;
        }
        int choice;
        choice = stoi(input);
        switch (choice) {
        case 1: {
            BuyerView();
            break;
        }
        case 2: {
            SellerView();
            break;
        }
        case 3: {
            UserInfoView();
            break;
        }
        case 4:
            return;
        default: {
            cout << "输入错误，请重新输入" << endl;
            break;
        }
        }
    }
}

void UserGeneral::BuyerView() {
    while (true) {
        // cout << "\n"
        //      << string(70, '=') << endl;
        cout << endl;
        PrintSymbolEqual(106);
        cout << "1.查看商品列表  2.购买商品  3.搜索商品  4.查看历史订单  5.查看商品详细信息  6.进入购物车  7.返回用户主界面" << endl;
        PrintSymbolEqual(106);
        int    choice;
        string input;
        cout << "请输入您的选择：";
        getline(cin, input);
        if (input.length() != 1) {
            cout << "输入错误，请重新输入" << endl;
            continue;
        }
        choice = stoi(input);
        switch (choice) {
        case 1: {
            cout << endl;
            PrintSymbolStar(100);
            // cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            PrintItemTitle();
            BuyerViewItem();
            PrintSymbolStar(100);
            break;
        }
        case 2: {
            string itemid;
            int    buynumber;
            cout << "请输入您要购买的商品ID：";
            getline(cin, itemid);
            if (nowuserid_ == sdb_->GetItemSellerid(itemid)) {
                cout << "您不能购买自己的商品" << endl;
                continue;
            }
            if (!sdb_->ItemExist(itemid)) {
                cout << "商品不存在" << endl;
                continue;
            }
            cout << "请输入您要购买的商品数量：";
            string input;
            getline(cin, input);
            buynumber = stoi(input);
            if (buynumber > sdb_->GetItemNumber(itemid)) {
                cout << "商品库存不足" << endl;
                continue;
            }
            if (!Purchase(itemid, buynumber))
                cout << "购买失败" << endl;
            break;
        }
        case 3: {
            string search;
            cout << "请输入您要搜索的商品名称：";
            getline(cin, search);
            cout << endl;
            PrintSymbolStar(100);
            // cout << "商品ID  名称  价格  上架时间  卖家ID  数量  商品状态" << endl;
            PrintItemTitle();
            SearchItem(search);
            PrintSymbolStar(100);
            break;
        }
        case 4: {
            cout << endl;
            PrintSymbolStar(70);
            // cout << "订单ID  商品ID  交易单价  数量  交易时间  卖家ID  买家ID" << endl;
            PrintOrderTitle();
            BuyerViewOrder();
            PrintSymbolStar(70);
            break;
        }
        case 5: {
            string itemid;
            cout << "请输入您要查看的商品ID：";
            getline(cin, itemid);
            sdb_->ViewItemDetail(itemid);
            break;
        }
        case 6: {
            ShoppingCart sc(sdb_);
            sc.CartInterface(this->nowuserid_);
            break;
        }
        case 7:
            return;
        default: {
            cout << "输入错误，请重新输入" << endl;
            break;
        }
        }
    }
}

void UserGeneral::SellerView() {
    while (true) {
        cout << endl;
        PrintSymbolEqual(90);
        cout << "1.发布商品  2.查看发布商品  3.修改商品信息  4.下架商品  5.查看历史订单  6.返回用户主界面" << endl;
        PrintSymbolEqual(90);
        cout << endl;
        // cout << nowuserid_ << endl;
        string input;
        int    choice;
        cout << "请输入您的选择：";
        getline(cin, input);
        if (input.length() != 1) {
            cout << "输入错误，请重新输入" << endl;
            continue;
        }
        choice = stoi(input);
        switch (choice) {
        case 1: {
            string itemname;
            string itemprice;
            string itemnumber;
            string itemdescription;
            regex  pricereg("^[0-9]+(.[0-9]{1,2})?$");
            regex  numberreg("^[1-9][0-9]*$");
            cout << "请输入商品名称：";
            getline(cin, itemname);
            cout << "请输入商品价格：";
            getline(cin, itemprice);
            cout << "请输入商品数量：";
            getline(cin, itemnumber);
            if (!regex_match(itemprice, pricereg) || !regex_match(itemnumber, numberreg)) {
                cout << "输入错误，请重新输入" << endl;
                continue;
            }
            cout << "请输入商品描述：";
            getline(cin, itemdescription);
            cout << endl;
            cout << "请确认已输入的商品信息：" << endl;
            PrintSymbolHorizontal(30);
            cout << "商品名称：" << itemname << endl;
            cout << "商品价格：" << itemprice << endl;
            cout << "商品数量：" << itemnumber << endl;
            cout << "商品描述：" << itemdescription << endl;
            PrintSymbolHorizontal(30);
            cout << endl;
            cout << "是否确认发布？(y/n)：";
            getline(cin, input);
            if (input == "y" || input == "Y") {
                if (!PostItem(itemname, itemprice, itemnumber, itemdescription))
                    cout << "发布失败" << endl;
            }
            else {
                cout << "已取消发布商品" << endl;
            }
            break;
        }
        case 2: {
            cout << endl;
            PrintSymbolStar(100);
            // cout << "商品ID  名称  价格  数量  描述  卖家ID  上架时间  商品状态" << endl;
            PrintItemTitle();
            SellerViewItem();
            PrintSymbolStar(100);
            cout << endl;
            break;
        }
        case 3: {
            string itemid;
            int    modifychoice;
            string modifydata;
            cout << "请输入需要修改的商品编号：";
            getline(cin, itemid);
            if (!sdb_->ItemExist(itemid)) {
                cout << "商品不存在" << endl;
                continue;
            }
            if (nowuserid_ != sdb_->GetItemSellerid(itemid)) {
                cout << "您无权修改该商品" << endl;
                continue;
            }
            cout << "请输入您的选择(1.价格  2.描述)：";
            getline(cin, input);
            if (input.length() != 1) {
                cout << "输入错误，请重新输入" << endl;
                break;
            }
            modifychoice = stoi(input);
            switch (modifychoice) {
            case 1: {
                cout << "请输入新的价格：";
                getline(cin, modifydata);
                if (!ModifyItem(itemid, modifychoice, modifydata))
                    cout << "修改失败" << endl;
                break;
            }
            case 2: {
                cout << "请输入新的描述：";
                getline(cin, modifydata);
                if (!ModifyItem(itemid, modifychoice, modifydata))
                    cout << "修改失败" << endl;
                break;
            }
            default: {
                cout << "输入错误，请重新输入" << endl;
                break;
            }
            }
            break;
        }
        case 4: {
            string itemid;
            cout << "请输入需要下架的商品编号：";
            getline(cin, itemid);
            if (sdb_->GetItemSellerid(itemid) != nowuserid_) {
                cout << "您无权下架该商品" << endl;
                break;
            }
            PrintSymbolStar(100);
            // cout << "商品ID  名称  价格  数量  描述  卖家ID  上架时间  商品状态" << endl;
            PrintItemTitle();
            User::ViewItem(itemid);
            PrintSymbolStar(100);
            cout << "是否确认下架？(y/n)：";
            getline(cin, input);
            if (input == "y" || input == "Y") {
                if (!User::OffShelf(itemid))
                    cout << "下架失败" << endl;
            }
            else {
                cout << "取消下架商品" << endl;
            }
            break;
        }
        case 5: {
            cout << endl;
            PrintSymbolStar(63);
            // cout << "订单ID  商品ID  交易单价  数量  交易时间  卖家ID  买家ID" << endl;
            PrintOrderTitle();
            SellerViewOrder();
            PrintSymbolStar(63);
            break;
        }
        case 6:
            return;
        default: {
            cout << "输入错误，请重新输入" << endl;
            break;
        }
        }
    }
}

void UserGeneral::UserInfoView() {
    while (true) {
        cout << endl;
        PrintSymbolEqual(50);
        cout << "1.查看信息  2.修改信息  3.充值  4.返回用户主界面" << endl;
        PrintSymbolEqual(50);
        string input;
        int    choice;
        cout << "请输入您的选择：";
        getline(cin, input);
        if (input.length() != 1) {
            cout << "输入错误，请重新输入" << endl;
            continue;
        }
        choice = stoi(input);
        switch (choice) {
        case 1: {
            ViewUserDetail();
            break;
        }
        case 2: {
            int    choice;
            string newdata;
            cout << "请输入修改属性(1.用户名  2.联系方式  3.地址  4.密码)：";
            getline(cin, input);
            choice = stoi(input);
            cout << "请输入新的信息：";
            getline(cin, newdata);
            if (!ModifyUserInfo(choice, newdata))
                cout << "修改失败" << endl;
            break;
        }
        case 3: {
            double money;
            cout << "请输入充值金额：";
            getline(cin, input);
            money = stod(input);
            Recharge(money);
            break;
        }
        case 4:
            return;
        default: {
            cout << "输入错误，请重新输入" << endl;
            break;
        }
        }
    }
}

bool UserGeneral::PostItem(const std::string& itemname, const std::string& itemprice, const std::string& itemnumber, const std::string& itemdescription) {
    if (stod(itemprice) <= 0 || stod(itemnumber) <= 0) {
        cout << "价格或数量不合法" << endl;
        return false;
    }
    string itemdata = "(" + sdb_->GetNewItemid() + "," + itemname + "," + itemprice + "," + itemnumber + "," + itemdescription + "," + this->nowuserid_ + "," + TimeType2() + "," + "销售中" + ")";
    sdb_->ParseSql("INSERT INTO commodity VALUES " + itemdata);
    return true;
}

void UserGeneral::SellerViewItem() {
    sdb_->ParseSql("SELECT * FROM commodity WHERE sellerID CONTAINS " + this->nowuserid_);
    return;
}

bool UserGeneral::ModifyItem(const std::string& itemid, int modifychoice, const std::string& modifydata) {
    switch (modifychoice) {
    case 1: {
        sdb_->ParseSql("UPDATE commodity SET price=" + modifydata + " WHERE commodityID=" + itemid);
        return true;
    }
    case 2: {
        sdb_->ParseSql("UPDATE commodity SET description=" + modifydata + " WHERE commodityID=" + itemid);
        return true;
    }
    default: {
        cout << "输入错误，请重新输入" << endl;
        return false;
    }
    }
}

void UserGeneral::SellerViewOrder() {
    sdb_->ParseSql("SELECT * FROM order WHERE sellerID CONTAINS " + this->nowuserid_);
    return;
}

void UserGeneral::BuyerViewItem() {
    sdb_->ParseSql("SELECT * FROM commodity WHERE state CONTAINS 销售中");
    return;
}

void UserGeneral::SearchItem(const string& itemname) {
    sdb_->ParseSql("SELECT * FROM commodity WHERE commodityName CONTAINS " + itemname);
    return;
}

void UserGeneral::BuyerViewOrder() {
    sdb_->ParseSql("SELECT * FROM order WHERE buyerID CONTAINS " + this->nowuserid_);
    return;
}

bool UserGeneral::Purchase(const string& itemid, int buynumber) {
    int    itemnumber  = sdb_->GetItemNumber(itemid);
    double unitprice   = sdb_->GetItemPrice(itemid);
    double nowmoney    = sdb_->FindUserBalance(this->nowuserid_);
    string sellerid    = sdb_->GetItemSellerid(itemid);
    double sellermoney = sdb_->FindUserBalance(sellerid);
    if (!sdb_->ItemNotDown(itemid)) {
        cout << "商品已下架" << endl;
        return false;
    }
    // item exist
    if (unitprice > 0) {
        if (itemnumber >= buynumber) {
            if (nowmoney >= buynumber * unitprice) {
                sdb_->ParseSql("UPDATE commodity SET number=" + to_string(itemnumber - buynumber) + " WHERE commodityID=" + itemid);
                sdb_->ParseSql("UPDATE user SET balance=" + to_string(nowmoney - buynumber * unitprice) + " WHERE userID=" + this->nowuserid_);
                sdb_->ParseSql("UPDATE user SET balance=" + to_string(sellermoney + buynumber * unitprice) + " WHERE userID=" + sellerid);
                sdb_->ParseSql("INSERT INTO order VALUES (" + sdb_->GetNewOrderid() + "," + itemid + "," + to_string(unitprice) + "," + to_string(buynumber) + "," + TimeType2() + "," + sellerid + ","
                               + this->nowuserid_ + ")");
                if (itemnumber == buynumber)
                    sdb_->ParseSql("UPDATE commodity SET state=已下架 WHERE commodityID=" + itemid);
                return true;
            }
            else {
                cout << "余额不足" << endl;
                cout << "需要进行充值吗？(y/n):";
                string choice;
                getline(cin, choice);
                if (choice == "y" || choice == "Y") {
                    string money;
                    cout << "请输入充值金额：";
                    getline(cin, money);
                    Recharge(stod(money));
                    return false;
                }
                else {
                    return false;
                }
                return false;
            }
        }
        else {
            cerr << "库存不足" << endl;
            return false;
        }
    }
    else {
        cerr << "商品不存在" << endl;
        return false;
    }
}

bool UserGeneral::ModifyUserInfo(int choice, const string& modifydata) {
    if (choice == 1) {
        if (sdb_->UsernameExist(modifydata)) {
            cout << "用户名已存在" << endl;
            return false;
        }
        sdb_->ParseSql("UPDATE user SET username=" + modifydata + " WHERE userID=" + this->nowuserid_);
        return true;
    }
    else if (choice == 2) {
        regex phonereg("^[+]*[(]{0,1}[0-9]{1,4}[)]{0,1}[-\\s\\./0-9]*$");
        if (!regex_match(modifydata, phonereg)) {
            cout << "号码格式错误" << endl;
            return false;
        }
        sdb_->ParseSql("UPDATE user SET phoneNumber=" + modifydata + " WHERE userID=" + this->nowuserid_);
        return true;
    }
    else if (choice == 3) {
        sdb_->ParseSql("UPDATE user SET address=" + modifydata + " WHERE userID=" + this->nowuserid_);
        return true;
    }
    else if (choice == 4) {
        regex passwordreg("^[a-zA-Z0-9]{6,16}$");
        if (!regex_match(modifydata, passwordreg)) {
            cout << "密码格式错误" << endl;
            return false;
        }
        sdb_->ParseSql("UPDATE user SET password=" + modifydata + " WHERE userID=" + this->nowuserid_);
        return true;
    }
    else {
        return false;
    }
}

bool UserGeneral::Recharge(double money) {
    double nowmoney = sdb_->FindUserBalance(this->nowuserid_);
    sdb_->ParseSql("UPDATE user SET balance=" + to_string(nowmoney + money) + " WHERE userID=" + this->nowuserid_);
    ofstream outfile("data/recharge.txt", ios::app);
    outfile << this->nowuserid_ << " " << money << " " << TimeType2() << endl;
    outfile.close();
    return true;
}

void UserGeneral::ViewUserDetail() {
    cout << endl;
    PrintSymbolStar(40);
    cout << "用户名：" << sdb_->FindUsername(this->nowuserid_) << endl;
    cout << "联系方式: " << sdb_->FindUserPhone(this->nowuserid_) << endl;
    cout << "地址：" << sdb_->FindUserAddress(this->nowuserid_) << endl;
    cout << "余额：" << sdb_->CalculateBalance(this->nowuserid_) << endl;
    PrintSymbolStar(40);
    cout << endl;
    return;
}