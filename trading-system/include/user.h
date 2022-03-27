#ifndef USER_H_
#define USER_H_

#include "simpledatabase.h"

class User
{
public:
    User();
    User(SimpleDataBase *sdb);

    // Admin functions, view all
    void ViewUser();
    // Admin functions, view all
    void ViewItem();
    // Admin functions, view all
    void ViewOrder();

    // view user by userid
    void ViewUser(const std::string &userid);
    // view item by itemid
    void ViewItem(const std::string &itemid);
    // Off shelf commomity by itemid
    bool OffShelf(const std::string &itemid);
protected:
    SimpleDataBase *sdb_;
};

#endif // USER_H_