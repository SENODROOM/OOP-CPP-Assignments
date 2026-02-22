# 📘 Q4.cpp — Dynamic Thesaurus Array: Deep Line-by-Line Explanation

---

## 📦 Header Includes

```cpp
#include <iostream>
#include <string>
using namespace std;
```

| Header | Purpose |
|--------|---------|
| `<iostream>` | Console I/O (`cin`, `cout`) |
| `<string>` | The `string` class for word storage and manipulation |

---

## 🔧 Function: `countGroups()`

```cpp
int countGroups(char *ws)
{
    int count = 1;
    for (int i = 0; ws[i] != '\0'; i++)
    {
        if (ws[i] == '#')
            count++;
    }
    return count;
}
```

**Purpose:** Counts how many synonym groups exist in the input string by counting `#` delimiters.

- `char *ws` — a C-style string (character pointer). The string is terminated by the null character `'\0'`.
- `count = 1` — starts at 1 because `n` delimiters divide a string into `n+1` parts. For example, `"A#B#C"` has 2 `#` signs → 3 groups.
- The loop iterates character by character until the null terminator `'\0'` is reached.
- Each `#` found increments `count`.

**Example:** `"abandon discontinue#absent missing#cable wire"` → 2 `#` symbols → returns `3`.

---

## 🔧 Function: `countWords()`

```cpp
int countWords(const string &group)
{
    int count = 0;
    bool inWord = false;
    for (int i = 0; i < (int)group.size(); i++)
    {
        if (group[i] != ' ' && !inWord)
        {
            inWord = true;
            count++;
        }
        else if (group[i] == ' ')
        {
            inWord = false;
        }
    }
    return count;
}
```

**Purpose:** Counts the number of words in a given group string, handling multiple consecutive spaces gracefully.

- `inWord` is a boolean flag: `true` when currently inside a word, `false` when in whitespace.
- **Entering a word:** when the current character is not a space AND we're not already in a word → increment count, set `inWord = true`.
- **Leaving a word:** when a space is encountered → set `inWord = false`.
- This state-machine approach correctly handles:
  - Leading spaces: don't count until a non-space is found.
  - Multiple spaces between words: only the first space triggers `inWord = false`.
  - Trailing spaces: no false increment since a space doesn't trigger a count.

**Example:** `"  abandon  discontinue  vacate  "` → 3 words.

---

## 🔧 Function: `CreateDynamicArray()`

```cpp
string **CreateDynamicArray(char *ws, int &numGroups, int *&rowSizes)
```

**Signature breakdown:**
- `char *ws` — the full thesaurus input string with `#` as group separator.
- `int &numGroups` — **output parameter** (reference): the function writes the group count here so the caller can use it.
- `int *&rowSizes` — **output parameter** (reference to pointer): function allocates and fills this array with each row's word count.
- Returns `string **` — a jagged 2D array of strings.

---

### Phase 1: Count Groups

```cpp
numGroups = countGroups(ws);
rowSizes = new int[numGroups];
```

- Sets `numGroups` in the caller's scope.
- Allocates the `rowSizes` array.

---

### Phase 2: Split into Group Strings

```cpp
string *groups = new string[numGroups];
int gi = 0;
string current = "";
for (int i = 0; ws[i] != '\0'; i++)
{
    if (ws[i] == '#')
    {
        groups[gi++] = current;
        current = "";
    }
    else
    {
        current += ws[i];
    }
}
groups[gi] = current;
```

- `groups` is a temporary 1D array of strings — one per synonym group.
- Iterates through the C-string character by character.
- When `#` is found, saves the accumulated `current` string as the current group and resets `current`.
- After the loop, saves the final group (after the last `#`).

**Example after this phase for input `"abandon discontinue vacate#absent missing unavailable#cable wire"`:**
- `groups[0]` = `"abandon discontinue vacate"`
- `groups[1]` = `"absent missing unavailable"`
- `groups[2]` = `"cable wire"`

---

### Phase 3: Build the 2D Jagged String Array

```cpp
string **arr = new string *[numGroups];
for (int i = 0; i < numGroups; i++)
{
    rowSizes[i] = countWords(groups[i]);
    arr[i] = new string[rowSizes[i]];

    int wi = 0;
    string word = "";
    for (int j = 0; j < (int)groups[i].size(); j++)
    {
        if (groups[i][j] == ' ')
        {
            if (!word.empty())
            {
                arr[i][wi++] = word;
                word = "";
            }
        }
        else
        {
            word += groups[i][j];
        }
    }
    if (!word.empty())
        arr[i][wi] = word;
}
```

For each group:
1. **Count words** with `countWords()` → determines row allocation size.
2. **Allocate** `new string[rowSizes[i]]` — exactly enough space.
3. **Parse words** by scanning character by character:
   - Non-space characters are appended to `word`.
   - Space triggers saving `word` into `arr[i][wi]` (if `word` is non-empty) and resetting `word`.
   - After the loop, any remaining `word` (the last word, which has no trailing space) is saved.

---

### Phase 4: Cleanup Temporary Array

```cpp
delete[] groups;
return arr;
```

- The temporary `groups` string array served its purpose and is freed.
- The 2D `arr` is returned to the caller (the caller is responsible for freeing it).

---

## 🏁 `main()` — Step by Step

### Input Data

```cpp
char ws[] = "abandon discontinue vacate#absent missing unavailable#cable wire#calculate compute determine measure#safety security refuge";
```

- A C-style character array (mutable, on the stack).
- 5 groups separated by 4 `#` characters.
- Each group is a set of synonyms; the **first word** is considered the "keyword" and the **last word** is the replacement.

### Creating the Thesaurus

```cpp
int numGroups = 0;
int *rowSizes = nullptr;
string **thesaurus = CreateDynamicArray(ws, numGroups, rowSizes);
```

After this call:
- `numGroups = 5`
- `rowSizes = [3, 3, 2, 4, 3]`
- `thesaurus[0] = {"abandon", "discontinue", "vacate"}`
- `thesaurus[1] = {"absent", "missing", "unavailable"}`
- `thesaurus[2] = {"cable", "wire"}`
- `thesaurus[3] = {"calculate", "compute", "determine", "measure"}`
- `thesaurus[4] = {"safety", "security", "refuge"}`

### Displaying the Thesaurus

```cpp
for (int i = 0; i < numGroups; i++)
{
    cout << "Group " << i << ": ";
    for (int j = 0; j < rowSizes[i]; j++)
        cout << "[" << thesaurus[i][j] << "] ";
    cout << endl;
}
```

Prints each group's words in brackets, e.g.:
```
Group 0: [abandon] [discontinue] [vacate]
```

### Paraphrase (Word Lookup)

```cpp
cout << "\nEnter word to paraphrase: ";
string userWord;
cin >> userWord;

bool found = false;
for (int i = 0; i < numGroups; i++)
{
    if (rowSizes[i] > 0 && thesaurus[i][0] == userWord)
    {
        cout << "Replaced word: " << thesaurus[i][rowSizes[i] - 1] << endl;
        found = true;
        break;
    }
}
```

- Reads a single word from the user.
- Compares it only against the **first word** of each group (`thesaurus[i][0]`).
- If matched, outputs the **last word** of that group (`thesaurus[i][rowSizes[i] - 1]`).
- `break` stops after the first match (no duplicate keys expected).

**Design decision:** Using first word as key and last word as replacement is a simplified paraphrase convention.

### Memory Cleanup

```cpp
for (int i = 0; i < numGroups; i++)
    delete[] thesaurus[i];
delete[] thesaurus;
delete[] rowSizes;
```

Standard jagged 2D array cleanup — rows first, then the outer pointer array, then `rowSizes`.

---

## 🧪 Full Test Case Walkthrough

### Input string:
```
abandon discontinue vacate#absent missing unavailable#cable wire#calculate compute determine measure#safety security refuge
```

### After `countGroups()`:
- Counts 4 `#` symbols → `numGroups = 5`

### After splitting into `groups[]`:

| Index | Group String |
|-------|-------------|
| 0 | `"abandon discontinue vacate"` |
| 1 | `"absent missing unavailable"` |
| 2 | `"cable wire"` |
| 3 | `"calculate compute determine measure"` |
| 4 | `"safety security refuge"` |

### After `countWords()` for each group:

| Group | Words | rowSizes[i] |
|-------|-------|------------|
| 0 | abandon, discontinue, vacate | 3 |
| 1 | absent, missing, unavailable | 3 |
| 2 | cable, wire | 2 |
| 3 | calculate, compute, determine, measure | 4 |
| 4 | safety, security, refuge | 3 |

### Thesaurus display output:
```
===== Thesaurus Array =====
Group 0: [abandon] [discontinue] [vacate]
Group 1: [absent] [missing] [unavailable]
Group 2: [cable] [wire]
Group 3: [calculate] [compute] [determine] [measure]
Group 4: [safety] [security] [refuge]
```

### User enters: `"calculate"`

- Loop checks `thesaurus[0][0]` = `"abandon"` → no match
- Loop checks `thesaurus[1][0]` = `"absent"` → no match
- Loop checks `thesaurus[2][0]` = `"cable"` → no match
- Loop checks `thesaurus[3][0]` = `"calculate"` → **MATCH!**
- `rowSizes[3] - 1 = 3`, so `thesaurus[3][3]` = `"measure"`

```
Replaced word: measure
```

### User enters: `"hello"` (not in thesaurus):
```
Word not found in thesaurus.
```

---

## 🎯 Key Concepts Demonstrated

| Concept | Where Used |
|---------|-----------|
| C-style strings (`char *`) | Input string `ws`, null-terminator `'\0'` |
| Delimiter-based string parsing | Splitting by `#` in `CreateDynamicArray()` |
| State machine for word counting | `inWord` flag in `countWords()` |
| Jagged 2D array of `string` | `thesaurus` — each group has different word count |
| Output parameters via reference (`int &`, `int *&`) | `numGroups`, `rowSizes` |
| First/last element as key/value | Paraphrase lookup convention |
| Temporary heap allocation + cleanup | `groups[]` array freed before return |
| `cin >>` for single word input | No `getline()` needed for single word |
