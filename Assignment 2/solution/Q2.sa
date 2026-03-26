#include <iostream>
#include <stdexcept>
using namespace std;

// ============================================================
// MyString — custom string class using raw dynamic memory
// No std::string used internally anywhere.
// ============================================================
class MyString
{
private:
    char *str;  // dynamically allocated, always null-terminated
    int length; // char count NOT including '\0'

    // ----------------------------------------------------------
    // Internal helper: compute length of a C-string manually
    // ----------------------------------------------------------
    static int cstrLen(const char *s)
    {
        if (!s)
            return 0;
        int len = 0;
        while (*(s + len) != '\0')
            ++len;
        return len;
    }

    // ----------------------------------------------------------
    // Internal helper: deep-copy a C-string into this object
    // ----------------------------------------------------------
    void deepCopy(const char *src, int len)
    {
        length = len;
        str = new char[length + 1];
        for (int i = 0; i <= length; ++i) // copies '\0' too
            *(str + i) = *(src + i);
    }

public:
    // ----------------------------------------------------------
    // Default constructor — empty string ""
    // ----------------------------------------------------------
    MyString()
    {
        length = 0;
        str = new char[1];
        *str = '\0';
    }

    // ----------------------------------------------------------
    // C-string constructor — deep copy of input
    // ----------------------------------------------------------
    MyString(const char *input)
    {
        if (!input)
        {
            length = 0;
            str = new char[1];
            *str = '\0';
        }
        else
        {
            deepCopy(input, cstrLen(input));
        }
    }

    // ----------------------------------------------------------
    // Copy constructor — Rule of Three
    // ----------------------------------------------------------
    MyString(const MyString &other)
    {
        deepCopy(other.str, other.length);
    }

    // ----------------------------------------------------------
    // Copy assignment — Rule of Three
    // ----------------------------------------------------------
    MyString &operator=(const MyString &other)
    {
        if (this == &other)
            return *this; // self-assignment guard
        delete[] str;
        deepCopy(other.str, other.length);
        return *this;
    }

    // ----------------------------------------------------------
    // Destructor — Rule of Three
    // ----------------------------------------------------------
    ~MyString()
    {
        delete[] str;
    }

    // ----------------------------------------------------------
    // Member functions
    // ----------------------------------------------------------

    /// lengthOfString(): returns char count (no null)
    int lengthOfString() const { return length; }

    /// display(): prints the string to stdout
    void display() const { cout << str; }

    /// countWords(): space-separated word count (handles multi-spaces)
    int countWords() const
    {
        int count = 0;
        bool inWord = false;
        for (int i = 0; i < length; ++i)
        {
            if (*(str + i) != ' ')
            {
                if (!inWord)
                {
                    ++count;
                    inWord = true;
                }
            }
            else
            {
                inWord = false;
            }
        }
        return count;
    }

    /// toUpperCase(): convert in-place using ASCII arithmetic
    void toUpperCase()
    {
        for (int i = 0; i < length; ++i)
        {
            char c = *(str + i);
            if (c >= 'a' && c <= 'z')
                *(str + i) = c - ('a' - 'A');
        }
    }

    /// toLowerCase(): convert in-place
    void toLowerCase()
    {
        for (int i = 0; i < length; ++i)
        {
            char c = *(str + i);
            if (c >= 'A' && c <= 'Z')
                *(str + i) = c + ('a' - 'A');
        }
    }

    /// toSentenceCase(): first char upper, rest lower
    void toSentenceCase()
    {
        toLowerCase();
        if (length > 0)
        {
            char c = *str;
            if (c >= 'a' && c <= 'z')
                *str = c - ('a' - 'A');
        }
    }

    /// reverse(): returns NEW MyString with chars in reverse order
    MyString reverse() const
    {
        char *buf = new char[length + 1];
        for (int i = 0; i < length; ++i)
            *(buf + i) = *(str + (length - 1 - i));
        *(buf + length) = '\0';
        MyString result(buf);
        delete[] buf;
        return result;
    }

    // ----------------------------------------------------------
    // Concatenation operators
    // ----------------------------------------------------------

    /// MyString + MyString
    MyString operator+(const MyString &other) const
    {
        int newLen = length + other.length;
        char *buf = new char[newLen + 1];
        for (int i = 0; i < length; ++i)
            *(buf + i) = *(str + i);
        for (int i = 0; i <= other.length; ++i) // includes '\0'
            *(buf + length + i) = *(other.str + i);
        MyString result(buf);
        delete[] buf;
        return result;
    }

    /// MyString + const char*
    MyString operator+(const char *other) const
    {
        return *this + MyString(other);
    }

    /// MyString += MyString — reallocate in-place
    MyString &operator+=(const MyString &other)
    {
        *this = *this + other;
        return *this;
    }

    /// MyString += const char*
    MyString &operator+=(const char *other)
    {
        *this = *this + MyString(other);
        return *this;
    }

    // ----------------------------------------------------------
    // Comparison operators — manual lexicographic comparison
    // ----------------------------------------------------------
    bool operator==(const MyString &other) const
    {
        if (length != other.length)
            return false;
        for (int i = 0; i < length; ++i)
            if (*(str + i) != *(other.str + i))
                return false;
        return true;
    }

    bool operator!=(const MyString &other) const { return !(*this == other); }

    bool operator<(const MyString &other) const
    {
        int minLen = (length < other.length) ? length : other.length;
        for (int i = 0; i < minLen; ++i)
        {
            if (*(str + i) < *(other.str + i))
                return true;
            if (*(str + i) > *(other.str + i))
                return false;
        }
        return length < other.length;
    }

    bool operator>(const MyString &other) const { return other < *this; }
    bool operator<=(const MyString &other) const { return !(*this > other); }
    bool operator>=(const MyString &other) const { return !(*this < other); }

    // ----------------------------------------------------------
    // Indexing operator [] — returns char& for read & write
    // ----------------------------------------------------------
    char &operator[](int index)
    {
        if (index < 0 || index >= length)
            throw out_of_range("Error: index out of range");
        return *(str + index);
    }

    const char &operator[](int index) const
    {
        if (index < 0 || index >= length)
            throw out_of_range("Error: index out of range");
        return *(str + index);
    }

    // ----------------------------------------------------------
    // Function call operator () — returns reversed copy
    // ----------------------------------------------------------
    MyString operator()() const
    {
        return reverse();
    }

    // ----------------------------------------------------------
    // Friend: const char* + MyString
    // ----------------------------------------------------------
    friend MyString operator+(const char *lhs, const MyString &rhs)
    {
        return MyString(lhs) + rhs;
    }

    // ----------------------------------------------------------
    // Stream operators
    // ----------------------------------------------------------

    /// >> reads a full line and stores it
    friend istream &operator>>(istream &in, MyString &ms)
    {
        // Dynamic buffer — grow as needed
        int cap = 128;
        int len = 0;
        char *buf = new char[cap];

        char c;
        // Consume any leading newline left in buffer
        if (in.peek() == '\n')
            in.get();

        while (in.get(c) && c != '\n')
        {
            if (len + 1 >= cap)
            { // grow buffer
                int newCap = cap * 2;
                char *newBuf = new char[newCap];
                for (int i = 0; i < len; ++i)
                    *(newBuf + i) = *(buf + i);
                delete[] buf;
                buf = newBuf;
                cap = newCap;
            }
            *(buf + len++) = c;
        }
        *(buf + len) = '\0';

        delete[] ms.str;
        ms.length = len;
        ms.str = new char[len + 1];
        for (int i = 0; i <= len; ++i)
            *(ms.str + i) = *(buf + i);

        delete[] buf;
        return in;
    }

    /// << prints the string
    friend ostream &operator<<(ostream &out, const MyString &ms)
    {
        out << ms.str;
        return out;
    }
};

// ============================================================
// main() — menu-driven driver
// ============================================================
int main()
{
    MyString current;
    int choice;

    do
    {
        cout << "\n============================================\n";
        cout << "     Custom Text Processing Engine\n";
        cout << "============================================\n";
        cout << " 1.  Enter new string\n";
        cout << " 2.  Display string\n";
        cout << " 3.  Show length\n";
        cout << " 4.  Count words\n";
        cout << " 5.  Convert to uppercase\n";
        cout << " 6.  Convert to lowercase\n";
        cout << " 7.  Convert to sentence case\n";
        cout << " 8.  Reverse string\n";
        cout << " 9.  Concatenate another string\n";
        cout << " 10. Compare with another string\n";
        cout << " 11. Access character using index []\n";
        cout << " 12. Test assignment operator =\n";
        cout << " 13. Test function call operator ()\n";
        cout << " 14. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try
        {
            if (choice == 1)
            {
                cout << "Enter string: ";
                cin >> current;
                cout << "Stored: " << current << "\n";
            }
            else if (choice == 2)
            {
                cout << "String: ";
                current.display();
                cout << "\n";
            }
            else if (choice == 3)
            {
                cout << "Length: " << current.lengthOfString() << "\n";
            }
            else if (choice == 4)
            {
                cout << "Word count: " << current.countWords() << "\n";
            }
            else if (choice == 5)
            {
                current.toUpperCase();
                cout << "Uppercase: " << current << "\n";
            }
            else if (choice == 6)
            {
                current.toLowerCase();
                cout << "Lowercase: " << current << "\n";
            }
            else if (choice == 7)
            {
                current.toSentenceCase();
                cout << "Sentence case: " << current << "\n";
            }
            else if (choice == 8)
            {
                MyString rev = current.reverse();
                cout << "Reversed: " << rev << "\n";
            }
            else if (choice == 9)
            {
                cout << "Enter string to concatenate: ";
                MyString other;
                cin >> other;
                current += other;
                cout << "After concatenation: " << current << "\n";
            }
            else if (choice == 10)
            {
                cout << "Enter second string to compare: ";
                MyString other;
                cin >> other;
                cout << "Equal?        " << (current == other ? "Yes" : "No") << "\n";
                cout << "Not equal?    " << (current != other ? "Yes" : "No") << "\n";
                cout << "Less than?    " << (current < other ? "Yes" : "No") << "\n";
                cout << "Greater than? " << (current > other ? "Yes" : "No") << "\n";
            }
            else if (choice == 11)
            {
                cout << "Enter index: ";
                int idx;
                cin >> idx;
                cout << "Character at [" << idx << "]: " << current[idx] << "\n";
                cout << "Modify character? (y/n): ";
                char ans;
                cin >> ans;
                if (ans == 'y' || ans == 'Y')
                {
                    cout << "Enter new character: ";
                    char nc;
                    cin >> nc;
                    current[idx] = nc;
                    cout << "Updated string: " << current << "\n";
                }
            }
            else if (choice == 12)
            {
                cout << "Enter string for assignment: ";
                MyString temp;
                cin >> temp;
                current = temp;
                cout << "After assignment: " << current << "\n";
            }
            else if (choice == 13)
            {
                MyString reversed = current();
                cout << "Reversed via (): " << reversed << "\n";
            }
            else if (choice == 14)
            {
                cout << "Exiting...\n";
            }
            else
            {
                cout << "Invalid choice. Please enter 1-14.\n";
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << "\n";
        }

    } while (choice != 14);

    return 0;
}