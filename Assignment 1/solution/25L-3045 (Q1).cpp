#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 7;
const int MAX_LEN = 200;

string trim(const string &s)
{
    int start = 0, end = (int)s.size() - 1;
    while (start <= end && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n'))
    {
        start++;
    }
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n'))
    {
        end--;
    }
    if (start > end)
    {
        return "";
    }
    return s.substr(start, end - start + 1);
}

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

int categoryOrder(const string &cat)
{
    if (cat == "Appetizer")
        return 0;
    if (cat == "Main Course")
        return 1;
    if (cat == "Dessert")
        return 2;
    return 3;
}

string baseCuisine(const string &cuisine)
{
    int pos = cuisine.find('-');
    if (pos != (int)string::npos)
        return cuisine.substr(0, pos);
    return cuisine;
}

bool compareLess(string **arr, int a, int b)
{
    string ca = baseCuisine(arr[a][1]);
    string cb = baseCuisine(arr[b][1]);
    if (ca != cb)
        return ca < cb;
    if (arr[a][4] != arr[b][4])
        return arr[a][4] < arr[b][4];
    int oa = categoryOrder(arr[a][0]);
    int ob = categoryOrder(arr[b][0]);
    if (oa != ob)
        return oa < ob;
    int pa = arr[a][3].empty() ? 0 : stoi(arr[a][3]);
    int pb = arr[b][3].empty() ? 0 : stoi(arr[b][3]);
    return pa < pb;
}

void sortMenu(string **dynArr, int rows)
{
    // Bubble sort
    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < rows - i - 1; j++)
        {
            if (!compareLess(dynArr, j, j + 1))
            {
                // Swap pointers
                string *temp = dynArr[j];
                dynArr[j] = dynArr[j + 1];
                dynArr[j + 1] = temp;
            }
        }
    }
}

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

int main()
{
    // ---- Step 1: Read file into static 2D char array ----
    string staticArr[MAX_ROWS][MAX_COLS];
    int rowCount = 0;

    ifstream fin;
    string pathsToTry[] = {
        "Q1.txt",
        "solution/Q1.txt",
        "Assignment 1/solution/Q1.txt",
        "Assignments/Assignment 1/solution/Q1.txt",
        "C:/Software Engineering/Semester 2/Object Oriented Programming/Assignments/Assignment 1/solution/Q1.txt"};
    for (int p = 0; p < 5; p++)
    {
        fin.open(pathsToTry[p]);
        if (fin.is_open())
        {
            cout << "Opened file: " << pathsToTry[p] << endl;
            break;
        }
    }
    if (!fin.is_open())
    {
        cout << "Error: Could not open Q1.txt in any expected location." << endl;
        cout << "Edit the absolute path in the code to match your system." << endl;
        return 1;
    }

    string line;
    while (getline(fin, line) && rowCount < MAX_ROWS)
    {
        line = trim(line);
        if (line.empty())
            continue;
        string tokens[MAX_COLS];
        int count = splitLine(line, tokens, MAX_COLS);
        for (int j = 0; j < MAX_COLS; j++)
        {
            staticArr[rowCount][j] = (j < count) ? tokens[j] : "";
        }
        rowCount++;
    }
    fin.close();

    cout << "Read " << rowCount << " records from file." << endl;

    // ---- Step 2: Create dynamic 2D string array ----
    // Each row has MAX_COLS + 1 columns (last column = null marker via empty string sentinel)
    int DCOLS = MAX_COLS + 1; // last col is null marker
    string **dynArr = new string *[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        dynArr[i] = new string[DCOLS];
        for (int j = 0; j < MAX_COLS; j++)
        {
            dynArr[i][j] = staticArr[i][j];
        }
        dynArr[i][MAX_COLS] = "\0"; // null marker as empty/null string
    }

    // ---- Step 3: Sort ----
    sortMenu(dynArr, rowCount);

    // ---- Step 4 & 5: Display sorted results ----
    cout << "\n========== SORTED MENU ==========\n"
         << endl;
    cout << "Sorted by: Cuisine Type -> Restaurant Name -> Category -> Price\n"
         << endl;
    for (int i = 0; i < rowCount; i++)
    {
        cout << "Item #" << (i + 1) << ":" << endl;
        displayItem(dynArr, i);
    }

    // ---- Search Feature ----
    cout << "\n========== SEARCH BY CUISINE TYPE ==========\n"
         << endl;
    cout << "Enter cuisine type to search (e.g., Mexican, Experimental, Fusion): ";
    string searchCuisine;
    getline(cin, searchCuisine);
    searchCuisine = trim(searchCuisine);

    cout << "\nResults for cuisine containing \"" << searchCuisine << "\":\n"
         << endl;
    bool found = false;
    for (int i = 0; i < rowCount; i++)
    {
        string cuisine = dynArr[i][1];
        // Check if cuisine starts with or equals the search term
        if (cuisine == searchCuisine ||
            (cuisine.size() > searchCuisine.size() && cuisine.substr(0, searchCuisine.size()) == searchCuisine && cuisine[searchCuisine.size()] == '-') ||
            (cuisine.size() > searchCuisine.size() && cuisine.find(searchCuisine) == 0))
        {
            displayItem(dynArr, i);
            found = true;
        }
    }
    if (!found)
    {
        cout << "No items found for cuisine: " << searchCuisine << endl;
    }

    // ---- Bonus: Export to file ----
    ofstream fout("C:/Software Engineering/Semester 2/Object Oriented Programming/Assignments/Assignment 1/solution/sorted_menu.txt");
    if (!fout)
    {
        cout << "\nWarning: Could not create sorted_menu.txt" << endl;
    }
    else
    {
        fout << "========== ORGANIZED MENU ==========\n\n";
        string lastCategory = "";
        for (int i = 0; i < rowCount; i++)
        {
            if (dynArr[i][0] != lastCategory)
            {
                lastCategory = dynArr[i][0];
                fout << "\n*" << lastCategory << "*\n";
            }
            fout << "  " << dynArr[i][2]
                 << "  |  Price: " << dynArr[i][3]
                 << "  |  Restaurant: " << dynArr[i][4]
                 << "  |  Cook: " << (dynArr[i][5].empty() ? "[missing]" : dynArr[i][5])
                 << "  |  Calories: " << (dynArr[i][6].empty() ? "[missing]" : dynArr[i][6])
                 << "\n";
        }
        fout.close();
        cout << "\nSorted menu exported to sorted_menu.txt" << endl;
        cout << "Both files (menu_data.txt and sorted_menu.txt) are saved in the SAME folder as your .exe" << endl;
    }

    // ---- Cleanup ----
    for (int i = 0; i < rowCount; i++)
    {
        delete[] dynArr[i];
    }
    delete[] dynArr;

    return 0;
}