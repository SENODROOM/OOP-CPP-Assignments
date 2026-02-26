#include "InventoryCleanup.h"

int countNonZero(int *row, int cols)
{
    int count = 0;
    for (int j = 0; j < cols; j++)
    {
        if (row[j] != 100)
        {
            count++;
        }
    }
    return count;
}

int **createCompactList(int **grid, int rows, int cols, int *&rowSizes)
{
    rowSizes = new int[rows];
    for (int i = 0; i < rows; i++)
    {
        rowSizes[i] = countNonZero(grid[i], cols);
    }
    int **compact = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        compact[i] = new int[rowSizes[i]];
        int idx = 0;
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] != 100)
            {
                compact[i][idx++] = grid[i][j];
            }
        }
    }
    return compact;
}

void printGrid(int **grid, int rows, int cols)
{
    cout << "Input Matrix:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << grid[i][j];
            if (j < cols - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void printCompact(int **compact, int rows, int *rowSizes)
{
    cout << "\nOutput Array (Compact List):" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "Shelf " << (i + 1) << ": ";
        if (rowSizes[i] == 0)
        {
            cout << "(empty)";
        }
        for (int j = 0; j < rowSizes[i]; j++)
        {
            cout << compact[i][j];
            if (j < rowSizes[i] - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    int ROWS, COLS;

    cout << "Enter number of rows: ";
    cin >> ROWS;
    cout << "Enter number of columns: ";
    cin >> COLS;

    // Create dynamic grid
    int **grid = new int *[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        grid[i] = new int[COLS];
    }

    // Get user input with data[0][0] style display
    cout << "\nEnter matrix elements:" << endl;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << "data[" << i << "][" << j << "]: ";
            cin >> grid[i][j];
        }
    }

    printGrid(grid, ROWS, COLS);

    int *rowSizes = nullptr;
    int **compact = createCompactList(grid, ROWS, COLS, rowSizes);

    printCompact(compact, ROWS, rowSizes);

    for (int i = 0; i < ROWS; i++)
    {
        delete[] grid[i];
        delete[] compact[i];
    }
    delete[] grid;
    delete[] compact;
    delete[] rowSizes;

    return 0;
}