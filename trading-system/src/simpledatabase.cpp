#include "simpledatabase.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include <filesystem>

#include "strhandle.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::map;
using std::ios;
using std::cout;
using std::endl;
using std::istringstream;
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

        vector<string> datatoken;
        StringSplit(line, datatoken, ",");
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
        string itemid, itemname, description, sellerid, addeddate, state;
        double price;
        int number;

        size_t pos = line.find(',');
        itemid = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        itemname = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        price = stod(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(',');
        number = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(',');
        description = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        sellerid = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        addeddate = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        state = line.substr(0, pos);

        ItemInfo iteminfo;
        iteminfo.itemname = itemname;
        iteminfo.price = price;
        iteminfo.number = number;
        iteminfo.description = description;
        iteminfo.sellerid = sellerid;
        iteminfo.addeddate = addeddate;
        iteminfo.state = state;
        item_[itemid] = iteminfo;
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
        string orderid, itemid, date, sellerid, buyerid;
        double unitprice;
        int number;

        size_t pos = line.find(',');
        orderid = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        itemid = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        unitprice = stod(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(',');
        number = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(',');
        date = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        sellerid = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(',');
        buyerid = line.substr(0, pos);

        OrderInfo orderinfo;
        orderinfo.itemid = itemid;
        orderinfo.unitprice = unitprice;
        orderinfo.number = number;
        orderinfo.date = date;
        orderinfo.sellerid = sellerid;
        orderinfo.buyerid = buyerid;
        order_[orderid] = orderinfo;
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

    char tmp[32] = {NULL};
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", &stime);
    string date(tmp);

    logfile << endl
            << date << ": " << sql;
    logfile.close();
    return true;
}

void SimpleDataBase::InsertUser(const string &insertdata)
{
    string temp = insertdata.substr(1, insertdata.length() - 2);
    string tempid;
    UserInfo tempinfo;

    size_t pos = temp.find(',');
    tempid = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.username = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.password = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.telephone = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.address = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.balance = stod(temp.substr(0, pos));
    temp = temp.substr(pos + 1);
    tempinfo.userstate = temp;

    user_[tempid] = tempinfo;

    SaveUser("data/user.txt");
}

void SimpleDataBase::InsertItem(const string &insertdata)
{
    string temp = insertdata.substr(1, insertdata.length() - 2);
    string tempid;
    ItemInfo tempinfo;

    size_t pos = temp.find(',');
    tempid = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.itemname = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.price = stod(temp.substr(0, pos));
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.number = stoi(temp.substr(0, pos));
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.description = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.sellerid = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.addeddate = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    tempinfo.state = temp;

    item_[tempid] = tempinfo;

    SaveItem("data/commodity.txt");
}

void SimpleDataBase::InsertOrder(const string &insertdata)
{
    string temp = insertdata.substr(1, insertdata.length() - 2);
    string tempid;
    OrderInfo tempinfo;

    size_t pos = temp.find(',');
    tempid = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.itemid = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.unitprice = stod(temp.substr(0, pos));
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.number = stoi(temp.substr(0, pos));
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.date = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    pos = temp.find(',');
    tempinfo.sellerid = temp.substr(0, pos);
    temp = temp.substr(pos + 1);
    tempinfo.buyerid = temp;

    order_[tempid] = tempinfo;

    SaveOrder("data/order.txt");
}

int SimpleDataBase::ParseSql(const string &sql)
{
    LogFile(sql);
    istringstream sqldevide(sql);
    string temp;
    vector<string> words;
    while (sqldevide >> temp)
        words.push_back(temp);

    if (words[0] == "INSERT")
    {
        if (words[1] == "INTO")
        {
            if (words[2] == "user")
            {
                InsertUser(words[4]);
                return 1;
            }
            else if (words[2] == "commodity")
            {
                InsertItem(words[4]);
                return 2;
            }
            else if (words[2] == "order")
            {
                InsertOrder(words[4]);
                return 3;
            }
        }
    }
    return 0;
}

bool SimpleDataBase::print(string tablename)
{
    if (tablename == "user")
    {
        for (auto &user : user_)
        {
            cout << user.first << " " << user.second.username << " " << user.second.password << " " << user.second.telephone << " " << user.second.address << " " << user.second.balance << " " << user.second.userstate << endl;
        }
    }
    else if (tablename == "item")
    {
        for (auto &item : item_)
        {
            cout << item.first << " " << item.second.itemname << " " << item.second.price << " " << item.second.number << " " << item.second.description << " " << item.second.sellerid << " " << item.second.addeddate << " " << item.second.state << endl;
        }
    }
    else if (tablename == "order")
    {
        for (auto &order : order_)
        {
            cout << order.first << " " << order.second.itemid << " " << order.second.unitprice << " " << order.second.number << " " << order.second.date << " " << order.second.sellerid << " " << order.second.buyerid << endl;
        }
    }
    else
    {
        cout << "Wrong table name!" << endl;
        return false;
    }
    return true;
}

// int main()
//{
//     SimpleDataBase sdb;
//     sdb.ParseSql("INSERT INTO user VALUES (U004,user4,123456,6545465,QingHai,1314.0,iactive)");
//     sdb.print("user");
//     return 0;
// }