#include "ShoppingCartManagementSystem.h"

Attribute::Attribute(const string &n, const string &v) : name(n), value(v), next(nullptr) {}

CartItem::CartItem(int i, const string &n) : id(i), name(n), attrs(nullptr), next(nullptr) {}

CartItem::~CartItem()
{
    Attribute *cur = attrs;
    while (cur)
    {
        Attribute *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}


ShoppingCart::ShoppingCart() : head(nullptr), size(0) {}

ShoppingCart::~ShoppingCart()
{
    while (head)
    {
        CartItem *tmp = head;
        head = head->next;
        delete tmp;
    }
}

void ShoppingCart::addItem(int id, const string &name)
{
    CartItem *cur = head;
    while (cur)
    {
        if (cur->id == id)
        {
            cout << "Item with ID " << id << " already exists!" << endl;
            return;
        }
        cur = cur->next;
    }
    CartItem *newItem = new CartItem(id, name);
    if (!head)
    {
        head = newItem;
    }
    else
    {
        CartItem *tmp = head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = newItem;
    }
    size++;
    cout << "Item added successfully!" << endl;
}

void ShoppingCart::removeItem(int id)
{
    if (!head)
    {
        cout << "Cart is empty!" << endl;
        return;
    }
    if (head->id == id)
    {
        CartItem *tmp = head;
        head = head->next;
        delete tmp;
        size--;
        cout << "Item removed successfully!" << endl;
        return;
    }
    CartItem *cur = head;
    while (cur->next && cur->next->id != id)
    {
        cur = cur->next;
    }
    if (!cur->next)
    {
        cout << "Item not found!" << endl;
        return;
    }
    CartItem *tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
    size--;
    cout << "Item removed successfully!" << endl;
}

void ShoppingCart::addAttribute(int id, const string &attrName, const string &attrValue)
{
    CartItem *item = findItem(id);
    if (!item)
    {
        cout << "Item not found!" << endl;
        return;
    }
    Attribute *cur = item->attrs;
    while (cur)
    {
        if (cur->name == attrName)
        {
            cur->value = attrValue;
            cout << "Attribute added successfully!" << endl;
            return;
        }
        cur = cur->next;
    }
    Attribute *newAttr = new Attribute(attrName, attrValue);
    if (!item->attrs)
    {
        item->attrs = newAttr;
    }
    else
    {
        Attribute *tmp = item->attrs;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = newAttr;
    }
    cout << "Attribute added successfully!" << endl;
}

void ShoppingCart::removeAttribute(int id, const string &attrName)
{
    CartItem *item = findItem(id);
    if (!item)
    {
        cout << "Item not found!" << endl;
        return;
    }
    if (!item->attrs)
    {
        cout << "No attributes found for item!" << endl;
        return;
    }
    if (item->attrs->name == attrName)
    {
        Attribute *tmp = item->attrs;
        item->attrs = item->attrs->next;
        delete tmp;
        cout << "Attribute removed successfully!" << endl;
        return;
    }
    Attribute *cur = item->attrs;
    while (cur->next && cur->next->name != attrName)
    {
        cur = cur->next;
    }
    if (!cur->next)
    {
        cout << "Attribute not found!" << endl;
        return;
    }
    Attribute *tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
    cout << "Attribute removed successfully!" << endl;
}

void ShoppingCart::getItemInfo(int id)
{
    CartItem *item = findItem(id);
    if (!item)
    {
        cout << "Item not found!" << endl;
        return;
    }
    cout << "Item ID: " << item->id << endl;
    cout << "Name: " << item->name << endl;
    Attribute *cur = item->attrs;
    while (cur)
    {
        cout << cur->name << ": " << cur->value << endl;
        cur = cur->next;
    }
}

void ShoppingCart::clearCart()
{
    CartItem *cur = head;
    while (cur)
    {
        CartItem *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    head = nullptr;
    size = 0;
    cout << "Cart cleared successfully!" << endl;
}

void ShoppingCart::sortCartByAttr(const string &attrName)
{
    if (!head || !head->next)
    {
        cout << "Cart sorted successfully!" << endl;
        printCart(attrName);
        return;
    }
    CartItem **arr = new CartItem *[size];
    CartItem *cur = head;
    for (int i = 0; i < size; i++)
    {
        arr[i] = cur;
        cur = cur->next;
    }
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            string va = getAttrValue(arr[j], attrName);
            string vb = getAttrValue(arr[j + 1], attrName);
            bool shouldSwap = false;
            bool aIsNum = isNumeric(va);
            bool bIsNum = isNumeric(vb);
            if (aIsNum && bIsNum)
            {
                shouldSwap = stod(va) > stod(vb);
            }
            else
            {
                shouldSwap = va > vb;
            }
            if (shouldSwap)
            {
                CartItem *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    head = arr[0];
    for (int i = 0; i < size - 1; i++)
    {
        arr[i]->next = arr[i + 1];
    }
    arr[size - 1]->next = nullptr;
    delete[] arr;
    cout << "Cart sorted successfully!" << endl;
    printCart(attrName);
}

void ShoppingCart::totalCartValue(const string &priceAttr)
{
    double total = 0;
    CartItem *cur = head;
    while (cur)
    {
        string val = getAttrValue(cur, priceAttr);
        if (!val.empty() && isNumeric(val))
        {
            total += stod(val);
        }
        cur = cur->next;
    }
    cout << "Total Cart Value: " << total << endl;
}

void ShoppingCart::avgCartValue(const string &priceAttr)
{
    if (size == 0)
    {
        cout << "Cart is empty!" << endl;
        return;
    }
    double total = 0;
    int count = 0;
    CartItem *cur = head;
    while (cur)
    {
        string val = getAttrValue(cur, priceAttr);
        if (!val.empty() && isNumeric(val))
        {
            total += stod(val);
            count++;
        }
        cur = cur->next;
    }
    if (count == 0)
    {
        cout << "No numeric values found for attribute: " << priceAttr << endl;
        return;
    }
    double avg = total / count;
    cout << "Average Cart Value: ";
    int intPart = (int)avg;
    int decPart = customRound((avg - intPart) * 100);
    if (decPart == 100)
    {
        intPart++;
        decPart = 0;
    }
    cout << intPart << ".";
    if (decPart < 10)
    {
        cout << "0";
    }
    cout << decPart << endl;
}

void ShoppingCart::filterByAttribute(const string &attrName, const string &attrValue)
{
    cout << "Filtered Items:" << endl;
    bool found = false;
    CartItem *cur = head;
    while (cur)
    {
        string val = getAttrValue(cur, attrName);
        if (attrValue.empty() || val == attrValue)
        {
            cout << cur->id << " - " << cur->name << endl;
            found = true;
        }
        cur = cur->next;
    }
    if (!found)
    {
        cout << "No items match the filter." << endl;
    }
}

void ShoppingCart::printCart(const string &attrName)
{
    cout << "Items in Cart:" << endl;
    CartItem *cur = head;
    while (cur)
    {
        cout << cur->id << " - " << cur->name;
        if (!attrName.empty())
        {
            string val = getAttrValue(cur, attrName);
            if (!val.empty())
            {
                cout << " - " << val;
            }
        }
        cout << endl;
        cur = cur->next;
    }
}

CartItem *ShoppingCart::findItem(int id)
{
    CartItem *cur = head;
    while (cur)
    {
        if (cur->id == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

string ShoppingCart::getAttrValue(CartItem *item, const string &attrName)
{
    Attribute *cur = item->attrs;
    while (cur)
    {
        if (cur->name == attrName)
        {
            return cur->value;
        }
        cur = cur->next;
    }
    return "";
}

bool ShoppingCart::isNumeric(const string &s)
{
    if (s.empty())
    {
        return false;
    }
    int start = 0;
    if (s[0] == '-')
    {
        start = 1;
    }
    bool hasDot = false;
    for (int i = start; i < (int)s.size(); i++)
    {
        if (s[i] == '.' && !hasDot)
        {
            hasDot = true;
            continue;
        }
        if (s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }
    return true;
}

void printMenu()
{
    cout << "\n===== SHOPPING CART MENU =====" << endl;
    cout << "1. Add Item" << endl;
    cout << "2. Remove Item" << endl;
    cout << "3. Add Attribute" << endl;
    cout << "4. Remove Attribute" << endl;
    cout << "5. Get Item Info" << endl;
    cout << "6. Sort Cart By Attribute" << endl;
    cout << "7. Total Cart Value" << endl;
    cout << "8. Average Cart Value" << endl;
    cout << "9. Filter By Attribute" << endl;
    cout << "10. Clear Cart" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int ShoppingCart::customRound(double value)
{
    if (value >= 0)
    {
        return (int)(value + 0.5);
    }
    else
    {
        return (int)(value - 0.5);
    }
}

int main()
{
    ShoppingCart cart;
    int choice;

    while (true)
    {
        printMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 0)
        {
            cout << "Thank you for using Shopping Cart System!" << endl;
            break;
        }
        else if (choice == 1)
        {
            int id;
            string name;
            cout << "Enter Item ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Item Name: ";
            getline(cin, name);
            cart.addItem(id, name);
        }
        else if (choice == 2)
        {
            int id;
            cout << "Enter Item ID to Remove: ";
            cin >> id;
            cin.ignore();
            cart.removeItem(id);
        }
        else if (choice == 3)
        {
            int id;
            string attrName, attrValue;
            cout << "Enter Item ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Attribute Name: ";
            getline(cin, attrName);
            cout << "Enter Attribute Value: ";
            getline(cin, attrValue);
            cart.addAttribute(id, attrName, attrValue);
        }
        else if (choice == 4)
        {
            int id;
            string attrName;
            cout << "Enter Item ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Attribute Name to Remove: ";
            getline(cin, attrName);
            cart.removeAttribute(id, attrName);
        }
        else if (choice == 5)
        {
            int id;
            cout << "Enter Item ID: ";
            cin >> id;
            cin.ignore();
            cart.getItemInfo(id);
        }
        else if (choice == 6)
        {
            string attr;
            cout << "Enter Attribute to Sort By: ";
            getline(cin, attr);
            cart.sortCartByAttr(attr);
        }
        else if (choice == 7)
        {
            string attr;
            cout << "Enter Price Attribute Name: ";
            getline(cin, attr);
            cart.totalCartValue(attr);
        }
        else if (choice == 8)
        {
            string attr;
            cout << "Enter Price Attribute Name: ";
            getline(cin, attr);
            cart.avgCartValue(attr);
        }
        else if (choice == 9)
        {
            string attrName, attrValue;
            cout << "Enter Attribute Name: ";
            getline(cin, attrName);
            cout << "Enter Attribute Value (leave blank for all): ";
            getline(cin, attrValue);
            cart.filterByAttribute(attrName, attrValue);
        }
        else if (choice == 10)
        {
            cart.clearCart();
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}