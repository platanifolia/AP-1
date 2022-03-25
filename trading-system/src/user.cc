#include "user.h"

User::User()
{
    sdb_ = nullptr;
}

User::User(SimpleDataBase *sdb)
{
    sdb_ = sdb;
}