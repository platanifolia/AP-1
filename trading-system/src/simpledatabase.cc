#include "simpledatabase.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "strhandle.h"
#include "calculator.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::istringstream;
using std::map;
using std::ofstream;
using std::string;
using std::to_string;
using std::vector;
using namespace std::filesystem;

SimpleDataBase::SimpleDataBase()
{
    create_directory("data");
    LoadUser("data/user.txt");
    LoadItem("data/commodity.txt");
    LoadOrder("data/order.txt");
}

bool SimpleDataBase::LoadUser(const string &filename)
{
    ifstream userfile(filename);
    if (!userfile)
    {
        ofstream userfile(filename);
        if (userfile)
            userfile << "userID,username,password,phoneNumber,address,balance,userState";
        userfile.close();
        return false;
    }
    string line;
    getline(userfile, line);
    while (getline(userfile, line))
    {
        vector<string> datatoken;
        StringSplit(line, datatoken, ",");
        UserInfo userinfotemp{datatoken[1], datatoken[2], datatoken[3], datatoken[4], stod(datatoken[5]), datatoken[6]};
        user_[datatoken[0]] = userinfotemp;
    }
    userfile.close();
    return true;
}

bool SimpleDataBase::LoadItem(const string &filename)
{
    ifstream itemfile(filename);
    if (!itemfile)
    {
        ofstream itemfile(filename);
        if (itemfile)
            itemfile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state";
        itemfile.close();
        return false;
    }
    string line;
    getline(itemfile, line);
    while (getline(itemfile, line))
    {
        vector<string> datatoken;
        StringSplit(line, datatoken, ",");
        ItemInfo iteminfotemp{datatoken[1], stod(datatoken[2]), stoi(datatoken[3]), datatoken[4], datatoken[5], datatoken[6], datatoken[7]};
        item_[datatoken[0]] = iteminfotemp;
    }
    itemfile.close();
    return true;
}

bool SimpleDataBase::LoadOrder(const string &filename)
{
    ifstream orderfile(filename);
    if (!orderfile)
    {
        ofstream orderfile(filename);
        if (orderfile)
            orderfile << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
        orderfile.close();
        return false;
    }
    string line;
    getline(orderfile, line);
    while (getline(orderfile, line))
    {
        vector<string> datatoken;
        StringSplit(line, datatoken, ",");
        OrderInfo orderinfotemp{datatoken[1], stod(datatoken[2]), stoi(datatoken[3]), datatoken[4], datatoken[5], datatoken[6]};
        order_[datatoken[0]] = orderinfotemp;
    }
    orderfile.close();
    return true;
}

bool SimpleDataBase::SaveUser(const string &filename)
{
    ofstream userfile(filename, ios::trunc);
    if (!userfile)
    {
        userfile.close();
        return false;
    }
    userfile << "userID,username,password,phoneNumber,address,balance,userState";
    for (auto &user : user_)
    {
        userfile << endl
                 << user.first << ',' << user.second.username << ',' << user.second.password << ','
                 << user.second.telephone << ',' << user.second.address << ',' << user.second.balance << ','
                 << user.second.userstate;
    }
    userfile.close();
    return true;
}

bool SimpleDataBase::SaveItem(const string &filename)
{
    ofstream itemfile(filename, ios::trunc);
    if (!itemfile)
    {
        itemfile.close();
        return false;
    }
    itemfile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state";
    for (auto &item : item_)
    {
        itemfile << endl
                 << item.first << ',' << item.second.itemname << ',' << item.second.price << ',' << item.second.number
                 << ',' << item.second.description << ',' << item.second.sellerid << ',' << item.second.addeddate << ','
                 << item.second.state;
    }
    itemfile.close();
    return true;
}

bool SimpleDataBase::SaveOrder(const string &filename)
{
    ofstream orderfile(filename, ios::trunc);
    if (!orderfile)
    {
        orderfile.close();
        return false;
    }
    orderfile << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
    for (auto &order : order_)
    {
        orderfile << endl
                  << order.first << ',' << order.second.itemid << ',' << order.second.unitprice << ',' << order.second.number
                  << ',' << order.second.date << ',' << order.second.sellerid << ',' << order.second.buyerid;
    }
    orderfile.close();
    return true;
}

void SimpleDataBase::InsertUser(const string &insertdata)
{
    string strtemp = insertdata;
    strtemp.erase(strtemp.begin());
    strtemp.pop_back();
    vector<string> datatoken;
    StringSplit(strtemp, datatoken, ",");
    if (datatoken.size() != 7)
    {
        cerr << "Insert data error!" << endl;
        return;
    }
    UserInfo userinfotemp{datatoken[1], datatoken[2], datatoken[3], datatoken[4], stod(datatoken[5]), datatoken[6]};
    user_[datatoken[0]] = userinfotemp;
    SaveUser("data/user.txt");
}

void SimpleDataBase::InsertItem(const string &insertdata)
{
    string strtemp = insertdata;
    strtemp.erase(strtemp.begin());
    strtemp.pop_back();
    vector<string> datatoken;
    StringSplit(strtemp, datatoken, ",");
    if (datatoken.size() != 8)
    {
        cerr << "Insert data error!" << endl;
        return;
    }
    ItemInfo iteminfotemp{datatoken[1], stod(datatoken[2]), stoi(datatoken[3]), datatoken[4], datatoken[5], datatoken[6], datatoken[7]};
    item_[datatoken[0]] = iteminfotemp;
    SaveItem("data/commodity.txt");
}

void SimpleDataBase::InsertOrder(const string &insertdata)
{
    string strtemp = insertdata;
    strtemp.erase(strtemp.begin());
    strtemp.pop_back();
    vector<string> datatoken;
    StringSplit(strtemp, datatoken, ",");
    if (datatoken.size() != 7)
    {
        cerr << "Insert data error!" << endl;
        return;
    }
    OrderInfo orderinfotemp{datatoken[1], stod(datatoken[2]), stoi(datatoken[3]), datatoken[4], datatoken[5], datatoken[6]};
    order_[datatoken[0]] = orderinfotemp;
    SaveOrder("data/order.txt");
}

void SimpleDataBase::SelectUser(const std::string &column, const std::string &condition)
{
    if (column == "" || condition == "")
    {
        for (auto &i : user_)
        {
            cout << i.first << " " << i.second.username << " " << i.second.password << " "
                 << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                 << i.second.userstate << endl;
        }
        return;
    }
    else if (column == "userID")
    {
        // for (auto &i : user_)
        // {
        //     if (i.first.find(condition) != string::npos)
        //     {
        //         cout << i.first << " " << i.second.username << " " << i.second.password << " "
        //              << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
        //              << i.second.userstate << endl;
        //     }
        // }
        // return;
        if (user_.find(condition) != user_.end())
        {
            cout << condition
                 << user_[condition].username << " " << user_[condition].password << " "
                 << user_[condition].telephone << " " << user_[condition].address << " "
                 << user_[condition].balance << " " << user_[condition].userstate << endl;
            return;
        }
        else
        {
            cerr << "No such user!" << endl;
            return;
        }
    }
    else if (column == "username")
    {
        for (auto &i : user_)
        {
            if (i.second.username == condition)
            {
                cout << i.first << " " << i.second.username << " " << i.second.password << " "
                     << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                     << i.second.userstate << endl;
                return;
            }
        }
        return;
    }
    else if (column == "password")
    {
        for (auto &i : user_)
        {
            if (i.second.password.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.username << " " << i.second.password << " "
                     << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                     << i.second.userstate << endl;
            }
        }
        return;
    }
    else if (column == "phoneNumber")
    {
        for (auto &i : user_)
        {
            if (i.second.telephone.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.username << " " << i.second.password << " "
                     << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                     << i.second.userstate << endl;
            }
        }
        return;
    }
    else if (column == "address")
    {
        for (auto &i : user_)
        {
            if (i.second.address.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.username << " " << i.second.password << " "
                     << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                     << i.second.userstate << endl;
            }
        }
        return;
    }
    else if (column == "balance")
    {
        for (auto &i : user_)
        {
            if (i.second.balance == stod(condition))
            {
                cout << i.first << " " << i.second.username << " " << i.second.password << " "
                     << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                     << i.second.userstate << endl;
            }
        }
        return;
    }
    else if (column == "userState")
    {
        for (auto &i : user_)
        {
            if (i.second.userstate == condition)
            {
                cout << i.first << " " << i.second.username << " " << i.second.password << " "
                     << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                     << i.second.userstate << endl;
            }
        }
        return;
    }
    else
    {
        cerr << "Select user error!" << endl;
        return;
    }
}

void SimpleDataBase::SelectItem(const std::string &column, const std::string &condition)
{
    int selectnum = 0;
    if (column == "" || condition == "")
    {
        for (auto &i : item_)
        {
            selectnum += 1;
            cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                 << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                 << i.second.addeddate << " " << i.second.state << endl;
        }
        if (selectnum == 0)
            cout << "No item!" << endl;
        return;
    }
    else if (column == "commodityID")
    {
        // for (auto &i : item_)
        // {
        //     if (i.first == condition)
        //     {
        //         selectnum += 1;
        //         cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
        //              << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
        //              << i.second.addeddate << " " << i.second.state << endl;
        //     }
        // }
        // if (selectnum == 0)
        //     cout << "No item!" << endl;
        // return;
        if (item_.find(condition) != item_.end())
        {
            cout << condition
                 << item_[condition].itemname << " " << item_[condition].price << " "
                 << item_[condition].number << " " << item_[condition].description << " "
                 << item_[condition].sellerid << " " << item_[condition].addeddate << " "
                 << item_[condition].state << endl;
            return;
        }
        else
        {
            cerr << "No such item!" << endl;
            return;
        }
    }
    else if (column == "commodityName")
    {
        for (auto &i : item_)
        {
            if (i.second.itemname.find(condition) != string::npos)
            {
                selectnum += 1;
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        if (selectnum == 0)
            cout << "No item!" << endl;
        return;
    }
    else if (column == "price")
    {
        for (auto &i : item_)
        {
            if (i.second.price == stod(condition))
            {
                selectnum += 1;
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        if (selectnum == 0)
            cout << "No item!" << endl;
        return;
    }
    else if (column == "number")
    {
        for (auto &i : item_)
        {
            if (i.second.number == stoi(condition))
            {
                selectnum += 1;
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        if (selectnum == 0)
            cout << "No item!" << endl;
        return;
    }
    else if (column == "description")
    {
        for (auto &i : item_)
        {
            if (i.second.description.find(condition) != string::npos)
            {
                selectnum += 1;
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        if (selectnum == 0)
            cout << "No item!" << endl;
        return;
    }
    else if (column == "sellerID")
    {
        for (auto &i : item_)
        {
            if (i.second.sellerid == condition)
            {
                selectnum += 1;
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        if (selectnum == 0)
            cout << "No item!" << endl;
        return;
    }
    else if (column == "addedDate")
    {
        for (auto &i : item_)
        {
            if (i.second.addeddate.find(condition) != string::npos)
            {
                selectnum += 1;
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        if (selectnum == 0)
            cout << "No item!" << endl;
        return;
    }
    else if (column == "state")
    {
        for (auto &i : item_)
        {
            if (i.second.state == condition)
            {
                selectnum += 1;
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        if (selectnum == 0)
            cout << "No item!" << endl;
        return;
    }
    else
    {
        cerr << "Select commodity error!" << endl;
        return;
    }
}

void SimpleDataBase::SelectOrder(const std::string &column, const std::string &condition)
{
    if (column == "" || condition == "")
    {
        for (auto &i : order_)
        {
            cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
                 << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
                 << i.second.buyerid << endl;
        }
        return;
    }
    else if (column == "orderID")
    {
        // for (auto &i : order_)
        // {
        //     if (i.first.find(condition) != string::npos)
        //     {
        //         cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
        //              << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
        //              << i.second.buyerid << endl;
        //     }
        // }
        // return;
        if (order_.find(condition) != order_.end())
        {
            cout << condition
                 << order_[condition].itemid << " " << order_[condition].unitprice << " "
                 << order_[condition].number << " " << order_[condition].date << " "
                 << order_[condition].sellerid << " " << order_[condition].buyerid << endl;
            return;
        }
        else
        {
            cerr << "No such order!" << endl;
            return;
        }
    }
    else if (column == "commodityID")
    {
        for (auto &i : order_)
        {
            if (i.second.itemid == condition)
            {
                cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
                     << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
                     << i.second.buyerid << endl;
            }
        }
        return;
    }
    else if (column == "unitPrice")
    {
        for (auto &i : order_)
        {
            if (i.second.unitprice == stod(condition))
            {
                cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
                     << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
                     << i.second.buyerid << endl;
            }
        }
        return;
    }
    else if (column == "number")
    {
        for (auto &i : order_)
        {
            if (i.second.number == stoi(condition))
            {
                cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
                     << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
                     << i.second.buyerid << endl;
            }
        }
        return;
    }
    else if (column == "date")
    {
        for (auto &i : order_)
        {
            if (i.second.date.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
                     << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
                     << i.second.buyerid << endl;
            }
        }
        return;
    }
    else if (column == "sellerID")
    {
        for (auto &i : order_)
        {
            if (i.second.sellerid == condition)
            {
                cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
                     << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
                     << i.second.buyerid << endl;
            }
        }
        return;
    }
    else if (column == "buyerID")
    {
        for (auto &i : order_)
        {
            if (i.second.buyerid == condition)
            {
                cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
                     << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
                     << i.second.buyerid << endl;
            }
        }
        return;
    }
    else
    {
        cerr << "Select order error!" << endl;
        return;
    }
}

bool SimpleDataBase::UpdateUser(const std::string &updatedata, const std::string &condition)
{
    vector<string> changevalue;
    StringSplit(updatedata, changevalue, ",");
    vector<string> conditionvalue;
    StringSplit(condition, conditionvalue, "=");
    if (conditionvalue.size() != 2)
    {
        cerr << "Update user condition error!" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为userID的情形
    if (conditionvalue[0] != "userID")
    {
        cerr << "Update user condition error!" << endl;
        return false;
    }

    for (string &i : changevalue)
    {
        vector<string> changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 2)
        {
            cerr << "Update user data error!" << endl;
            return false;
        }
        if (changetemp[0] == "username")
        {
            // TOFIX: 更新username使之不重复
            user_[conditionvalue[1]].username = changetemp[1];
        }
        else if (changetemp[0] == "password")
        {
            user_[conditionvalue[1]].password = changetemp[1];
        }
        else if (changetemp[0] == "phoneNumber")
        {
            user_[conditionvalue[1]].telephone = changetemp[1];
        }
        else if (changetemp[0] == "address")
        {
            user_[conditionvalue[1]].address = changetemp[1];
        }
        else if (changetemp[0] == "balance")
        {
            user_[conditionvalue[1]].balance = stod(changetemp[1]);
        }
        else if (changetemp[0] == "userState")
        {
            user_[conditionvalue[1]].userstate = changetemp[1];
        }
        else
        {
            cerr << "Update user data error!" << endl;
            return false;
        }
    }
    SaveUser("data/user.txt");
    return true;
}

bool SimpleDataBase::UpdateItem(const std::string &updatedata, const std::string &condition)
{
    vector<string> changevalue;
    StringSplit(updatedata, changevalue, ",");
    vector<string> conditionvalue;
    StringSplit(condition, conditionvalue, "=");
    if (conditionvalue.size() != 2)
    {
        cerr << "Update item condition error!" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为itemID的情形
    if (conditionvalue[0] != "commodityID")
    {
        cerr << "Update item condition error!" << endl;
        return false;
    }

    for (string &i : changevalue)
    {
        vector<string> changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 2)
        {
            cerr << "Update item data error!" << endl;
            return false;
        }
        if (changetemp[0] == "commodityName")
        {
            item_[conditionvalue[1]].itemname = changetemp[1];
        }
        else if (changetemp[0] == "price")
        {
            item_[conditionvalue[1]].price = stoi(changetemp[1]);
        }
        else if (changetemp[0] == "number")
        {
            item_[conditionvalue[1]].number = stoi(changetemp[1]);
        }
        else if (changetemp[0] == "description")
        {
            item_[conditionvalue[1]].description = stoi(changetemp[1]);
        }
        else if (changetemp[0] == "sellerID")
        {
            item_[conditionvalue[1]].sellerid = changetemp[1];
        }
        else if (changetemp[0] == "addedDate")
        {
            item_[conditionvalue[1]].addeddate = changetemp[1];
        }
        else if (changetemp[0] == "state")
        {
            item_[conditionvalue[1]].state = changetemp[1];
        }
        else
        {
            cerr << "Update item data error!" << endl;
            return false;
        }
    }
    SaveItem("data/commodity.txt");
    return true;
}

bool SimpleDataBase::UpdateOrder(const std::string &updatedata, const std::string &condition)
{
    vector<string> changevalue;
    StringSplit(updatedata, changevalue, ",");
    vector<string> conditionvalue;
    StringSplit(condition, conditionvalue, "=");
    if (conditionvalue.size() != 2)
    {
        cerr << "Update order condition error!" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为orderID的情形
    if (conditionvalue[0] != "orderID")
    {
        cerr << "Update order condition error!" << endl;
        return false;
    }

    for (string &i : changevalue)
    {
        vector<string> changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 2)
        {
            cerr << "Update order data error!" << endl;
            return false;
        }
        if (changetemp[0] == "commodityID")
        {
            order_[conditionvalue[1]].itemid = changetemp[1];
        }
        else if (changetemp[0] == "unitPrice")
        {
            order_[conditionvalue[1]].unitprice = stod(changetemp[1]);
        }
        else if (changetemp[0] == "number")
        {
            order_[conditionvalue[1]].number = stoi(changetemp[1]);
        }
        else if (changetemp[0] == "date")
        {
            order_[conditionvalue[1]].date = changetemp[1];
        }
        else if (changetemp[0] == "sellerID")
        {
            order_[conditionvalue[1]].sellerid = changetemp[1];
        }
        else if (changetemp[0] == "buyerID")
        {
            order_[conditionvalue[1]].buyerid = changetemp[1];
        }
        else
        {
            cerr << "Update order data error!" << endl;
            return false;
        }
    }
    SaveOrder("data/order.txt");
    return true;
}

int SimpleDataBase::ParseSql(const string &sql)
{
    LogFile(sql);
    vector<string> sqltokens;
    StringSplit(sql, sqltokens, " ");
    if (sqltokens[0] == "INSERT" && sqltokens[1] == "INTO" && sqltokens[3] == "VALUES")
    {
        if (sqltokens[2] == "user")
        {
            InsertUser(sqltokens[4]);
            return 1;
        }
        else if (sqltokens[2] == "commodity")
        {
            InsertItem(sqltokens[4]);
            return 2;
        }
        else if (sqltokens[2] == "order")
        {
            InsertOrder(sqltokens[4]);
            return 3;
        }
    }
    else if (sqltokens[0] == "SELECT" && sqltokens[1] == "*" && sqltokens[2] == "FROM")
    {
        if (sqltokens.size() == 4)
        {
            if (sqltokens[3] == "user")
            {
                SelectUser();
                return 4;
            }
            else if (sqltokens[3] == "commodity")
            {
                SelectItem();
                return 5;
            }
            else if (sqltokens[3] == "order")
            {
                SelectOrder();
                return 6;
            }
            else
            {
                cerr << "Select data error!" << endl;
                return 0;
            }
        }
        else if (sqltokens.size() == 8 && sqltokens[6] == "CONTAINS")
        {
            if (sqltokens[3] == "user")
            {
                SelectUser(sqltokens[5], sqltokens[7]);
                return 4;
            }
            else if (sqltokens[3] == "commodity")
            {
                SelectItem(sqltokens[5], sqltokens[7]);
                return 5;
            }
            else if (sqltokens[3] == "order")
            {
                SelectOrder(sqltokens[5], sqltokens[7]);
                return 6;
            }
            else
            {
                cerr << "Select data error!" << endl;
                return 0;
            }
        }
    }
    else if (sqltokens[0] == "UPDATE" && sqltokens[2] == "SET" && sqltokens[4] == "WHERE")
    {
        if (sqltokens[1] == "user")
        {
            UpdateUser(sqltokens[3], sqltokens[5]);
            return 7;
        }
        else if (sqltokens[1] == "commodity")
        {
            UpdateItem(sqltokens[3], sqltokens[5]);
            return 8;
        }
        else if (sqltokens[1] == "order")
        {
            UpdateOrder(sqltokens[3], sqltokens[5]);
            return 9;
        }
    }
    else
    {
        cerr << "Sql error!" << endl;
        return 0;
    }
    return 0;
}

bool SimpleDataBase::LogFile(string sql)
{
    ofstream logfile("./commands.txt", ios::app);
    if (!logfile)
    {
        logfile.close();
        return false;
    }
    logfile << endl
            << TimeType1() << ": " << sql;
    logfile.close();
    return true;
}

bool SimpleDataBase::UsernameExist(const string &username)
{
    for (auto &i : user_)
    {
        if (i.second.username == username)
        {
            return true;
        }
    }
    return false;
}

string SimpleDataBase::FindUserid(const string &username)
{
    for (auto &i : user_)
    {
        if (i.second.username == username)
        {
            return i.first;
        }
    }
    return "";
}

string SimpleDataBase::FindUsername(const string &userid)
{
    if (user_.find(userid) == user_.end())
    {
        return "";
    }
    return user_[userid].username;
}

string SimpleDataBase::FindUserPhone(const string &userid)
{
    if (user_.find(userid) == user_.end())
    {
        return "";
    }
    return user_[userid].telephone;
}

string SimpleDataBase::FindUserAddress(const string &userid)
{
    if (user_.find(userid) == user_.end())
    {
        return "";
    }
    return user_[userid].address;
}

bool SimpleDataBase::UserVerification(const string &username, const string &password)
{
    for (auto &i : user_)
    {
        if (i.second.username == username && i.second.password == password)
        {
            return true;
        }
    }
    return false;
}

string SimpleDataBase::GetNewUserid()
{
    int newuser = user_.size() + 1;
    if (newuser < 10)
    {
        return "U00" + to_string(newuser);
    }
    else if (newuser < 100)
    {
        return "U0" + to_string(newuser);
    }
    else
    {
        return "U" + to_string(newuser);
    }
}

string SimpleDataBase::GetNewItemid()
{
    int newitem = item_.size() + 1;
    if (newitem < 10)
    {
        return "M00" + to_string(newitem);
    }
    else if (newitem < 100)
    {
        return "M0" + to_string(newitem);
    }
    else
    {
        return "M" + to_string(newitem);
    }
}

string SimpleDataBase::GetNewOrderid()
{
    int neworder = order_.size() + 1;
    if (neworder < 10)
    {
        return "T00" + to_string(neworder);
    }
    else if (neworder < 100)
    {
        return "T0" + to_string(neworder);
    }
    else
    {
        return "T" + to_string(neworder);
    }
}

// string SimpleDataBase::GetItemOwner(const std::string &itemid)
// {
//     if (item_.find(itemid) == item_.end())
//     {
//         return "";
//     }
//     else
//     {
//         return item_[itemid].sellerid;
//     }
// }

void SimpleDataBase::ViewItemDetail(const string &itemid)
{
    if (item_.find(itemid) == item_.end())
    {
        cerr << "Item not found!" << endl;
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

double SimpleDataBase::FindUserBalance(const string &userid)
{
    if (user_.find(userid) == user_.end())
    {
        cerr << "User not found!" << endl;
        return -1;
    }
    return user_[userid].balance;
}

int SimpleDataBase::GetItemNumber(const string &itemid)
{
    if (item_.find(itemid) == item_.end())
    {
        cerr << "Item not found!" << endl;
        return -1;
    }
    return item_[itemid].number;
}

double SimpleDataBase::GetItemPrice(const string &itemid)
{
    if (item_.find(itemid) == item_.end())
    {
        cerr << "Item not found!" << endl;
        return -1;
    }
    return item_[itemid].price;
}

string SimpleDataBase::GerItemSellerid(const string &itemid)
{
    if (item_.find(itemid) == item_.end())
    {
        cerr << "Item not found!" << endl;
        return "";
    }
    return item_[itemid].sellerid;
}

double SimpleDataBase::CalculateBalance(const string &userid)
{
    string expression = "";
    ifstream recharge("data/recharge.txt");
    string line;
    while (getline(recharge, line))
    {
        if (line == "")
            continue;
        istringstream iss(line);
        string usid;
        string money;
        string data;
        iss >> usid >> money >> data;
        if (usid == userid)
            expression += " + " + money;
    }
    recharge.close();
    expression.erase(0, 3);
    map<int, vector<double>> link;
    for (auto &i : order_)
    {
        if (i.second.sellerid == userid)
        {
            link[i.second.number].push_back(i.second.unitprice);
        }
        if (i.second.buyerid == userid)
        {
            link[i.second.number].push_back(-i.second.unitprice);
        }
    }
    for (auto &i : link)
    {
        expression += " + " + to_string(i.first) + " * " + Array2Expr(i.second);
    }
    Evaluator evaluator(expression);
    return evaluator.Calculate();
}