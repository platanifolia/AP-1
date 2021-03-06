#ifndef SIMPLEDATABASE_H_
#define SIMPLEDATABASE_H_

#include <string>
#include <map>

// using namespace std;

struct UserInfo
{
    std::string username;
    std::string password;
    std::string telephone;
    std::string address;
    double balance;
    std::string userstate;
};

struct ItemInfo
{
    std::string itemname;
    double price;
    int number;
    std::string description;
    std::string sellerid;
    std::string addeddate;
    std::string state;
};

struct OrderInfo
{
    std::string itemid;
    double unitprice;
    int number;
    std::string date;
    std::string sellerid;
    std::string buyerid;
};

class SimpleDataBase
{
private:
    std::map<std::string, UserInfo> user_;
    std::map<std::string, ItemInfo> item_;
    std::map<std::string, OrderInfo> order_;
    // std::string currentuser_;

public:
    SimpleDataBase();
    // ~SimpleDataBase();

    bool LoadUser(const std::string &filename);
    bool LoadItem(const std::string &filename);
    bool LoadOrder(const std::string &filename);

    bool SaveUser(const std::string &filename);
    bool SaveItem(const std::string &filename);
    bool SaveOrder(const std::string &filename);

    void InsertUser(const std::string &insertdata);
    void InsertItem(const std::string &insertdata);
    void InsertOrder(const std::string &insertdata);

    void SelectUser(const std::string &column = "", const std::string &condition = "");
    void SelectItem(const std::string &column = "", const std::string &condition = "");
    void SelectOrder(const std::string &column = "", const std::string &condition = "");

    bool UpdateUser(const std::string &updatedata, const std::string &condition = "");
    bool UpdateItem(const std::string &updatedata, const std::string &condition = "");
    bool UpdateOrder(const std::string &updatedata, const std::string &condition = "");

    int ParseSql(const std::string &sql);

    bool LogFile(std::string sql);

    bool UsernameExist(const std::string &username);
    std::string FindUserid(const std::string &username);
    std::string FindUsername(const std::string &userid);
    std::string FindUserPhone(const std::string &userid);
    std::string FindUserAddress(const std::string &userid);
    double FindUserBalance(const std::string &userid);
    bool UserVerification(const std::string &username, const std::string &password);
    std::string GetNewUserid();
    std::string GetNewItemid();
    std::string GetNewOrderid();
    // std::string GetItemOwner(const std::string &itemid);
    void ViewItemDetail(const std::string &itemid);
    int GetItemNumber(const std::string &itemid);
    double GetItemPrice(const std::string &itemid);
    std::string GerItemSellerid(const std::string &itemid);

    double CalculateBalance(const std::string &userid);
};

#endif // SIMPLEDATABASE_H_