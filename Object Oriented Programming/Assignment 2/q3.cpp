#include <iostream>
#include "string_utils.h"
#include "math_utils.h"
using namespace std;

int deparse(char a)
{
    switch (a)
    {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0;
    }
}

char parse(int x)
{
    switch (x)
    {
    case 1:
        return 'I';
    case 5:
        return 'V';
    case 10:
        return 'X';
    case 50:
        return 'L';
    case 100:
        return 'C';
    case 500:
        return 'D';
    case 1000:
        return 'M';
    default:
        return 0;
    }
}

int romanToInt(const string &num)
{
    int len = num.size();
    int conversion = deparse(num[len - 1]);
    for (int i = len - 2; i >= 0; --i)
    {
        if (deparse(num[i]) >= deparse(num[i + 1]))
        {
            conversion += deparse(num[i]);
        }
        else
        {
            conversion -= deparse(num[i]);
        }
    }

    return conversion;
}

string intToRoman(int n)
{
    if (n <= 0 || n > 3999)
        return "";

    string roman;
    int currNum = n;

    int romanArr[] = {1, 5, 10, 50, 100, 500, 1000};
    int sizeRomanArr = sizeof(romanArr) / sizeof(int);

    bool startsWith4 = startsWithK(currNum, 4);
    bool startsWith9 = startsWithK(currNum, 9);

    int romanArrCounter = sizeRomanArr - 1;
    while (true)
    {
        if (currNum % romanArr[romanArrCounter - (startsWith4 || startsWith9)] < currNum)
        {
            int firstVal = (startsWith4 || startsWith9) * romanArr[romanArrCounter - (startsWith4 + (2 * startsWith9))];
            int secondVal = romanArr[romanArrCounter];

            return (roman + parse(firstVal) + parse(secondVal) + intToRoman(currNum - (secondVal - firstVal)));
        }
        else
        {
            romanArrCounter--;
        }
    }
}

class RomanNumber
{
private:
    string m_num{};
    int m_numInt{};

public:
    RomanNumber(const string &num)
    {
        if (romanToInt(num) == 0)
        {
            cout << "Invalid roman number.\n";
            return;
        }

        int inputInt = romanToInt(num);
        if (num != intToRoman(inputInt)) // There are no alternatives to any roman number
        {
            cout << "Invalid roman number.\n";
            return;
        }

        m_num = num;
        m_numInt = inputInt;
    }

    RomanNumber(int numInt)
    {
        if (numInt <= 0 || numInt > 3999)
        {
            cout << "Invalid roman number.\n";
            return;
        }

        m_numInt = numInt;
        m_num = intToRoman(m_numInt);
    }

    const string &getRoman() const { return m_num; }
    int getInt() const { return m_numInt; }

    RomanNumber operator+(const RomanNumber &obj) const { return RomanNumber{m_numInt + obj.m_numInt}; }
    RomanNumber operator+(int numInt) const { return RomanNumber{m_numInt + numInt}; }
    friend RomanNumber operator+(int numInt, const RomanNumber &obj) { return RomanNumber{numInt + obj.m_numInt}; }

    RomanNumber operator-(const RomanNumber &obj) const { return RomanNumber{m_numInt - obj.m_numInt}; }
    RomanNumber operator-(int numInt) const { return RomanNumber{m_numInt - numInt}; }
    friend RomanNumber operator-(int numInt, const RomanNumber &obj) { return RomanNumber{numInt - obj.m_numInt}; }

    RomanNumber operator*(const RomanNumber &obj) const { return RomanNumber{m_numInt * obj.m_numInt}; }
    RomanNumber operator*(int numInt) const { return RomanNumber{m_numInt * numInt}; }
    friend RomanNumber operator*(int numInt, const RomanNumber &obj) { return RomanNumber{numInt * obj.m_numInt}; }

    RomanNumber operator/(const RomanNumber &obj) const
    {
        if (obj.m_numInt == 0)
        {
            cout << "Roman division by zero.\n";
            return RomanNumber{0};
        }

        return RomanNumber{m_numInt / obj.m_numInt};
    }
    RomanNumber operator/(int numInt) const
    {
        if (numInt == 0)
        {
            cout << "Roman division by zero.\n";
            return RomanNumber{0};
        }

        return RomanNumber{m_numInt / numInt};
    }
    friend RomanNumber operator/(int numInt, const RomanNumber &obj)
    {
        if (obj.m_numInt == 0)
        {
            cout << "Roman division by zero.\n";
            return RomanNumber{0};
        }

        return RomanNumber{numInt / obj.m_numInt};
    }

    bool operator==(const RomanNumber &obj) const { return m_numInt == obj.m_numInt; }
    bool operator==(int numInt) const { return m_numInt == numInt; }
    friend bool operator==(int numInt, const RomanNumber &obj) { return numInt == obj.m_numInt; }

    bool operator!=(const RomanNumber &obj) const { return !(*this == obj); }
    bool operator!=(int numInt) const { return !(*this == numInt); }
    friend bool operator!=(int numInt, const RomanNumber &obj) { return !(numInt == obj); }

    bool operator>(const RomanNumber &obj) const { return m_numInt > obj.m_numInt; }
    bool operator>(int numInt) const { return m_numInt > numInt; }
    friend bool operator>(int numInt, const RomanNumber &obj) { return numInt > obj.m_numInt; }

    bool operator<(const RomanNumber &obj) const { return m_numInt < obj.m_numInt; }
    bool operator<(int numInt) const { return m_numInt < numInt; }
    friend bool operator<(int numInt, const RomanNumber &obj) { return numInt < obj.m_numInt; }

    RomanNumber &operator++()
    {
        m_numInt++;
        m_num = intToRoman(m_numInt);
        return *this;
    }
    RomanNumber operator++(int)
    {
        RomanNumber temp = *this;
        m_numInt++;
        m_num = intToRoman(m_numInt);
        return temp;
    }

    RomanNumber &operator--()
    {
        m_numInt--;
        m_num = intToRoman(m_numInt);
        return *this;
    }
    RomanNumber operator--(int)
    {
        RomanNumber temp = *this;
        m_numInt--;
        m_num = intToRoman(m_numInt);
        return temp;
    }
};

int main()
{
    RomanNumber n1{"IXIX"};
    cout << n1.getInt();

    system("pause");
    return 0;
}