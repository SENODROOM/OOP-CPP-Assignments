#include <iostream>
#include <string>
using namespace std;

int countGroups(char *ws)
{
    int count = 1;
    for (int i = 0; ws[i] != '\0'; i++)
    {
        if (ws[i] == '#')
        {
            count++;
        }
    }
    return count;
}

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

string **CreateDynamicArray(char *ws, int &numGroups, int *&rowSizes)
{
    numGroups = countGroups(ws);
    rowSizes = new int[numGroups];

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
        {
            arr[i][wi] = word;
        }
    }

    delete[] groups;
    return arr;
}

int main()
{
    char ws[] = "abandon discontinue vacate#absent missing unavailable#cable wire#calculate compute determine measure#safety security refuge";

    int numGroups = 0;
    int *rowSizes = nullptr;
    string **thesaurus = CreateDynamicArray(ws, numGroups, rowSizes);

    cout << "===== Thesaurus Array =====" << endl;
    for (int i = 0; i < numGroups; i++)
    {
        cout << "Group " << i << ": ";
        for (int j = 0; j < rowSizes[i]; j++)
        {
            cout << "[" << thesaurus[i][j] << "] ";
        }
        cout << endl;
    }

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
    if (!found)
    {
        cout << "Word not found in thesaurus." << endl;
    }

    for (int i = 0; i < numGroups; i++)
    {
        delete[] thesaurus[i];
    }
    delete[] thesaurus;
    delete[] rowSizes;

    return 0;
}