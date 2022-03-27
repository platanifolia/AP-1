#ifndef USERADMIN_H_
#define USERADMIN_H_

#include "user.h"

class UserAdmin : public User
{
public:
    UserAdmin();
    UserAdmin(SimpleDataBase *sdb);

    void AdminView();

    void SearchItem(const std::string &itemname);

    bool BanUser(const std::string &userid);
};

#endif // USERADMIN_H_