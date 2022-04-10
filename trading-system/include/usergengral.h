#ifndef USERGENERAL_H_
#define USERGENERAL_H_

#include "user.h"

class UserGeneral : public User {
public:
    UserGeneral();
    UserGeneral(SimpleDataBase* sdb, const std::string& nowuserid);

    void UserGeneralView();
    void BuyerView();
    void SellerView();
    void UserInfoView();

    // Seller functions
    bool PostItem(const std::string& itemname, const std::string& itemprice, const std::string& itemnumber, const std::string& itemdescription);
    void SellerViewItem();
    bool ModifyItem(const std::string& itemid, int choice, const std::string& modifydata);
    void SellerViewOrder();
    // Buyer functions
    void BuyerViewItem();
    void SearchItem(const std::string& itemname);
    void BuyerViewOrder();
    bool Purchase(const std::string& itemid, int buynumber);
    // UserInfo functions
    void ViewUserDetail();
    bool ModifyUserInfo(int choice, const std::string& modifydata);
    bool Recharge(double money);

protected:
    std::string nowuserid_;
};

#endif  // USERGENERAL_H_