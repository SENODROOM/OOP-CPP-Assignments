#ifndef INVENTORY_CLEANUP_H
#define INVENTORY_CLEANUP_H

#include <iostream>
using namespace std;

int countNonZero(int *row, int cols);
int **createCompactList(int **grid, int rows, int cols, int *&rowSizes);
void printGrid(int **grid, int rows, int cols);
void printCompact(int **compact, int rows, int *rowSizes);

#endif
