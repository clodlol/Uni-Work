#include <iostream>
#include <vector>
using namespace std;

class RecursiveNumberConverter
{
private:
    void decimalToBinaryHelper(int number, vector<int> &v)
    {
        if (number == 0)
            return;
        v.insert(v.begin(), number % 2);
        decimalToBinaryHelper(number / 2, v);
    }

    void decimalToOctalHelper(int number, vector<int> &v)
    {
        if (number == 0)
            return;
        v.insert(v.begin(), number % 8);
        decimalToOctalHelper(number / 8, v);
    }

    int sumOfDigitsHelper(int number)
    {
        if (number == 0)
            return 0;
        return (number % 10) + sumOfDigitsHelper(number / 10);
    }

    int countDigitsHelper(int number)
    {
        if (number == 0)
            return 0;
        return 1 + countDigitsHelper(number / 10);
    }

    void reverseNumberHelper(int number, int &res)
    {
        if (number == 0)
            return;
        res *= 10;
        res += number % 10;
        reverseNumberHelper(number / 10, res);
    }

public:
    void decimalToBinary(int number)
    {
        vector<int> binaryDigits;
        decimalToBinaryHelper(number, binaryDigits);
    }
    void decimalToOctal(int number)
    {
        vector<int> octalDigits;
        decimalToOctalHelper(number, octalDigits);
    }

    int sumOfDigits(int number)
    {
        return sumOfDigitsHelper(number);
    }
    int countDigits(int number)
    {
        return countDigitsHelper(number);
    }

    void reverseNumber(int number)
    {
        int res = 0;
        reverseNumberHelper(number, res);
    }
};
