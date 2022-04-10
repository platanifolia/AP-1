#include "simpledatabase.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "calculator.h"
#include "strhandle.h"
#include "utfwidth.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::istringstream;
using std::left;
using std::map;
using std::ofstream;
using std::string;
using std::to_string;
using std::vector;
using namespace std::filesystem;

SimpleDataBase::SimpleDataBase() {
    create_directory("data");
    LoadUser("data/user.txt");
    LoadItem("data/commodity.txt");
    LoadOrder("data/order.txt");
}

bool SimpleDataBase::LoadUser(const string& filename) {
    ifstream userfile(filename);
    if (!userfile) {
        ofstream userfile(filename);
        if (userfile)
            // userfile << "userID,username,password,phoneNumber,address,balance,userState";
            userfile << "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态";
        userfile.close();
        return false;
    }
    string line;
    getline(userfile, line);
    while (getline(userfile, line)) {
        vector< string > datatoken;
        StringSplit(line, datatoken, ",");
        UserInfo userinfotemp{ datatoken[1], datatoken[2], datatoken[3], datatoken[4], stod(datatoken[5]), datatoken[6] };
        user_[datatoken[0]] = userinfotemp;
    }
    userfile.close();
    return true;
}

bool SimpleDataBase::LoadItem(const string& filename) {
    ifstream itemfile(filename);
    if (!itemfile) {
        ofstream itemfile(filename);
        if (itemfile)
            // itemfile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state";
            itemfile << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态";
        itemfile.close();
        return false;
    }
    string line;
    getline(itemfile, line);
    while (getline(itemfile, line)) {
        vector< string > datatoken;
        StringSplit(line, datatoken, ",");
        ItemInfo iteminfotemp{ datatoken[1], stod(datatoken[2]), stoi(datatoken[3]), datatoken[4], datatoken[5], datatoken[6], datatoken[7] };
        item_[datatoken[0]] = iteminfotemp;
    }
    itemfile.close();
    return true;
}

bool SimpleDataBase::LoadOrder(const string& filename) {
    ifstream orderfile(filename);
    if (!orderfile) {
        ofstream orderfile(filename);
        if (orderfile)
            // orderfile << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
            orderfile << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID";
        orderfile.close();
        return false;
    }
    string line;
    getline(orderfile, line);
    while (getline(orderfile, line)) {
        vector< string > datatoken;
        StringSplit(line, datatoken, ",");
        OrderInfo orderinfotemp{ datatoken[1], stod(datatoken[2]), stoi(datatoken[3]), datatoken[4], datatoken[5], datatoken[6] };
        order_[datatoken[0]] = orderinfotemp;
    }
    orderfile.close();
    return true;
}

bool SimpleDataBase::SaveUser(const string& filename) {
    ofstream userfile(filename, ios::trunc);
    if (!userfile) {
        userfile.close();
        return false;
    }
    // userfile << "userID,username,password,phoneNumber,address,balance,userState";
    userfile << "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态";
    for (auto& user : user_) {
        userfile << endl
                 << user.first << ',' << user.second.username << ',' << user.second.password << ',' << user.second.telephone << ',' << user.second.address << ',' << user.second.balance << ','
                 << user.second.userstate;
    }
    userfile.close();
    return true;
}

bool SimpleDataBase::SaveItem(const string& filename) {
    ofstream itemfile(filename, ios::trunc);
    if (!itemfile) {
        itemfile.close();
        return false;
    }
    // itemfile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state";
    itemfile << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态";
    for (auto& item : item_) {
        itemfile << endl
                 << item.first << ',' << item.second.itemname << ',' << item.second.price << ',' << item.second.number << ',' << item.second.description << ',' << item.second.sellerid << ','
                 << item.second.addeddate << ',' << item.second.state;
    }
    itemfile.close();
    return true;
}

bool SimpleDataBase::SaveOrder(const string& filename) {
    ofstream orderfile(filename, ios::trunc);
    if (!orderfile) {
        orderfile.close();
        return false;
    }
    // orderfile << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
    orderfile << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID";
    for (auto& order : order_) {
        orderfile << endl
                  << order.first << ',' << order.second.itemid << ',' << order.second.unitprice << ',' << order.second.number << ',' << order.second.date << ',' << order.second.sellerid << ','
                  << order.second.buyerid;
    }
    orderfile.close();
    return true;
}

void SimpleDataBase::InsertUser(const string& insertdata) {
    string strtemp = insertdata;
    strtemp.erase(strtemp.begin());
    strtemp.pop_back();
    vector< string > datatoken;
    StringSplit(strtemp, datatoken, ",");
    if (datatoken.size() != 7) {
        cerr << "\033[91mInsert data error!\033[0m" << endl;
        return;
    }
    UserInfo userinfotemp{ datatoken[1], datatoken[2], datatoken[3], datatoken[4], stod(datatoken[5]), datatoken[6] };
    user_[datatoken[0]] = userinfotemp;
    SaveUser("data/user.txt");
}

void SimpleDataBase::InsertItem(const string& insertdata) {
    string strtemp = insertdata;
    strtemp.erase(strtemp.begin());
    strtemp.pop_back();
    vector< string > datatoken;
    StringSplit(strtemp, datatoken, ",");
    if (datatoken.size() != 8) {
        cerr << "\033[91mInsert data error!\033[0m" << endl;
        return;
    }
    ItemInfo iteminfotemp{ datatoken[1], stod(datatoken[2]), stoi(datatoken[3]), datatoken[4], datatoken[5], datatoken[6], datatoken[7] };
    item_[datatoken[0]] = iteminfotemp;
    SaveItem("data/commodity.txt");
}

void SimpleDataBase::InsertOrder(const string& insertdata) {
    string strtemp = insertdata;
    strtemp.erase(strtemp.begin());
    strtemp.pop_back();
    vector< string > datatoken;
    StringSplit(strtemp, datatoken, ",");
    if (datatoken.size() != 7) {
        cerr << "\033[91mInsert data error!\033[0m" << endl;
        return;
    }
    OrderInfo orderinfotemp{ datatoken[1], stod(datatoken[2]), stoi(datatoken[3]), datatoken[4], datatoken[5], datatoken[6] };
    order_[datatoken[0]] = orderinfotemp;
    SaveOrder("data/order.txt");
}

void SimpleDataBase::SelectUser(const std::string& column, const std::string& condition) {
    if (column == "" || condition == "") {
        for (auto& i : user_) {
            cout << left << setw_u8(8, i.first) << i.first;
            cout << left << setw_u8(10, i.second.username) << i.second.username;
            cout << left << setw_u8(18, i.second.password) << i.second.password;
            cout << left << setw_u8(15, i.second.telephone) << i.second.telephone;
            cout << left << setw_u8(15, i.second.address) << i.second.address;
            cout << left << setw(8) << i.second.balance;
            cout << left << setw_u8(8, i.second.userstate) << i.second.userstate;
            cout << endl;
        }
        return;
    }
    else if (column == "userID") {
        if (user_.find(condition) != user_.end()) {
            cout << left << setw_u8(8, condition) << condition;
            cout << left << setw_u8(10, user_[condition].username) << user_[condition].username;
            cout << left << setw_u8(18, user_[condition].password) << user_[condition].password;
            cout << left << setw_u8(15, user_[condition].telephone) << user_[condition].telephone;
            cout << left << setw_u8(15, user_[condition].address) << user_[condition].address;
            cout << left << setw(8) << user_[condition].balance;
            cout << left << setw_u8(8, user_[condition].userstate) << user_[condition].userstate;
            cout << endl;
            return;
        }
        else {
            cerr << "\033[91mNo such user!\033[0m" << endl;
            return;
        }
    }
    else if (column == "username") {
        for (auto& i : user_) {
            if (i.second.username == condition) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(10, i.second.username) << i.second.username;
                cout << left << setw_u8(18, i.second.password) << i.second.password;
                cout << left << setw_u8(15, i.second.telephone) << i.second.telephone;
                cout << left << setw_u8(15, i.second.address) << i.second.address;
                cout << left << setw(8) << i.second.balance;
                cout << left << setw_u8(8, i.second.userstate) << i.second.userstate;
                cout << endl;
                return;
            }
        }
        return;
    }
    else if (column == "password") {
        for (auto& i : user_) {
            if (i.second.password.find(condition) != string::npos) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(10, i.second.username) << i.second.username;
                cout << left << setw_u8(18, i.second.password) << i.second.password;
                cout << left << setw_u8(15, i.second.telephone) << i.second.telephone;
                cout << left << setw_u8(15, i.second.address) << i.second.address;
                cout << left << setw(8) << i.second.balance;
                cout << left << setw_u8(8, i.second.userstate) << i.second.userstate;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "phoneNumber") {
        for (auto& i : user_) {
            if (i.second.telephone.find(condition) != string::npos) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(10, i.second.username) << i.second.username;
                cout << left << setw_u8(18, i.second.password) << i.second.password;
                cout << left << setw_u8(15, i.second.telephone) << i.second.telephone;
                cout << left << setw_u8(15, i.second.address) << i.second.address;
                cout << left << setw(8) << i.second.balance;
                cout << left << setw_u8(8, i.second.userstate) << i.second.userstate;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "address") {
        for (auto& i : user_) {
            if (i.second.address.find(condition) != string::npos) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(10, i.second.username) << i.second.username;
                cout << left << setw_u8(18, i.second.password) << i.second.password;
                cout << left << setw_u8(15, i.second.telephone) << i.second.telephone;
                cout << left << setw_u8(15, i.second.address) << i.second.address;
                cout << left << setw(8) << i.second.balance;
                cout << left << setw_u8(8, i.second.userstate) << i.second.userstate;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "balance") {
        for (auto& i : user_) {
            if (i.second.balance == stod(condition)) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(10, i.second.username) << i.second.username;
                cout << left << setw_u8(18, i.second.password) << i.second.password;
                cout << left << setw_u8(15, i.second.telephone) << i.second.telephone;
                cout << left << setw_u8(15, i.second.address) << i.second.address;
                cout << left << setw(8) << i.second.balance;
                cout << left << setw_u8(8, i.second.userstate) << i.second.userstate;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "userState") {
        for (auto& i : user_) {
            if (i.second.userstate == condition) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(10, i.second.username) << i.second.username;
                cout << left << setw_u8(18, i.second.password) << i.second.password;
                cout << left << setw_u8(15, i.second.telephone) << i.second.telephone;
                cout << left << setw_u8(15, i.second.address) << i.second.address;
                cout << left << setw(8) << i.second.balance;
                cout << left << setw_u8(8, i.second.userstate) << i.second.userstate;
                cout << endl;
            }
        }
        return;
    }
    else {
        cerr << "\033[91mSelect user error!\033[0m" << endl;
        return;
    }
}

void SimpleDataBase::SelectItem(const std::string& column, const std::string& condition) {
    // int selectnum = 0;
    if (column == "" || condition == "") {
        for (auto& i : item_) {
            // selectnum += 1;
            cout << left << setw_u8(8, i.first) << i.first;
            cout << left << setw_u8(15, i.second.itemname) << i.second.itemname;
            cout << left << setw(12) << i.second.price;
            cout << left << setw(12) << i.second.number;
            cout << left << setw_u8(20, i.second.description) << i.second.description;
            cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
            cout << left << setw_u8(15, i.second.addeddate) << i.second.addeddate;
            cout << left << setw_u8(8, i.second.state) << i.second.state;
            cout << endl;
        }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        return;
    }
    else if (column == "commodityID") {
        if (item_.find(condition) != item_.end()) {
            cout << left << setw_u8(8, condition) << condition;
            cout << left << setw_u8(15, item_[condition].itemname) << item_[condition].itemname;
            cout << left << setw(12) << item_[condition].price;
            cout << left << setw(12) << item_[condition].number;
            cout << left << setw_u8(20, item_[condition].description) << item_[condition].description;
            cout << left << setw_u8(8, item_[condition].sellerid) << item_[condition].sellerid;
            cout << left << setw_u8(15, item_[condition].addeddate) << item_[condition].addeddate;
            cout << left << setw_u8(8, item_[condition].state) << item_[condition].state;
            cout << endl;
            return;
        }
        // else
        // {
        //     cerr << "No such item!" << endl;
        //     return;
        // }
    }
    else if (column == "commodityName") {
        for (auto& i : item_) {
            if (i.second.itemname.find(condition) != string::npos) {
                // selectnum += 1;
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(15, i.second.itemname) << i.second.itemname;
                cout << left << setw(12) << i.second.price;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(20, i.second.description) << i.second.description;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(15, i.second.addeddate) << i.second.addeddate;
                cout << left << setw_u8(8, i.second.state) << i.second.state;
                cout << endl;
            }
        }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        return;
    }
    else if (column == "price") {
        for (auto& i : item_) {
            if (i.second.price == stod(condition)) {
                // selectnum += 1;
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(15, i.second.itemname) << i.second.itemname;
                cout << left << setw(12) << i.second.price;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(20, i.second.description) << i.second.description;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(15, i.second.addeddate) << i.second.addeddate;
                cout << left << setw_u8(8, i.second.state) << i.second.state;
                cout << endl;
            }
        }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        return;
    }
    else if (column == "number") {
        for (auto& i : item_) {
            if (i.second.number == stoi(condition)) {
                // selectnum += 1;
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(15, i.second.itemname) << i.second.itemname;
                cout << left << setw(12) << i.second.price;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(20, i.second.description) << i.second.description;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(15, i.second.addeddate) << i.second.addeddate;
                cout << left << setw_u8(8, i.second.state) << i.second.state;
                cout << endl;
            }
        }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        return;
    }
    else if (column == "description") {
        for (auto& i : item_) {
            if (i.second.description.find(condition) != string::npos) {
                // selectnum += 1;
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(15, i.second.itemname) << i.second.itemname;
                cout << left << setw(12) << i.second.price;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(20, i.second.description) << i.second.description;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(15, i.second.addeddate) << i.second.addeddate;
                cout << left << setw_u8(8, i.second.state) << i.second.state;
                cout << endl;
            }
        }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        return;
    }
    else if (column == "sellerID") {
        for (auto& i : item_) {
            if (i.second.sellerid == condition) {
                // selectnum += 1;
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(15, i.second.itemname) << i.second.itemname;
                cout << left << setw(12) << i.second.price;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(20, i.second.description) << i.second.description;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(15, i.second.addeddate) << i.second.addeddate;
                cout << left << setw_u8(8, i.second.state) << i.second.state;
                cout << endl;
            }
        }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        return;
    }
    else if (column == "addedDate") {
        for (auto& i : item_) {
            if (i.second.addeddate.find(condition) != string::npos) {
                // selectnum += 1;
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(15, i.second.itemname) << i.second.itemname;
                cout << left << setw(12) << i.second.price;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(20, i.second.description) << i.second.description;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(15, i.second.addeddate) << i.second.addeddate;
                cout << left << setw_u8(8, i.second.state) << i.second.state;
                cout << endl;
            }
        }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        return;
    }
    else if (column == "state") {
        for (auto& i : item_) {
            if (i.second.state == condition) {
                // selectnum += 1;
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(15, i.second.itemname) << i.second.itemname;
                cout << left << setw(12) << i.second.price;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(20, i.second.description) << i.second.description;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(15, i.second.addeddate) << i.second.addeddate;
                cout << left << setw_u8(8, i.second.state) << i.second.state;
                cout << endl;
            }
        }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        return;
    }
    else {
        cerr << "\033[91mSelect commodity error!\033[0m" << endl;
        return;
    }
}

void SimpleDataBase::SelectOrder(const std::string& column, const std::string& condition) {
    if (column == "" || condition == "") {
        for (auto& i : order_) {
            cout << left << setw_u8(8, i.first) << i.first;
            cout << left << setw_u8(8, i.second.itemid) << i.second.itemid;
            cout << left << setw(12) << i.second.unitprice;
            cout << left << setw(12) << i.second.number;
            cout << left << setw_u8(15, i.second.date) << i.second.date;
            cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
            cout << left << setw_u8(8, i.second.buyerid) << i.second.buyerid;
            cout << endl;
        }
        return;
    }
    else if (column == "orderID") {
        if (order_.find(condition) != order_.end()) {
            cout << left << setw_u8(8, condition) << condition;
            cout << left << setw_u8(8, order_[condition].itemid) << order_[condition].itemid;
            cout << left << setw(12) << order_[condition].unitprice;
            cout << left << setw(12) << order_[condition].number;
            cout << left << setw_u8(15, order_[condition].date) << order_[condition].date;
            cout << left << setw_u8(8, order_[condition].sellerid) << order_[condition].sellerid;
            cout << left << setw_u8(8, order_[condition].buyerid) << order_[condition].buyerid;
            cout << endl;
            return;
        }
        else {
            cerr << "\033[91mNo such order!\033[0m" << endl;
            return;
        }
    }
    else if (column == "commodityID") {
        for (auto& i : order_) {
            if (i.second.itemid == condition) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(8, i.second.itemid) << i.second.itemid;
                cout << left << setw(12) << i.second.unitprice;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(15, i.second.date) << i.second.date;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(8, i.second.buyerid) << i.second.buyerid;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "unitPrice") {
        for (auto& i : order_) {
            if (i.second.unitprice == stod(condition)) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(8, i.second.itemid) << i.second.itemid;
                cout << left << setw(12) << i.second.unitprice;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(15, i.second.date) << i.second.date;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(8, i.second.buyerid) << i.second.buyerid;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "number") {
        for (auto& i : order_) {
            if (i.second.number == stoi(condition)) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(8, i.second.itemid) << i.second.itemid;
                cout << left << setw(12) << i.second.unitprice;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(15, i.second.date) << i.second.date;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(8, i.second.buyerid) << i.second.buyerid;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "date") {
        for (auto& i : order_) {
            if (i.second.date.find(condition) != string::npos) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(8, i.second.itemid) << i.second.itemid;
                cout << left << setw(12) << i.second.unitprice;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(15, i.second.date) << i.second.date;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(8, i.second.buyerid) << i.second.buyerid;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "sellerID") {
        for (auto& i : order_) {
            if (i.second.sellerid == condition) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(8, i.second.itemid) << i.second.itemid;
                cout << left << setw(12) << i.second.unitprice;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(15, i.second.date) << i.second.date;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(8, i.second.buyerid) << i.second.buyerid;
                cout << endl;
            }
        }
        return;
    }
    else if (column == "buyerID") {
        for (auto& i : order_) {
            if (i.second.buyerid == condition) {
                cout << left << setw_u8(8, i.first) << i.first;
                cout << left << setw_u8(8, i.second.itemid) << i.second.itemid;
                cout << left << setw(12) << i.second.unitprice;
                cout << left << setw(12) << i.second.number;
                cout << left << setw_u8(15, i.second.date) << i.second.date;
                cout << left << setw_u8(8, i.second.sellerid) << i.second.sellerid;
                cout << left << setw_u8(8, i.second.buyerid) << i.second.buyerid;
                cout << endl;
            }
        }
        return;
    }
    else {
        cerr << "\033[91mSelect order error!\033[0m" << endl;
        return;
    }
}

bool SimpleDataBase::UpdateUser(const std::string& updatedata, const std::string& condition) {
    vector< string > changevalue;
    StringSplit(updatedata, changevalue, ",");
    vector< string > conditionvalue;
    StringSplit(condition, conditionvalue, "=");
    if (conditionvalue.size() != 2) {
        cerr << "\033[91mUpdate user condition error!\033[0m" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为userID的情形
    if (conditionvalue[0] != "userID") {
        cerr << "\033[91mUpdate user condition error!\033[0m" << endl;
        return false;
    }

    for (string& i : changevalue) {
        vector< string > changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 2) {
            cerr << "\033[91mUpdate user data error 01\033[0m" << endl;
            return false;
        }
        if (changetemp[0] == "username") {
            user_[conditionvalue[1]].username = changetemp[1];
        }
        else if (changetemp[0] == "password") {
            user_[conditionvalue[1]].password = changetemp[1];
        }
        else if (changetemp[0] == "phoneNumber") {
            user_[conditionvalue[1]].telephone = changetemp[1];
        }
        else if (changetemp[0] == "address") {
            user_[conditionvalue[1]].address = changetemp[1];
        }
        else if (changetemp[0] == "balance") {
            user_[conditionvalue[1]].balance = stod(changetemp[1]);
        }
        else if (changetemp[0] == "userState") {
            user_[conditionvalue[1]].userstate = changetemp[1];
        }
        else {
            cerr << "\033[91mUpdate user data error 02\033[0m" << endl;
            return false;
        }
    }
    SaveUser("data/user.txt");
    return true;
}

bool SimpleDataBase::UpdateItem(const std::string& updatedata, const std::string& condition) {
    vector< string > changevalue;
    StringSplit(updatedata, changevalue, ",");
    vector< string > conditionvalue;
    StringSplit(condition, conditionvalue, "=");
    if (conditionvalue.size() != 2) {
        cerr << "\033[91mUpdate item condition error!\033[0m" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为itemID的情形
    if (conditionvalue[0] != "commodityID") {
        cerr << "\033[91mUpdate item condition error!\033[0m" << endl;
        return false;
    }

    for (string& i : changevalue) {
        vector< string > changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 2) {
            cerr << "\033[91mUpdate item data error!\033[0m" << endl;
            return false;
        }
        if (changetemp[0] == "commodityName") {
            item_[conditionvalue[1]].itemname = changetemp[1];
        }
        else if (changetemp[0] == "price") {
            item_[conditionvalue[1]].price = stod(changetemp[1]);
        }
        else if (changetemp[0] == "number") {
            item_[conditionvalue[1]].number = stoi(changetemp[1]);
        }
        else if (changetemp[0] == "description") {
            item_[conditionvalue[1]].description = changetemp[1];
        }
        else if (changetemp[0] == "sellerID") {
            item_[conditionvalue[1]].sellerid = changetemp[1];
        }
        else if (changetemp[0] == "addedDate") {
            item_[conditionvalue[1]].addeddate = changetemp[1];
        }
        else if (changetemp[0] == "state") {
            item_[conditionvalue[1]].state = changetemp[1];
        }
        else {
            cerr << "\033[91mUpdate item data error!\033[0m" << endl;
            return false;
        }
    }
    SaveItem("data/commodity.txt");
    return true;
}

bool SimpleDataBase::UpdateOrder(const std::string& updatedata, const std::string& condition) {
    vector< string > changevalue;
    StringSplit(updatedata, changevalue, ",");
    vector< string > conditionvalue;
    StringSplit(condition, conditionvalue, "=");
    if (conditionvalue.size() != 2) {
        cerr << "\033[91mUpdate order condition error!\033[0m" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为orderID的情形
    if (conditionvalue[0] != "orderID") {
        cerr << "\033[91mUpdate order condition error!\033[0m" << endl;
        return false;
    }

    for (string& i : changevalue) {
        vector< string > changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 2) {
            cerr << "\033[91mUpdate order data error!\033[0m" << endl;
            return false;
        }
        if (changetemp[0] == "commodityID") {
            order_[conditionvalue[1]].itemid = changetemp[1];
        }
        else if (changetemp[0] == "unitPrice") {
            order_[conditionvalue[1]].unitprice = stod(changetemp[1]);
        }
        else if (changetemp[0] == "number") {
            order_[conditionvalue[1]].number = stoi(changetemp[1]);
        }
        else if (changetemp[0] == "date") {
            order_[conditionvalue[1]].date = changetemp[1];
        }
        else if (changetemp[0] == "sellerID") {
            order_[conditionvalue[1]].sellerid = changetemp[1];
        }
        else if (changetemp[0] == "buyerID") {
            order_[conditionvalue[1]].buyerid = changetemp[1];
        }
        else {
            cerr << "\033[91mUpdate order data error!\033[0m" << endl;
            return false;
        }
    }
    SaveOrder("data/order.txt");
    return true;
}

int SimpleDataBase::ParseSql(const string& sql) {
    LogFile(sql);
    vector< string > sqltokens;
    StringSplit(sql, sqltokens, " ");
    if (sqltokens[0] == "INSERT" && sqltokens[1] == "INTO" && sqltokens[3] == "VALUES") {
        if (sqltokens[2] == "user") {
            InsertUser(sqltokens[4]);
            return 1;
        }
        else if (sqltokens[2] == "commodity") {
            InsertItem(sqltokens[4]);
            return 2;
        }
        else if (sqltokens[2] == "order") {
            InsertOrder(sqltokens[4]);
            return 3;
        }
    }
    else if (sqltokens[0] == "SELECT" && sqltokens[1] == "*" && sqltokens[2] == "FROM") {
        if (sqltokens.size() == 4) {
            if (sqltokens[3] == "user") {
                SelectUser();
                return 4;
            }
            else if (sqltokens[3] == "commodity") {
                SelectItem();
                return 5;
            }
            else if (sqltokens[3] == "order") {
                SelectOrder();
                return 6;
            }
            else {
                cerr << "\033[91mSelect data error!\033[0m" << endl;
                return 0;
            }
        }
        else if (sqltokens.size() == 8 && sqltokens[6] == "CONTAINS") {
            if (sqltokens[3] == "user") {
                SelectUser(sqltokens[5], sqltokens[7]);
                return 4;
            }
            else if (sqltokens[3] == "commodity") {
                SelectItem(sqltokens[5], sqltokens[7]);
                return 5;
            }
            else if (sqltokens[3] == "order") {
                SelectOrder(sqltokens[5], sqltokens[7]);
                return 6;
            }
            else {
                cerr << "\033[91mSelect data error!\033[0m" << endl;
                return 0;
            }
        }
    }
    else if (sqltokens[0] == "UPDATE" && sqltokens[2] == "SET" && sqltokens[4] == "WHERE") {
        if (sqltokens[1] == "user") {
            UpdateUser(sqltokens[3], sqltokens[5]);
            return 7;
        }
        else if (sqltokens[1] == "commodity") {
            UpdateItem(sqltokens[3], sqltokens[5]);
            return 8;
        }
        else if (sqltokens[1] == "order") {
            UpdateOrder(sqltokens[3], sqltokens[5]);
            return 9;
        }
    }
    else {
        cerr << "\033[91mSql error!\033[0m" << endl;
        return 0;
    }
    return 0;
}

bool SimpleDataBase::LogFile(string sql) {
    ofstream logfile("./commands.txt", ios::app);
    if (!logfile) {
        logfile.close();
        return false;
    }
    logfile << endl << TimeType1() << ": " << sql;
    logfile.close();
    return true;
}

bool SimpleDataBase::UsernameExist(const string& username) {
    for (auto& i : user_) {
        if (i.second.username == username) {
            return true;
        }
    }
    return false;
}

string SimpleDataBase::FindUserid(const string& username) {
    for (auto& i : user_) {
        if (i.second.username == username) {
            return i.first;
        }
    }
    return "";
}

string SimpleDataBase::FindUsername(const string& userid) {
    if (user_.find(userid) == user_.end()) {
        return "";
    }
    return user_[userid].username;
}

string SimpleDataBase::FindUserPhone(const string& userid) {
    if (user_.find(userid) == user_.end()) {
        return "";
    }
    return user_[userid].telephone;
}

string SimpleDataBase::FindUserAddress(const string& userid) {
    if (user_.find(userid) == user_.end()) {
        return "";
    }
    return user_[userid].address;
}

bool SimpleDataBase::UserVerification(const string& username, const string& password) {
    for (auto& i : user_) {
        if (i.second.username == username && i.second.password == password) {
            return true;
        }
    }
    return false;
}

bool SimpleDataBase::UserNotBan(const string& userid) {
    if (user_.find(userid) != user_.end())
        return user_[userid].userstate == "正常";
    return false;
}

string SimpleDataBase::GetNewUserid() {
    int newuser = user_.size() + 1;
    if (newuser < 10) {
        return "U00" + to_string(newuser);
    }
    else if (newuser < 100) {
        return "U0" + to_string(newuser);
    }
    else {
        return "U" + to_string(newuser);
    }
}

string SimpleDataBase::GetNewItemid() {
    int newitem = item_.size() + 1;
    if (newitem < 10) {
        return "M00" + to_string(newitem);
    }
    else if (newitem < 100) {
        return "M0" + to_string(newitem);
    }
    else {
        return "M" + to_string(newitem);
    }
}

string SimpleDataBase::GetNewOrderid() {
    int neworder = order_.size() + 1;
    if (neworder < 10) {
        return "T00" + to_string(neworder);
    }
    else if (neworder < 100) {
        return "T0" + to_string(neworder);
    }
    else {
        return "T" + to_string(neworder);
    }
}

void SimpleDataBase::ViewItemDetail(const string& itemid) {
    if (item_.find(itemid) == item_.end()) {
        cerr << "\033[91mItem not found!\033[0m" << endl;
        return;
    }
    cout << string(30, '*') << endl;
    cout << "商品 ID: " << itemid << endl;
    cout << "商品 名称: " << item_[itemid].itemname << endl;
    cout << "商品 价格: " << item_[itemid].price << endl;
    cout << "商品 描述: " << item_[itemid].description << endl;
    cout << "上架 时间: " << item_[itemid].addeddate << endl;
    cout << "商品 卖家: " << item_[itemid].sellerid << endl;
    cout << string(30, '*') << endl;
}

double SimpleDataBase::FindUserBalance(const string& userid) {
    if (user_.find(userid) == user_.end()) {
        cerr << "\033[91mUser not found!\033[0m" << endl;
        return -1;
    }
    return user_[userid].balance;
}

int SimpleDataBase::GetItemNumber(const string& itemid) {
    if (item_.find(itemid) == item_.end()) {
        cerr << "\033[91mItem not found!\033[0m" << endl;
        return -1;
    }
    return item_[itemid].number;
}

double SimpleDataBase::GetItemPrice(const string& itemid) {
    if (item_.find(itemid) == item_.end()) {
        cerr << "\033[91mItem not found!\033[0m" << endl;
        return -1;
    }
    return item_[itemid].price;
}

string SimpleDataBase::GetItemSellerid(const string& itemid) {
    if (item_.find(itemid) == item_.end()) {
        cerr << "\033[91mItem not found!\033[0m" << endl;
        return "";
    }
    return item_[itemid].sellerid;
}

bool SimpleDataBase::ItemNotDown(const string& itemid) {
    if (item_.find(itemid) == item_.end()) {
        cerr << "\033[91mItem not found!\033[0m" << endl;
        return false;
    }
    return item_[itemid].state == "销售中";
}

bool SimpleDataBase::ItemExist(const string& itemid) {
    if (item_.find(itemid) == item_.end()) {
        return false;
    }
    return true;
}

double SimpleDataBase::CalculateBalance(const string& userid) {
    string   expression = "";
    ifstream recharge("data/recharge.txt");
    string   line;
    while (getline(recharge, line)) {
        if (line == "")
            continue;
        istringstream iss(line);
        string        usid;
        string        money;
        string        data;
        iss >> usid >> money >> data;
        if (usid == userid)
            expression += " + " + money;
    }
    recharge.close();
    expression.erase(0, 3);
    map< int, vector< double > > link;
    for (auto& i : order_) {
        if (i.second.sellerid == userid) {
            link[i.second.number].push_back(i.second.unitprice);
        }
        if (i.second.buyerid == userid) {
            link[i.second.number].push_back(-i.second.unitprice);
        }
    }
    for (auto& i : link) {
        expression += " + " + to_string(i.first) + " * " + Array2Expr(i.second);
    }
    if (expression[0] == ' ' && expression[1] == '+')
        expression.erase(0, 3);
    Evaluator evaluator(expression);
    return evaluator.Calculate();
}