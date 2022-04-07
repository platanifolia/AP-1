#include "user.h"

User::User()
{
    sdb_ = nullptr;
}

User::User(SimpleDataBase *sdb)
{
    sdb_ = sdb;
}

void User::ViewUser()
{
    sdb_->ParseSql("SELECT * FROM user");
    return;
}

void User::ViewItem()
{
    sdb_->ParseSql("SELECT * FROM commodity");
    return;
}

void User::ViewOrder()
{
    sdb_->ParseSql("SELECT * FROM order");
    return;
}

void User::ViewUser(const std::string &userid)
{
    sdb_->ParseSql("SELECT * FROM user WHERE userID CONTAINS " + userid);
    return;
}

void User::ViewItem(const std::string &itemid)
{
    sdb_->ParseSql("SELECT * FROM commodity WHERE commodityID CONTAINS " + itemid);
    return;
}

bool User::OffShelf(const std::string &itemid)
{
    sdb_->ParseSql("UPDATE commodity SET state=已下架 WHERE commodityID=" + itemid);
    return true;
}