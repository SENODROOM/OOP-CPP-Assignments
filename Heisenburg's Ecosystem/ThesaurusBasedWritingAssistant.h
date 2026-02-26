#ifndef THESAURUS_BASED_WRITING_ASSISTANT_H
#define THESAURUS_BASED_WRITING_ASSISTANT_H

#include <iostream>
#include <string>
using namespace std;

int countGroups(char *ws);
int countWords(const string &group);
string **CreateDynamicArray(char *ws, int &numGroups, int *&rowSizes);

#endif
