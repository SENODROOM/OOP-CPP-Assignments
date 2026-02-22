# 📘 Q3.cpp — Sparse Matrix Compactor: Deep Line-by-Line Explanation

---

## 📦 Header Include

```cpp
#include <iostream>
using namespace std;
```

Only `<iostream>` is needed since this program uses no files, strings (beyond console I/O), or math functions. It is a focused demonstration of **dynamic 2D array manipulation**.

---

## 🔧 Function: `countNonZero()`

```cpp
int countNonZero(int *row, int cols)
{
    int count = 0;
    for (int j = 0; j < cols; j++)
    {
        if (row[j] != 0)
            count++;
    }
    return count;
}
```

**Purpose:** Counts the number of non-zero elements in a single row (1D array).

- `int *row` — a pointer to the first element of the row. Since a 2D array's row decays to a pointer, this works seamlessly.
- Iterates through all `cols` elements.
- Increments `count` for every element that is not `0`.
- Returns the total count — this will determine how large the compact row needs to be.

**Why this matters:** In a sparse matrix (mostly zeros), allocating full-sized rows wastes memory. This count lets us allocate only as much memory as we actually need.

---

## 🔧 Function: `createCompactList()`

```cpp
int **createCompactList(int **grid, int rows, int cols, int *&rowSizes)
```

**Signature breakdown:**
- `int **grid` — the original 2D matrix (pointer to array of row pointers).
- `int rows`, `int cols` — dimensions of the grid.
- `int *&rowSizes` — a **reference to a pointer**: the function modifies the caller's pointer to point to a newly allocated array. This is an output parameter.
- Returns `int **` — the new compact 2D array.

```cpp
rowSizes = new int[rows];
for (int i = 0; i < rows; i++)
    rowSizes[i] = countNonZero(grid[i], cols);
```

- Allocates `rowSizes` as an array of `rows` integers.
- For each row `i`, counts non-zero values using `countNonZero()` and stores it in `rowSizes[i]`.

```cpp
int **compact = new int *[rows];
for (int i = 0; i < rows; i++)
{
    compact[i] = new int[rowSizes[i]];
    int idx = 0;
    for (int j = 0; j < cols; j++)
    {
        if (grid[i][j] != 0)
            compact[i][idx++] = grid[i][j];
    }
}
return compact;
```

- Allocates the outer array: `rows` row pointers.
- For each row, allocates **exactly** `rowSizes[i]` integers (not the full `cols` count).
- Iterates through the original row and copies only the non-zero values into the compact row.
- `idx++` post-increments after each assignment — fills compact positions 0, 1, 2, … sequentially.

**Key insight:** If `rowSizes[i]` is `0` (row is all zeros), `new int[0]` is valid C++ — it allocates an empty array. This is handled gracefully in the print function.

---

## 🔧 Function: `printGrid()`

```cpp
void printGrid(int **grid, int rows, int cols)
{
    cout << "Input Matrix:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << grid[i][j];
            if (j < cols - 1) cout << " ";
        }
        cout << endl;
    }
}
```

**Purpose:** Prints the original matrix with space-separated values on each row.

- The condition `if (j < cols - 1)` prevents a trailing space after the last element.
- `cout << endl` moves to the next line after each row.

---

## 🔧 Function: `printCompact()`

```cpp
void printCompact(int **compact, int rows, int *rowSizes)
{
    cout << "\nOutput Array (Compact List):" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "Shelf " << (i + 1) << ": ";
        if (rowSizes[i] == 0)
            cout << "(empty)";
        for (int j = 0; j < rowSizes[i]; j++)
        {
            cout << compact[i][j];
            if (j < rowSizes[i] - 1) cout << " ";
        }
        cout << endl;
    }
}
```

**Purpose:** Displays the compact array using a "Shelf" metaphor (1-indexed for user friendliness).

- If a row has `rowSizes[i] == 0`, prints `"(empty)"` to indicate the shelf is blank.
- Otherwise prints all compacted values, space-separated, without a trailing space.

---

## 🏁 `main()` — Step by Step

### Hard-coded Matrix

```cpp
const int ROWS = 5;
const int COLS = 6;

int data[ROWS][COLS] = {
    {2, 3, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 0},
    {1, 1, 1, 2, 0, 2},
    {5, 0, 0, 0, 10, 0}
};
```

A 5×6 integer matrix is declared as a **static 2D array** on the stack. Each row represents a "shelf" of inventory; zeros mean "empty slot."

### Converting to Dynamic 2D Array

```cpp
int **grid = new int *[ROWS];
for (int i = 0; i < ROWS; i++)
{
    grid[i] = new int[COLS];
    for (int j = 0; j < COLS; j++)
        grid[i][j] = data[i][j];
}
```

- Allocates `grid` as a dynamic 2D array on the **heap**.
- Why? To practice dynamic allocation — `createCompactList()` expects `int **`.
- Copies data from the stack array into the heap array element by element.

### Creating the Compact List

```cpp
int *rowSizes = nullptr;
int **compact = createCompactList(grid, ROWS, COLS, rowSizes);
```

- `rowSizes` starts as `nullptr`; the function allocates and populates it.
- `compact` receives the new jagged array (each row has a different size).

### Printing

```cpp
printGrid(grid, ROWS, COLS);
printCompact(compact, ROWS, rowSizes);
```

### Memory Cleanup

```cpp
for (int i = 0; i < ROWS; i++)
{
    delete[] grid[i];
    delete[] compact[i];
}
delete[] grid;
delete[] compact;
delete[] rowSizes;
```

**Order matters:**
1. Delete each row array first (inner allocations).
2. Then delete the outer pointer arrays.
3. Then delete `rowSizes`.

If you `delete[] grid` before `delete[] grid[i]`, you lose the row pointers and the inner arrays become **memory leaks**.

---

## 🧪 Full Test Case Walkthrough

### Input Matrix:
```
Row 0: 2 3 1 0 0 0
Row 1: 0 0 0 1 1 0
Row 2: 1 0 0 0 0 0
Row 3: 1 1 1 2 0 2
Row 4: 5 0 0 0 10 0
```

### `countNonZero()` results:

| Row | Elements | Non-Zero Count |
|-----|----------|----------------|
| 0 | 2,3,1,0,0,0 | 3 |
| 1 | 0,0,0,1,1,0 | 2 |
| 2 | 1,0,0,0,0,0 | 1 |
| 3 | 1,1,1,2,0,2 | 5 |
| 4 | 5,0,0,0,10,0 | 2 |

So `rowSizes = [3, 2, 1, 5, 2]`.

### Memory allocated for compact:

- `compact[0]` → `new int[3]`
- `compact[1]` → `new int[2]`
- `compact[2]` → `new int[1]`
- `compact[3]` → `new int[5]`
- `compact[4]` → `new int[2]`

### Compact values copied:

| Shelf | Compact Values |
|-------|----------------|
| Shelf 1 | 2 3 1 |
| Shelf 2 | 1 1 |
| Shelf 3 | 1 |
| Shelf 4 | 1 1 1 2 2 |
| Shelf 5 | 5 10 |

### Console Output:

```
Input Matrix:
2 3 1 0 0 0
0 0 0 1 1 0
1 0 0 0 0 0
1 1 1 2 0 2
5 0 0 0 10 0

Output Array (Compact List):
Shelf 1: 2 3 1
Shelf 2: 1 1
Shelf 3: 1
Shelf 4: 1 1 1 2 2
Shelf 5: 5 10
```

### Memory savings illustrated:

| Row | Original slots | Compact slots | Saved |
|-----|---------------|---------------|-------|
| 0 | 6 | 3 | 3 |
| 1 | 6 | 2 | 4 |
| 2 | 6 | 1 | 5 |
| 3 | 6 | 5 | 1 |
| 4 | 6 | 2 | 4 |
| **Total** | **30** | **13** | **17 (57%)** |

---

## 🎯 Key Concepts Demonstrated

| Concept | Where Used |
|---------|-----------|
| Sparse matrix compaction | Core algorithm |
| Jagged (ragged) 2D arrays | `compact` — each row has a different size |
| Output parameters via reference-to-pointer (`int *&`) | `rowSizes` in `createCompactList()` |
| `new int[0]` — zero-length allocation | Rows that are all zeros |
| Correct order of `delete[]` | Memory cleanup in `main()` |
| Pointer arithmetic / row-as-pointer | `int *row` parameter in `countNonZero()` |
