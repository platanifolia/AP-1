#include "simpledatabase.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include <filesystem>

#include "strhandle.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::istringstream;
using std::map;
using std::ofstream;
using std::string;
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
        // userfile.close();
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
        // string userid0, username1, password2, phonenumber3, address4, userstate6;
        // double balance5;
        // size_t pos = line.find(',');
        // userid0 = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // username1 = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // password2 = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // phonenumber3 = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // address4 = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // balance5 = stod(line.substr(0, pos));
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // userstate6 = line.substr(0, pos);

        // UserInfo userinfo;
        // userinfo.username = username1;
        // userinfo.password = password2;
        // userinfo.telephone = phonenumber3;
        // userinfo.address = address4;
        // userinfo.balance = balance5;
        // userinfo.userstate = userstate6;

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
        // itemfile.close();
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
        // string itemid, itemname, description, sellerid, addeddate, state;
        // double price;
        // int number;
        // size_t pos = line.find(',');
        // itemid = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // itemname = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // price = stod(line.substr(0, pos));
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // number = stoi(line.substr(0, pos));
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // description = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // sellerid = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // addeddate = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // state = line.substr(0, pos);

        // ItemInfo iteminfo;
        // iteminfo.itemname = itemname;
        // iteminfo.price = price;
        // iteminfo.number = number;
        // iteminfo.description = description;
        // iteminfo.sellerid = sellerid;
        // iteminfo.addeddate = addeddate;
        // iteminfo.state = state;
        // item_[itemid] = iteminfo;

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
        // orderfile.close();
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
        // string orderid, itemid, date, sellerid, buyerid;
        // double unitprice;
        // int number;
        // size_t pos = line.find(',');
        // orderid = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // itemid = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // unitprice = stod(line.substr(0, pos));
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // number = stoi(line.substr(0, pos));
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // date = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // sellerid = line.substr(0, pos);
        // line = line.substr(pos + 1);
        // pos = line.find(',');
        // buyerid = line.substr(0, pos);

        // OrderInfo orderinfo;
        // orderinfo.itemid = itemid;
        // orderinfo.unitprice = unitprice;
        // orderinfo.number = number;
        // orderinfo.date = date;
        // orderinfo.sellerid = sellerid;
        // orderinfo.buyerid = buyerid;
        // order_[orderid] = orderinfo;

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
    ofstream userfile(filename);
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
    ofstream itemfile(filename);
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
    ofstream orderfile(filename);
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

bool SimpleDataBase::LogFile(string sql)
{
    ofstream logfile("./commands.txt", ios::app);
    if (!logfile)
    {
        logfile.close();
        return false;
    }

    struct tm stime;
    time_t now = time(0);
    localtime_s(&stime, &now);

    char tmp[32] = {0};
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", &stime);
    string date(tmp);

    logfile << endl
            << date << ": " << sql;
    logfile.close();
    return true;
}

void SimpleDataBase::InsertUser(const string &insertdata)
{
    // string temp = insertdata.substr(1, insertdata.length() - 2);
    // string tempid;
    // UserInfo tempinfo;
    // size_t pos = temp.find(',');
    // tempid = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.username = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.password = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.telephone = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.address = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.balance = stod(temp.substr(0, pos));
    // temp = temp.substr(pos + 1);
    // tempinfo.userstate = temp;
    // user_[tempid] = tempinfo;

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
    // string temp = insertdata.substr(1, insertdata.length() - 2);
    // string tempid;
    // ItemInfo tempinfo;
    // size_t pos = temp.find(',');
    // tempid = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.itemname = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.price = stod(temp.substr(0, pos));
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.number = stoi(temp.substr(0, pos));
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.description = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.sellerid = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.addeddate = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // tempinfo.state = temp;
    // item_[tempid] = tempinfo;

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
    // string temp = insertdata.substr(1, insertdata.length() - 2);
    // string tempid;
    // OrderInfo tempinfo;
    // size_t pos = temp.find(',');
    // tempid = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.itemid = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.unitprice = stod(temp.substr(0, pos));
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.number = stoi(temp.substr(0, pos));
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.date = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // pos = temp.find(',');
    // tempinfo.sellerid = temp.substr(0, pos);
    // temp = temp.substr(pos + 1);
    // tempinfo.buyerid = temp;
    // order_[tempid] = tempinfo;

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
        for (auto &i : user_)
        {
            if (i.first.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.username << " " << i.second.password << " "
                     << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                     << i.second.userstate << endl;
            }
        }
        return;
    }
    else if (column == "username")
    {
        for (auto &i : user_)
        {
            if (i.second.username.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.username << " " << i.second.password << " "
                     << i.second.telephone << " " << i.second.address << " " << i.second.balance << " "
                     << i.second.userstate << endl;
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
            if (i.second.userstate.find(condition) != string::npos)
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
    if (column == "" || condition == "")
    {
        for (auto &i : item_)
        {
            cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                 << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                 << i.second.addeddate << " " << i.second.state << endl;
        }
        return;
    }
    else if (column == "commodityID")
    {
        for (auto &i : item_)
        {
            if (i.first.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        return;
    }
    else if (column == "commodityName")
    {
        for (auto &i : item_)
        {
            if (i.second.itemname.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        return;
    }
    else if (column == "price")
    {
        for (auto &i : item_)
        {
            if (i.second.price == stod(condition))
            {
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        return;
    }
    else if (column == "number")
    {
        for (auto &i : item_)
        {
            if (i.second.number == stoi(condition))
            {
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        return;
    }
    else if (column == "description")
    {
        for (auto &i : item_)
        {
            if (i.second.description.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        return;
    }
    else if (column == "sellerID")
    {
        for (auto &i : item_)
        {
            if (i.second.sellerid.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        return;
    }
    else if (column == "addedDate")
    {
        for (auto &i : item_)
        {
            if (i.second.addeddate.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
        return;
    }
    else if (column == "state")
    {
        for (auto &i : item_)
        {
            if (i.second.state.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.itemname << " " << i.second.price << " "
                     << i.second.number << " " << i.second.description << " " << i.second.sellerid << " "
                     << i.second.addeddate << " " << i.second.state << endl;
            }
        }
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
        for (auto &i : order_)
        {
            if (i.first.find(condition) != string::npos)
            {
                cout << i.first << " " << i.second.itemid << " " << i.second.unitprice << " "
                     << i.second.number << " " << i.second.date << " " << i.second.sellerid << " "
                     << i.second.buyerid << endl;
            }
        }
        return;
    }
    else if (column == "commodityID")
    {
        for (auto &i : order_)
        {
            if (i.second.itemid.find(condition) != string::npos)
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
    else if (column == "data")
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
            if (i.second.sellerid.find(condition) != string::npos)
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
            if (i.second.buyerid.find(condition) != string::npos)
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
    if (conditionvalue.size() != 3)
    {
        cerr << "Update user condition error!" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为userID的情形
    // auto iter = user_.begin();

    for (string &i : changevalue)
    {
        vector<string> changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 3)
        {
            cerr << "Update user data error!" << endl;
            return false;
        }
        if (changetemp[0] == "username")
        {
            // TOFIX: 更新username使之不重复
            user_[conditionvalue[2]].username = changetemp[2];
        }
        else if (changetemp[0] == "password")
        {
            user_[conditionvalue[2]].password = changetemp[2];
        }
        else if (changetemp[0] == "phoneNumber")
        {
            user_[conditionvalue[2]].telephone = changetemp[2];
        }
        else if (changetemp[0] == "address")
        {
            user_[conditionvalue[2]].address = changetemp[2];
        }
        else if (changetemp[0] == "balance")
        {
            user_[conditionvalue[2]].balance = stod(changetemp[2]);
        }
        else if (changetemp[0] == "userState")
        {
            user_[conditionvalue[2]].userstate = changetemp[2];
        }
        else
        {
            cerr << "Update user data error!" << endl;
            return false;
        }
    }
    return true;
}

bool SimpleDataBase::UpdateItem(const std::string &updatedata, const std::string &condition)
{
    vector<string> changevalue;
    StringSplit(updatedata, changevalue, ",");
    vector<string> conditionvalue;
    StringSplit(condition, conditionvalue, "=");
    if (conditionvalue.size() != 3)
    {
        cerr << "Update item condition error!" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为itemID的情形
    // auto iter = item_.begin();

    for (string &i : changevalue)
    {
        vector<string> changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 3)
        {
            cerr << "Update item data error!" << endl;
            return false;
        }
        if (changetemp[0] == "commodityName")
        {
            item_[conditionvalue[2]].itemname = changetemp[2];
        }
        else if (changetemp[0] == "price")
        {
            item_[conditionvalue[2]].price = stoi(changetemp[2]);
        }
        else if (changetemp[0] == "number")
        {
            item_[conditionvalue[2]].number = stoi(changetemp[2]);
        }
        else if (changetemp[0] == "description")
        {
            item_[conditionvalue[2]].description = stoi(changetemp[2]);
        }
        else if (changetemp[0] == "sellerID")
        {
            item_[conditionvalue[2]].sellerid = changetemp[2];
        }
        else if (changetemp[0] == "addedDate")
        {
            item_[conditionvalue[2]].addeddate = changetemp[2];
        }
        else if (changetemp[0] == "state")
        {
            item_[conditionvalue[2]].state = changetemp[2];
        }
        else
        {
            cerr << "Update item data error!" << endl;
            return false;
        }
    }
    return true;
}

bool SimpleDataBase::UpdateOrder(const std::string &updatedata, const std::string &condition)
{
    vector<string> changevalue;
    StringSplit(updatedata, changevalue, ",");
    vector<string> conditionvalue;
    StringSplit(condition, conditionvalue, "=");
    if (conditionvalue.size() != 3)
    {
        cerr << "Update order condition error!" << endl;
        return false;
    }
    // TOFIX: 只是更新condition为orderID的情形
    // auto iter = order_.begin();

    for (string &i : changevalue)
    {
        vector<string> changetemp;
        StringSplit(i, changetemp, "=");
        if (changetemp.size() != 3)
        {
            cerr << "Update order data error!" << endl;
            return false;
        }
        if (changetemp[0] == "commodityID")
        {
            order_[conditionvalue[2]].itemid = changetemp[2];
        }
        else if (changetemp[0] == "unitPrice")
        {
            order_[conditionvalue[2]].unitprice = stod(changetemp[2]);
        }
        else if (changetemp[0] == "number")
        {
            order_[conditionvalue[2]].number = stoi(changetemp[2]);
        }
        else if (changetemp[0] == "date")
        {
            order_[conditionvalue[2]].date = changetemp[2];
        }
        else if (changetemp[0] == "sellerID")
        {
            order_[conditionvalue[2]].sellerid = changetemp[2];
        }
        else if (changetemp[0] == "buyerID")
        {
            order_[conditionvalue[2]].buyerid = changetemp[2];
        }
        else
        {
            cerr << "Update order data error!" << endl;
            return false;
        }
    }
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
    else
    {
        cerr << "Sql error!" << endl;
        return 0;
    }
    return 0;
}

// bool SimpleDataBase::print(string tablename)
// {
//     if (tablename == "user")
//     {
//         for (auto &user : user_)
//         {
//             cout << user.first << " " << user.second.username << " " << user.second.password << " " << user.second.telephone << " " << user.second.address << " " << user.second.balance << " " << user.second.userstate << endl;
//         }
//     }
//     else if (tablename == "item")
//     {
//         for (auto &item : item_)
//         {
//             cout << item.first << " " << item.second.itemname << " " << item.second.price << " " << item.second.number << " " << item.second.description << " " << item.second.sellerid << " " << item.second.addeddate << " " << item.second.state << endl;
//         }
//     }
//     else if (tablename == "order")
//     {
//         for (auto &order : order_)
//         {
//             cout << order.first << " " << order.second.itemid << " " << order.second.unitprice << " " << order.second.number << " " << order.second.date << " " << order.second.sellerid << " " << order.second.buyerid << endl;
//         }
//     }
//     else
//     {
//         cout << "Wrong table name!" << endl;
//         return false;
//     }
//     return true;
// }