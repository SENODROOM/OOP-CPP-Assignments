# 📘 Q2.cpp — Shopping Cart System: Deep Line-by-Line Explanation

---

## 📦 Header Includes

```cpp
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
```

| Header | Purpose |
|--------|---------|
| `<iostream>` | Console input/output (`cin`, `cout`) |
| `<string>` | The `string` class |
| `<cmath>` | Math functions — specifically `round()` used for average display |

---

## 🧱 Struct: `Attribute`

```cpp
struct Attribute
{
    string name;
    string value;
    Attribute *next;

    Attribute(const string &n, const string &v) : name(n), value(v), next(nullptr) {}
};
```

**Purpose:** A node in a **singly linked list** of key-value attribute pairs belonging to a cart item.

| Field | Type | Meaning |
|-------|------|---------|
| `name` | `string` | Attribute key, e.g., `"color"`, `"price"` |
| `value` | `string` | Attribute value, e.g., `"red"`, `"29.99"` |
| `next` | `Attribute*` | Pointer to the next attribute node (or `nullptr` if last) |

The constructor uses an **initializer list** (`: name(n), value(v), next(nullptr)`) — a C++ best practice that directly initializes members instead of assigning them in the body. This is more efficient for objects like `string`.

---

## 🧱 Struct: `CartItem`

```cpp
struct CartItem
{
    int id;
    string name;
    Attribute *attrs;
    CartItem *next;

    CartItem(int i, const string &n) : id(i), name(n), attrs(nullptr), next(nullptr) {}

    ~CartItem()
    {
        Attribute *cur = attrs;
        while (cur)
        {
            Attribute *tmp = cur->next;
            delete cur;
            cur = tmp;
        }
    }
};
```

**Purpose:** A node in the shopping cart's linked list. Each item has its own nested linked list of attributes.

| Field | Type | Meaning |
|-------|------|---------|
| `id` | `int` | Unique identifier for the item |
| `name` | `string` | Display name of the item |
| `attrs` | `Attribute*` | Head of this item's attribute linked list |
| `next` | `CartItem*` | Pointer to the next cart item |

**Destructor `~CartItem()`:** When a `CartItem` is `delete`d, it automatically cleans up all its `Attribute` nodes to prevent memory leaks.
- Saves the next pointer in `tmp` before deleting `cur` (critical — you cannot access `cur->next` after `delete cur`).

---

## 🏛️ Class: `ShoppingCart`

```cpp
class ShoppingCart
{
    CartItem *head;
    int size;
public:
    ShoppingCart() : head(nullptr), size(0) {}
    ~ShoppingCart() { clearCart(); }
    ...
};
```

| Member | Type | Purpose |
|--------|------|---------|
| `head` | `CartItem*` | Points to the first item in the linked list |
| `size` | `int` | Tracks number of items (avoids traversal to count) |

- `head(nullptr)` — empty cart starts with no items.
- `~ShoppingCart()` calls `clearCart()`, which deletes all nodes. This ensures no memory leaks when the cart object goes out of scope.

---

## 🔧 Method: `addItem()`

```cpp
void addItem(int id, const string &name)
{
    CartItem *cur = head;
    while (cur) {
        if (cur->id == id) {
            cout << "Item with ID " << id << " already exists!" << endl;
            return;
        }
        cur = cur->next;
    }
    CartItem *newItem = new CartItem(id, name);
    if (!head) {
        head = newItem;
    } else {
        CartItem *tmp = head;
        while (tmp->next) tmp = tmp->next;
        tmp->next = newItem;
    }
    size++;
    cout << "Item added successfully!" << endl;
}
```

**Step-by-step:**
1. **Duplicate check** — traverses the entire list to ensure no item with the same `id` already exists.
2. **Node creation** — allocates a new `CartItem` on the heap.
3. **Insertion at tail** — if list is empty, `head` points to new item. Otherwise, traverses to the last node and appends.
4. Increments `size`.

---

## 🔧 Method: `removeItem()`

```cpp
void removeItem(int id)
{
    if (!head) { cout << "Cart is empty!" << endl; return; }
    if (head->id == id) {
        CartItem *tmp = head;
        head = head->next;
        delete tmp;
        size--;
        return;
    }
    CartItem *cur = head;
    while (cur->next && cur->next->id != id) cur = cur->next;
    if (!cur->next) { cout << "Item not found!" << endl; return; }
    CartItem *tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
    size--;
}
```

**Step-by-step:**
1. Empty list guard.
2. **Head removal** — special case: update `head` pointer before deleting.
3. **Mid/tail removal** — stop at the node *before* the target (`cur->next->id == id`).
4. Re-link: `cur->next = tmp->next` skips over the deleted node.
5. `delete tmp` — destructor automatically frees the item's attribute list too.

---

## 🔧 Method: `addAttribute()`

```cpp
void addAttribute(int id, const string &attrName, const string &attrValue)
{
    CartItem *item = findItem(id);
    if (!item) { cout << "Item not found!" << endl; return; }
    Attribute *cur = item->attrs;
    while (cur) {
        if (cur->name == attrName) {
            cur->value = attrValue;   // UPDATE existing
            cout << "Attribute added successfully!" << endl;
            return;
        }
        cur = cur->next;
    }
    Attribute *newAttr = new Attribute(attrName, attrValue);
    // Append to tail of attribute list
    if (!item->attrs) item->attrs = newAttr;
    else {
        Attribute *tmp = item->attrs;
        while (tmp->next) tmp = tmp->next;
        tmp->next = newAttr;
    }
    cout << "Attribute added successfully!" << endl;
}
```

- First uses `findItem()` (private helper) to locate the item.
- Checks if the attribute already exists — if so, **updates** the value (upsert behavior).
- Otherwise, creates and appends a new `Attribute` node.

---

## 🔧 Method: `removeAttribute()`

```cpp
void removeAttribute(int id, const string &attrName)
```

- Finds the cart item by `id`.
- Uses the same "stop before target" technique as `removeItem()` to safely unlink and delete the `Attribute` node.

---

## 🔧 Method: `getItemInfo()`

```cpp
void getItemInfo(int id)
{
    CartItem *item = findItem(id);
    if (!item) { cout << "Item not found!" << endl; return; }
    cout << "Item ID: " << item->id << endl;
    cout << "Name: " << item->name << endl;
    Attribute *cur = item->attrs;
    while (cur) {
        cout << cur->name << ": " << cur->value << endl;
        cur = cur->next;
    }
}
```

Traverses and prints the item's info, then walks through its entire attribute linked list printing each key-value pair.

---

## 🔧 Method: `clearCart()`

```cpp
void clearCart()
{
    CartItem *cur = head;
    while (cur) {
        CartItem *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    head = nullptr;
    size = 0;
    cout << "Cart cleared successfully!" << endl;
}
```

- Iterates through every `CartItem`, saving the next pointer before deleting.
- Each `delete cur` triggers `~CartItem()`, which in turn deletes all attributes.
- Resets `head` and `size`.

---

## 🔧 Method: `sortCartByAttr()`

```cpp
void sortCartByAttr(const string &attrName)
{
    CartItem **arr = new CartItem *[size];
    // ... fill arr with pointers to each node ...
    // Bubble sort on arr, comparing attr values
    // Numeric comparison if both values are numbers, else string comparison
    // Re-link the list from sorted arr
    delete[] arr;
    printCart(attrName);
}
```

**Why the pointer array trick?**  
Linked lists can't be randomly accessed by index, so sorting them directly is complex. The trick:
1. Copy all node pointers into a temporary array `arr[]`.
2. Bubble sort the **pointers** (not the nodes themselves) by comparing attribute values.
3. Re-stitch the linked list in the new sorted order by updating `->next` pointers.
4. Free the temporary array.

**Smart comparison logic:**
- `isNumeric(va) && isNumeric(vb)` → convert both to `double` and compare numerically.
- Otherwise, compare lexicographically (string `<` operator).

---

## 🔧 Method: `totalCartValue()`

```cpp
void totalCartValue(const string &priceAttr)
{
    double total = 0;
    CartItem *cur = head;
    while (cur) {
        string val = getAttrValue(cur, priceAttr);
        if (!val.empty() && isNumeric(val))
            total += stod(val);
        cur = cur->next;
    }
    cout << "Total Cart Value: " << total << endl;
}
```

- Walks the cart, reads the named price attribute from each item.
- `stod()` (string to double) converts the string price to a number.
- Only adds to total if the attribute exists and is numeric.

---

## 🔧 Method: `avgCartValue()`

```cpp
void avgCartValue(const string &priceAttr)
{
    double avg = total / count;
    int intPart = (int)avg;
    int decPart = (int)round((avg - intPart) * 100);
    if (decPart == 100) { intPart++; decPart = 0; }
    cout << intPart << ".";
    if (decPart < 10) cout << "0";
    cout << decPart << endl;
}
```

- Computes average manually without using `printf` or `setprecision`.
- Extracts integer and decimal parts manually.
- `round()` from `<cmath>` rounds to 2 decimal places.
- Handles the edge case where rounding gives `decPart == 100` (e.g., `3.999` rounds to `4.00`).
- Manually pads single-digit decimals with a leading `"0"` (e.g., `3.05` not `3.5`).

---

## 🔧 Method: `filterByAttribute()`

```cpp
void filterByAttribute(const string &attrName, const string &attrValue)
```

- If `attrValue` is empty, displays ALL items that have the attribute (regardless of value).
- Otherwise, only displays items where the attribute equals the given value.

---

## 🔒 Private Helpers

### `findItem()`
```cpp
CartItem *findItem(int id)
```
Standard linked-list search. Returns pointer to the node or `nullptr` if not found.

### `getAttrValue()`
```cpp
string getAttrValue(CartItem *item, const string &attrName)
```
Walks an item's attribute list and returns the value for the given attribute name, or `""` if not found.

### `isNumeric()`
```cpp
bool isNumeric(const string &s)
```
- Handles optional leading `-` for negative numbers.
- Allows at most one `.` (decimal point).
- Returns `false` if any non-digit (other than `.` and leading `-`) is found.

---

## 🏁 `main()` — Menu Loop

```cpp
while (true) {
    printMenu();
    cin >> choice;
    cin.ignore();
    ...
}
```

- `cin >> choice` reads the integer choice. The `\n` character remains in the buffer.
- `cin.ignore()` discards that leftover `\n` so that subsequent `getline()` calls work correctly.
- The loop continues until the user enters `0`.

---

## 🧪 Full Test Case Walkthrough

### Sequence of operations:

**1. Add Item (ID=1, Name="Laptop")**
→ List: `[1: Laptop]`

**2. Add Item (ID=2, Name="Mouse")**
→ List: `[1: Laptop] → [2: Mouse]`

**3. Add Attribute (ID=1, "price", "999.99")**
→ Laptop's attrs: `[price: 999.99]`

**4. Add Attribute (ID=2, "price", "25.00")**
→ Mouse's attrs: `[price: 25.00]`

**5. Add Attribute (ID=1, "color", "silver")**
→ Laptop's attrs: `[price: 999.99] → [color: silver]`

**6. Get Item Info (ID=1)**
```
Item ID: 1
Name: Laptop
price: 999.99
color: silver
```

**7. Total Cart Value (attr="price")**
```
Total Cart Value: 1024.99
```

**8. Average Cart Value (attr="price")**
- avg = 1024.99 / 2 = 512.495
- intPart = 512, decPart = round(0.495 * 100) = 50
```
Average Cart Value: 512.50
```

**9. Sort Cart By Attribute "price"**
- Laptop (999.99) vs Mouse (25.00): numeric compare → Mouse < Laptop
- Sorted: `[2: Mouse → 25.00] → [1: Laptop → 999.99]`
```
Cart sorted successfully!
Items in Cart:
2 - Mouse - 25.00
1 - Laptop - 999.99
```

**10. Filter By Attribute (name="color", value="silver")**
```
Filtered Items:
1 - Laptop
```

**11. Remove Item (ID=2)**
→ List: `[1: Laptop]`

**12. Clear Cart**
→ All nodes deleted. List empty.

---

## 🎯 Key Concepts Demonstrated

| Concept | Where Used |
|---------|-----------|
| Singly Linked List | Cart items and attributes |
| Nested Linked Lists | Each `CartItem` contains its own `Attribute` list |
| Struct constructors & destructors | `CartItem`, `Attribute` |
| Pointer-array trick for sorting | `sortCartByAttr()` |
| Numeric vs string comparison | `sortCartByAttr()` / `isNumeric()` |
| Upsert pattern | `addAttribute()` updates if exists |
| Manual decimal formatting | `avgCartValue()` |
| `cin.ignore()` buffer flush | `main()` menu loop |
