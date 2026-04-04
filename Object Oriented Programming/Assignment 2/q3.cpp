#include <iostream>
using namespace std;

int calculateLen(char *arr)
{
    int c = 0;
    while (arr[c] != '\0')
        c++;

    return c;
}

void copyString(char *destination, int destAllocSize, char *source)
// we have to know the amount of allocated memory here, else the program throws
{
    if (destAllocSize <= 0)
    {
        cout << "Not enough allocated memory to copy string. \n"; // return an error here?
        return;
    }

    int sourceLen = calculateLen(source);
    destination[destAllocSize - 1] = '\0';
    for (int i = 0; i < destAllocSize - 1; ++i)
        destination[i] = source[i];
}

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

int romanToInt(char *num)
{
    int len = calculateLen(num);
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

char *intToRoman(int numInt)
{
    for (int i = numInt, mult = 1; i != 0; i /= 10, mult *= 10)
    {
        int currDigit = i % 10;
        if (currDigit == 0)
            continue;

        // find roman of currDigit*mult
    }

    return nullptr;
}

string romanize(int n)
{
    string roman;
    int romanArr[] = {1, 5, 10, 50, 100, 500, 1000};
    int romanArrLen = sizeof(romanArr) / sizeof(int);
    int currNum = n;

    for (int j = romanArrLen - 1; j >= 0;)
    {
        if (currNum % romanArr[j] < currNum)
        {
            roman += parse(romanArr[j]);
            currNum -= romanArr[j];
        }
        else
        {
            --j;
        }
    }

    return roman;
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
    cout << romanize(3999);

    return 0;
}