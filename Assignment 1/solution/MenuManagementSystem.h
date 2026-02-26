#ifndef MENUMANAGEMENTSYSTEM_H
#define MENUMANAGEMENTSYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 7;
const int MAX_LEN = 200;

// String manipulation functions
int stringLength(const string &s);
int stringFind(const string &s, char c);
int stringFind(const string &s, const string &substr);
string stringSubstr(const string &s, int pos, int len);
int stringToInt(const string &s);
bool customGetline(istream &input, string &line);
string trim(const string &s);
int splitLine(const string &line, string tokens[], int maxTokens);

// Menu processing functions
int categoryOrder(const string &cat);
string baseCuisine(const string &cuisine);
bool compareLess(string **arr, int a, int b);
void sortMenu(string **dynArr, int rows);
void displayItem(string **dynArr, int idx);

#endif // MENUMANAGEMENTSYSTEM_H
