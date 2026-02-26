#ifndef SHOPPING_CART_MANAGEMENT_SYSTEM_H
#define SHOPPING_CART_MANAGEMENT_SYSTEM_H

#include <iostream>
#include <string>
using namespace std;

struct Attribute
{
    string name;
    string value;
    Attribute *next;

    Attribute(const string &n, const string &v);
};

struct CartItem
{
    int id;
    string name;
    Attribute *attrs;
    CartItem *next;

    CartItem(int i, const string &n);
    ~CartItem();
};

class ShoppingCart
{
    CartItem *head;
    int size;

public:
    ShoppingCart();
    ~ShoppingCart();

    void addItem(int id, const string &name);
    void removeItem(int id);
    void addAttribute(int id, const string &attrName, const string &attrValue);
    void removeAttribute(int id, const string &attrName);
    void getItemInfo(int id);
    void clearCart();
    void sortCartByAttr(const string &attrName);
    void totalCartValue(const string &priceAttr);
    void avgCartValue(const string &priceAttr);
    void filterByAttribute(const string &attrName, const string &attrValue);
    void printCart(const string &attrName = "");

private:
    CartItem *findItem(int id);
    string getAttrValue(CartItem *item, const string &attrName);
    bool isNumeric(const string &s);
    int customRound(double value);
};

void printMenu();

#endif // SHOPPING_CART_MANAGEMENT_SYSTEM_H
