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
            int firstParsedVal = (startsWith4 || startsWith9) * romanArr[romanArrCounter - (startsWith4 + (2 * startsWith9))];
            int secondParsedVal = romanArr[romanArrCounter];

            return (roman + parse(firstParsedVal) + parse(secondParsedVal) + intToRoman(currNum - (secondParsedVal - firstParsedVal)));
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
    int m_numInt{};
    int m_numLen{};
    char *m_num{};

public:
    RomanNumber(char *num)
    {
        m_numLen = calculateLen(num);
        m_num = new char[m_numLen + 1];
        copyString(m_num, m_numLen + 1, num);
        m_numInt = romanToInt(m_num);
    }

    // RomanNumber(int numInt) : m_numInt{numInt}
    // {
    //     m_num = intToRoman(numInt);
    //     m_numLen = calculateLen(m_num);
    // }

    ~RomanNumber() { delete[] m_num; }

    // RomanNumber &operator=(const RomanNumber &obj)
    // {
    //     if (obj == *this)

    //         delete[] m_num;
    // }
};

int main()
{
    cout << intToRoman(3999);

    return 0;
}