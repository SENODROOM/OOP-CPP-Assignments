#include <iostream>
#include <stdexcept>
using namespace std;

int gcd(int a, int b)
{
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    return b == 0 ? a : gcd(b, a % b);
}

class Rational
{
private:
    int numerator;
    int denominator;

public:
    void reduce()
    {
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
        int g = gcd(numerator, denominator);
        if (g != 0)
        {
            numerator /= g;
            denominator /= g;
        }
    }

    Rational() : numerator(0), denominator(1) {}

    Rational(int num, int den)
    {
        if (den == 0)
            throw invalid_argument("Error: denominator cannot be zero");
        numerator = num;
        denominator = den;
        reduce();
    }

    Rational(int num) : numerator(num), denominator(1) {}

    Rational(const Rational &other)
        : numerator(other.numerator), denominator(other.denominator) {}

    double toDecimal() const
    {
        return static_cast<double>(numerator) / denominator;
    }
    Rational reciprocal() const
    {
        if (numerator == 0)
            throw logic_error("Error: cannot take reciprocal of zero");
        return Rational(denominator, numerator);
    }

    void display() const
    {
        cout << numerator << "/" << denominator;
    }

    Rational operator+(const Rational &other) const
    {
        return Rational(numerator * other.denominator + other.numerator * denominator,
                        denominator * other.denominator);
    }

    Rational operator-(const Rational &other) const
    {
        return Rational(numerator * other.denominator - other.numerator * denominator,
                        denominator * other.denominator);
    }

    Rational operator*(const Rational &other) const
    {
        return Rational(numerator * other.numerator,
                        denominator * other.denominator);
    }

    Rational operator/(const Rational &other) const
    {
        if (other.numerator == 0)
            throw invalid_argument("Error: division by zero rational");
        return Rational(numerator * other.denominator,
                        denominator * other.numerator);
    }

    Rational operator+(int n) const { return *this + Rational(n); }
    Rational operator-(int n) const { return *this - Rational(n); }
    Rational operator*(int n) const { return *this * Rational(n); }
    Rational operator/(int n) const { return *this / Rational(n); }

    Rational &operator+=(const Rational &other)
    {
        *this = *this + other;
        return *this;
    }
    Rational &operator-=(const Rational &other)
    {
        *this = *this - other;
        return *this;
    }
    Rational &operator*=(const Rational &other)
    {
        *this = *this * other;
        return *this;
    }
    Rational &operator/=(const Rational &other)
    {
        *this = *this / other;
        return *this;
    }

    bool operator==(const Rational &other) const
    {
        return numerator * other.denominator == other.numerator * denominator;
    }
    bool operator!=(const Rational &other) const { return !(*this == other); }
    bool operator<(const Rational &other) const
    {
        return numerator * other.denominator < other.numerator * denominator;
    }
    bool operator>(const Rational &other) const { return other < *this; }
    bool operator<=(const Rational &other) const { return !(*this > other); }
    bool operator>=(const Rational &other) const { return !(*this < other); }

    Rational &operator++()
    {
        numerator += denominator;
        reduce();
        return *this;
    }

    Rational operator++(int)
    {
        Rational temp(*this);
        numerator += denominator;
        reduce();
        return temp;
    }

    Rational &operator--()
    {
        numerator -= denominator;
        reduce();
        return *this;
    }

    Rational operator--(int)
    {
        Rational temp(*this);
        numerator -= denominator;
        reduce();
        return temp;
    }

    Rational operator()() const
    {
        return reciprocal();
    }

    friend Rational operator+(int n, const Rational &r) { return Rational(n) + r; }
    friend Rational operator-(int n, const Rational &r) { return Rational(n) - r; }
    friend Rational operator*(int n, const Rational &r) { return Rational(n) * r; }
    friend Rational operator/(int n, const Rational &r) { return Rational(n) / r; }

    friend istream &operator>>(istream &in, Rational &r)
    {
        int n, d;
        in >> n >> d;
        if (d == 0)
        {
            cout << "Error: denominator cannot be zero\n";
            r = Rational(0, 1);
        }
        else
        {
            r = Rational(n, d);
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, const Rational &r)
    {
        out << r.numerator << "/" << r.denominator;
        return out;
    }
};

Rational readRational(const string &prompt)
{
    while (true)
    {
        cout << prompt;
        int n, d;
        cin >> n >> d;
        try
        {
            return Rational(n, d);
        }
        catch (const exception &e)
        {
            cout << e.what() << " — please try again.\n";
        }
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\n============================================\n";
        cout << "       Rational Number System\n";
        cout << "============================================\n";
        cout << " 1.  Add two rational numbers\n";
        cout << " 2.  Subtract two rational numbers\n";
        cout << " 3.  Multiply two rational numbers\n";
        cout << " 4.  Divide two rational numbers\n";
        cout << " 5.  Compound assignment operations\n";
        cout << " 6.  Compare two rational numbers\n";
        cout << " 7.  Convert to decimal\n";
        cout << " 8.  Reciprocal (member function)\n";
        cout << " 9.  Prefix & Postfix Increment\n";
        cout << " 10. Prefix & Postfix Decrement\n";
        cout << " 11. Function call operator ()\n";
        cout << " 12. Operations with integers\n";
        cout << " 13. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try
        {
            if (choice == 1)
            {
                Rational a = readRational("Enter first rational (num den): ");
                Rational b = readRational("Enter second rational (num den): ");
                cout << "Result: " << (a + b) << "\n";
            }
            else if (choice == 2)
            {
                Rational a = readRational("Enter first rational (num den): ");
                Rational b = readRational("Enter second rational (num den): ");
                cout << "Result: " << (a - b) << "\n";
            }
            else if (choice == 3)
            {
                Rational a = readRational("Enter first rational (num den): ");
                Rational b = readRational("Enter second rational (num den): ");
                cout << "Result: " << (a * b) << "\n";
            }
            else if (choice == 4)
            {
                Rational a = readRational("Enter first rational (num den): ");
                Rational b = readRational("Enter second rational (num den): ");
                cout << "Result: " << (a / b) << "\n";
            }
            else if (choice == 5)
            {
                Rational r = readRational("Enter rational (num den): ");
                cout << "Original: " << r << "\n";
                Rational other = readRational("Enter operand for += (num den): ");
                r += other;
                cout << "After +=: " << r << "\n";
                other = readRational("Enter operand for -= (num den): ");
                r -= other;
                cout << "After -=: " << r << "\n";
                other = readRational("Enter operand for *= (num den): ");
                r *= other;
                cout << "After *=: " << r << "\n";
                other = readRational("Enter operand for /= (num den): ");
                r /= other;
                cout << "After /=: " << r << "\n";
            }
            else if (choice == 6)
            {
                Rational a = readRational("Enter first rational (num den): ");
                Rational b = readRational("Enter second rational (num den): ");
                cout << "Equal?        " << (a == b ? "Yes" : "No") << "\n";
                cout << "Not equal?    " << (a != b ? "Yes" : "No") << "\n";
                cout << "Less than?    " << (a < b ? "Yes" : "No") << "\n";
                cout << "Greater than? " << (a > b ? "Yes" : "No") << "\n";
                cout << "Less/equal?   " << (a <= b ? "Yes" : "No") << "\n";
                cout << "Greater/eq?   " << (a >= b ? "Yes" : "No") << "\n";
            }
            else if (choice == 7)
            {
                Rational r = readRational("Enter rational (num den): ");
                cout << "Decimal value: " << r.toDecimal() << "\n";
            }
            else if (choice == 8)
            {
                Rational r = readRational("Enter rational (num den): ");
                cout << "Reciprocal: " << r.reciprocal() << "\n";
            }
            else if (choice == 9)
            {
                Rational r = readRational("Enter rational (num den): ");
                cout << "Original:       " << r << "\n";
                Rational s = r++;
                cout << "After r++ — s (old): " << s << ", r (new): " << r << "\n";
                ++r;
                cout << "After ++r:      " << r << "\n";
            }
            else if (choice == 10)
            {
                Rational r = readRational("Enter rational (num den): ");
                cout << "Original:       " << r << "\n";
                Rational s = r--;
                cout << "After r-- — s (old): " << s << ", r (new): " << r << "\n";
                --r;
                cout << "After --r:      " << r << "\n";
            }
            else if (choice == 11)
            {
                Rational r = readRational("Enter rational (num den): ");
                cout << "Reciprocal via (): " << r() << "\n";
            }
            else if (choice == 12)
            {
                Rational r = readRational("Enter rational (num den): ");
                int n;
                cout << "Enter integer: ";
                cin >> n;
                cout << "r + n = " << (r + n) << "\n";
                cout << "r - n = " << (r - n) << "\n";
                cout << "r * n = " << (r * n) << "\n";
                cout << "n + r = " << (n + r) << "\n";
                cout << "n - r = " << (n - r) << "\n";
                cout << "n * r = " << (n * r) << "\n";
            }
            else if (choice == 13)
            {
                cout << "Exiting...\n";
            }
            else
            {
                cout << "Invalid choice. Please enter 1-13.\n";
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << "\n";
        }

    } while (choice != 13);

    return 0;
}