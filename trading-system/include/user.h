#ifndef USER_H_
#define USER_H_

#include "simpledatabase.h"

class User
{
public:
    User();
    User(SimpleDataBase *sdb);
protected:
    SimpleDataBase *sdb_;
};

#endif // USER_H_