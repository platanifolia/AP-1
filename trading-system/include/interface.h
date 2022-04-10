#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <string>

#include "simpledatabase.h"

class InterFace {
private:
    std::string adminname_;
    std::string adminpassword_;

    // string usernow_;
    SimpleDataBase* sdb_;

public:
    InterFace();
    InterFace(SimpleDataBase* sdb);

    void FirstView();

    bool AdminVerification();
    bool UserVerification(const std::string& username, const std::string& password);
    bool UserRegister(const std::string& username, const std::string& password);
};

#endif  // INTERFACE_H_