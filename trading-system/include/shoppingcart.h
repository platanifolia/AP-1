#ifndef SHOPPINGCART_H_
#define SHOPPINGCART_H_

#include "simpledatabase.h"

#include <string>
#include <map>

class ShoppingCart
{
private:
    SimpleDataBase *sdb_;
    std::map<std::string, std::map<std::string, int>> shoppingcart_;

public:
    ShoppingCart();
    ShoppingCart(SimpleDataBase *sdb);

    bool LoadShoppingCart();
    bool SaveShoppingCart();
    bool UpdateShoppingCart(const std::string &userid, const std::string &itemid, int number);
    void ViewShoppingCart(const std::string &userid);
    double TotalPrice(const std::string &userid);
    bool BuyAll(const std::string &userid);

    bool BuyItem(const std::string &userid, const std::string &itemid, int number);
    bool DeleteItem(const std::string &userid, const std::string &itemid);

    void CartInterface(const std::string &userid);
};

#endif // SHOPPINGCART_H_