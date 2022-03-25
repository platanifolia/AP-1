#ifndef USER_H_
#define USER_H_

#include "simpledatabase.h"

class User
{
public:
    User();
    User(SimpleDataBase *sdb);

    void ViewUser();
    void ViewItem();
    void ViewOrder();

    void ViewUser(const std::string &userid);
    void ViewItem(const std::string &itemid);

    bool OffShelf(const std::string &itemid);
protected:
    SimpleDataBase *sdb_;
};

#endif // USER_H_