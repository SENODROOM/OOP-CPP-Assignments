# 📘 Q1.cpp — Restaurant Menu Sorter: Deep Line-by-Line Explanation

---

## 📦 Header Includes & Namespace

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
```

| Header | Purpose |
|--------|---------|
| `<iostream>` | Enables `cin` and `cout` for console I/O |
| `<fstream>` | Enables `ifstream` / `ofstream` for file reading/writing |
| `<string>` | Provides the `string` class |
| `<cstring>` | C-style string utilities (included but not heavily used here) |
| `using namespace std;` | Avoids writing `std::` before every standard library name |

---

## 🔢 Constants

```cpp
const int MAX_ROWS = 100;
const int MAX_COLS = 7;
const int MAX_LEN  = 200;
```

- **`MAX_ROWS`** — The maximum number of menu items (rows) we can read from the file.
- **`MAX_COLS`** — Each menu item has 7 fields: Category, Cuisine, Item Name, Price, Restaurant, Cook Name, Calories.
- **`MAX_LEN`** — Maximum character length for a single line (declared but not used directly; serves as a design note).

---

## 🔧 Function: `trim()`

```cpp
string trim(const string &s)
{
    int start = 0, end = (int)s.size() - 1;
    while (start <= end && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n'))
        start++;
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n'))
        end--;
    if (start > end) return "";
    return s.substr(start, end - start + 1);
}
```

**Purpose:** Removes all leading and trailing whitespace (spaces, tabs, carriage returns, newlines) from a string.

- `start` begins at the first character; we move it forward while we see whitespace.
- `end` begins at the last character; we move it backward while we see whitespace.
- If `start > end`, the string was all whitespace — return `""`.
- Otherwise return the cleaned substring from `start` to `end` (inclusive).

**Why it matters:** CSV files often have trailing spaces or Windows-style `\r\n` line endings. Without `trim()`, comparisons like `"Mexican" == "Mexican\r"` would fail.

---

## 🔧 Function: `splitLine()`

```cpp
int splitLine(const string &line, string tokens[], int maxTokens)
{
    int count = 0;
    string current = "";
    for (int i = 0; i < (int)line.size(); i++)
    {
        if (line[i] == ',' && count < maxTokens - 1)
        {
            tokens[count++] = trim(current);
            current = "";
        }
        else
        {
            current += line[i];
        }
    }
    tokens[count++] = trim(current);
    return count;
}
```

**Purpose:** Splits a comma-separated line into individual tokens (fields).

- Iterates character by character.
- On each `,` (and when we haven't hit the max tokens limit), it saves the accumulated `current` string as the next token and resets `current`.
- The condition `count < maxTokens - 1` ensures the last field absorbs any remaining content (even if it contains commas).
- After the loop, the last field (after the final comma) is saved.
- Returns the total number of tokens found.

**Example:** `"Main Course, Mexican, Tacos, 12, RestaurantA, Chef Maria, 450"` → 7 tokens.

---

## 🔧 Function: `categoryOrder()`

```cpp
int categoryOrder(const string &cat)
{
    if (cat == "Appetizer")   return 0;
    if (cat == "Main Course") return 1;
    if (cat == "Dessert")     return 2;
    return 3;
}
```

**Purpose:** Maps meal category names to integer sort priorities.

- Appetizers come first (0), then Main Courses (1), then Desserts (2).
- Any unknown category gets priority 3 (sorted last).
- This integer is used in `compareLess()` for sorting.

---

## 🔧 Function: `baseCuisine()`

```cpp
string baseCuisine(const string &cuisine)
{
    int pos = cuisine.find('-');
    if (pos != (int)string::npos)
        return cuisine.substr(0, pos);
    return cuisine;
}
```

**Purpose:** Extracts the "base" cuisine type from hyphenated cuisine names.

- `string::npos` is the "not found" sentinel returned by `find()`.
- If a cuisine like `"Mexican-Fusion"` is found, it returns `"Mexican"`.
- If no hyphen exists (e.g., `"Italian"`), it returns the whole string unchanged.
- This ensures that `"Mexican"` and `"Mexican-Fusion"` are grouped under the same cuisine for sorting.

---

## 🔧 Function: `compareLess()`

```cpp
bool compareLess(string **arr, int a, int b)
{
    string ca = baseCuisine(arr[a][1]);
    string cb = baseCuisine(arr[b][1]);
    if (ca != cb) return ca < cb;
    if (arr[a][4] != arr[b][4]) return arr[a][4] < arr[b][4];
    int oa = categoryOrder(arr[a][0]);
    int ob = categoryOrder(arr[b][0]);
    if (oa != ob) return oa < ob;
    int pa = arr[a][3].empty() ? 0 : stoi(arr[a][3]);
    int pb = arr[b][3].empty() ? 0 : stoi(arr[b][3]);
    return pa < pb;
}
```

**Purpose:** A multi-key comparator — returns `true` if row `a` should come before row `b`.

The 4-level sort priority is:

| Priority | Field | Column Index |
|----------|-------|-------------|
| 1st | Base Cuisine (alphabetical) | `[1]` |
| 2nd | Restaurant Name (alphabetical) | `[4]` |
| 3rd | Category (Appetizer → Main → Dessert) | `[0]` |
| 4th | Price (ascending numeric) | `[3]` |

- `stoi()` converts the price string to an integer for numeric comparison.
- Empty prices default to `0`.

---

## 🔧 Function: `sortMenu()`

```cpp
void sortMenu(string **dynArr, int rows)
{
    for (int i = 0; i < rows - 1; i++)
        for (int j = 0; j < rows - i - 1; j++)
            if (!compareLess(dynArr, j, j + 1))
            {
                string *temp = dynArr[j];
                dynArr[j] = dynArr[j + 1];
                dynArr[j + 1] = temp;
            }
}
```

**Purpose:** Implements **Bubble Sort** on the dynamic array of menu rows.

- Outer loop `i`: each pass guarantees the largest unsorted element "bubbles" to its correct position.
- Inner loop `j`: compares adjacent elements.
- `!compareLess(dynArr, j, j+1)` means "if row `j` should NOT come before row `j+1`" → swap them.
- Swapping is done by swapping **pointers** (`string *`), not entire arrays — this is efficient since only the addresses move, not the actual string data.

---

## 🔧 Function: `displayItem()`

```cpp
void displayItem(string **dynArr, int idx)
{
    cout << "  Category     : " << dynArr[idx][0] << endl;
    cout << "  Cuisine      : " << dynArr[idx][1] << endl;
    cout << "  Item Name    : " << dynArr[idx][2] << endl;
    cout << "  Price        : " << dynArr[idx][3] << endl;
    cout << "  Restaurant   : " << dynArr[idx][4] << endl;
    cout << "  Cook Name    : " << (dynArr[idx][5].empty() ? "[missing]" : dynArr[idx][5]) << endl;
    cout << "  Calories     : " << (dynArr[idx][6].empty() ? "[missing]" : dynArr[idx][6]) << endl;
    cout << "  ----------------------------------------" << endl;
}
```

**Purpose:** Neatly prints all 7 fields of a menu item to the console.

- Uses the ternary operator `condition ? valueIfTrue : valueIfFalse` to display `[missing]` when optional fields (Cook Name, Calories) are empty strings.

---

## 🏁 `main()` — Step by Step

### Step 1: Reading the File

```cpp
string staticArr[MAX_ROWS][MAX_COLS];
int rowCount = 0;
```
- A 2D static array is declared to hold up to 100 rows × 7 columns of string data.
- `rowCount` tracks how many rows were actually read.

```cpp
ifstream fin;
string pathsToTry[] = { "Q1.txt", "solution/Q1.txt", ... };
for (int p = 0; p < 5; p++) {
    fin.open(pathsToTry[p]);
    if (fin.is_open()) { break; }
}
```
- Tries 5 different file paths in order, from relative to absolute.
- Stops as soon as one opens successfully.

```cpp
while (getline(fin, line) && rowCount < MAX_ROWS)
{
    line = trim(line);
    if (line.empty()) continue;
    string tokens[MAX_COLS];
    int count = splitLine(line, tokens, MAX_COLS);
    for (int j = 0; j < MAX_COLS; j++)
        staticArr[rowCount][j] = (j < count) ? tokens[j] : "";
    rowCount++;
}
```
- Reads one line at a time with `getline()`.
- Trims whitespace and skips blank lines.
- Splits the line by commas into up to 7 tokens.
- If a line has fewer than 7 fields, missing ones are stored as `""`.

---

### Step 2: Creating the Dynamic 2D Array

```cpp
int DCOLS = MAX_COLS + 1;
string **dynArr = new string *[rowCount];
for (int i = 0; i < rowCount; i++)
{
    dynArr[i] = new string[DCOLS];
    for (int j = 0; j < MAX_COLS; j++)
        dynArr[i][j] = staticArr[i][j];
    dynArr[i][MAX_COLS] = "\0";
}
```
- Allocates a dynamic array of exactly `rowCount` rows (more memory-efficient than the static 100-row array).
- Each row has 8 columns: 7 data fields + 1 null-marker column (an extra `"\0"` sentinel, a design choice to mark end-of-row).
- Data is copied from the static array to the dynamic one.

---

### Step 3: Sorting

```cpp
sortMenu(dynArr, rowCount);
```
- Calls the bubble sort using our multi-key comparator.

---

### Step 4: Display

```cpp
for (int i = 0; i < rowCount; i++) {
    cout << "Item #" << (i + 1) << ":" << endl;
    displayItem(dynArr, i);
}
```
- Loops through all sorted rows and prints each item.

---

### Step 5: Search by Cuisine

```cpp
getline(cin, searchCuisine);
for (int i = 0; i < rowCount; i++) {
    string cuisine = dynArr[i][1];
    if (cuisine == searchCuisine || ...)
        displayItem(dynArr, i);
}
```
- Accepts a user-entered cuisine name.
- Matches items where the cuisine exactly equals the search term, OR starts with it followed by a `-` (e.g., searching `"Mexican"` finds `"Mexican-Fusion"` too).

---

### Step 6: Export to File

```cpp
ofstream fout("...sorted_menu.txt");
```
- Writes the sorted menu to a `.txt` file, grouped by category using `lastCategory` tracking.

---

### Step 7: Memory Cleanup

```cpp
for (int i = 0; i < rowCount; i++)
    delete[] dynArr[i];
delete[] dynArr;
```
- Every dynamically allocated row is `delete[]`'d first.
- Then the outer pointer array is `delete[]`'d.
- This prevents **memory leaks**.

---

## 🧪 Full Test Case Walkthrough

### Input File (`Q1.txt`) — Sample Data:
```
Dessert, Italian, Tiramisu, 8, BistroRome, Chef Luca, 320
Appetizer, Mexican, Guacamole, 5, TacoLand, , 150
Main Course, Mexican, Enchiladas, 14, TacoLand, Chef Maria, 600
Appetizer, Italian, Bruschetta, 7, BistroRome, Chef Luca, 200
Main Course, Italian, Pasta, 12, BistroRome, , 500
```

### After `trim()` and `splitLine()`:
Each line becomes a row in `staticArr`. For example, row 0:
- `[0]` = `"Dessert"`, `[1]` = `"Italian"`, `[2]` = `"Tiramisu"`, `[3]` = `"8"`, `[4]` = `"BistroRome"`, `[5]` = `"Chef Luca"`, `[6]` = `"320"`

### Sort Order Applied:
`baseCuisine` → Restaurant → Category → Price

| # | Cuisine | Restaurant | Category | Price | Item |
|---|---------|-----------|---------|-------|------|
| 1 | Italian | BistroRome | Appetizer | 7 | Bruschetta |
| 2 | Italian | BistroRome | Main Course | 12 | Pasta |
| 3 | Italian | BistroRome | Dessert | 8 | Tiramisu |
| 4 | Mexican | TacoLand | Appetizer | 5 | Guacamole |
| 5 | Mexican | TacoLand | Main Course | 14 | Enchiladas |

### Console Output:
```
Item #1:
  Category     : Appetizer
  Cuisine      : Italian
  Item Name    : Bruschetta
  Price        : 7
  Restaurant   : BistroRome
  Cook Name    : Chef Luca
  Calories     : 200
  ----------------------------------------
...
```

### Search: User types `"Mexican"`:
Matches rows 4 and 5 → displays Guacamole and Enchiladas.

---

## 🎯 Key Concepts Demonstrated

| Concept | Where Used |
|---------|-----------|
| Static 2D arrays | Initial file storage |
| Dynamic 2D arrays (`new`/`delete`) | Working data structure |
| Pointer swapping in sort | `sortMenu()` |
| Multi-key comparator | `compareLess()` |
| File I/O (`ifstream`/`ofstream`) | Reading input, writing output |
| String manipulation | `trim()`, `splitLine()`, `baseCuisine()` |
| Ternary operator | `displayItem()` for missing fields |
