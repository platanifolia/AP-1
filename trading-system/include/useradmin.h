#ifndef USERADMIN_H_
#define USERADMIN_H_

#include "user.h"

class UserAdmin : public User
{
public:
    UserAdmin();
    UserAdmin(SimpleDataBase *sdb);

    void AdminView();
};

#endif // USERADMIN_H_