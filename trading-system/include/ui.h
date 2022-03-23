#ifndef UI_H_
#define UI_H_

#include <string>

using namespace std;

class InterFace
{
private:
    string adminname_;
    string adminpassword_;

    string usernow_;

public:
    InterFace();

    void FirstView();

    bool AdminLogin();
    bool UserRegister();
    bool UserLogin();

    bool AdminView();

    bool CommomUserView();
    bool BuyerView();
    bool SellerView();
};

#endif // UI_H_