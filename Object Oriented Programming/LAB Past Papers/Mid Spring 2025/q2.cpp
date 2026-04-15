#include <iostream>
using namespace std;

const int LIMIT = 5;
const int BASE = 1e10;

class HugeInt
{
private:
    int *digits{};

public:
    HugeInt()
    {
        digits = new int[LIMIT];
        for (int i = 0; i < LIMIT; ++i)
            digits[i] = 0;
    }
    HugeInt(int x)
    {
        digits = new int[LIMIT]{};

        int i = LIMIT - 1;
        while (x > 0 && i >= 0)
        {
            digits[i] = x % BASE;
            x /= BASE;
            --i;
        }
    }
    HugeInt(const HugeInt &obj)
    {
        *this = obj;
    }
    HugeInt &operator=(const HugeInt &obj)
    {
        if (digits)
            delete[] digits;

        digits = new int[LIMIT];
        for (int i = 0; i < LIMIT; ++i)
        {
            digits[i] = obj.digits[i];
        }

        return *this;
    }
    ~HugeInt()
    {
        delete[] digits;
    }

    HugeInt operator+(const HugeInt &obj) const
    {
        HugeInt temp{};
        int carry = 0;

        for (int i = LIMIT - 1; i >= 0; --i)
        {
            int sum = digits[i] + obj.digits[i] + carry;
            temp.digits[i] = sum % BASE;
            carry = sum / BASE;
        }

        return temp;
    }
    HugeInt operator*(const HugeInt &obj) const
    {
        HugeInt temp{};
        int carry = 0;

        for (int i = LIMIT - 1; i >= 0; --i)
        {
            int product = digits[i] * obj.digits[i] + carry;
            temp.digits[i] = product % BASE;
            carry = product / BASE;
        }

        return temp;
    }

    void print() const
    {
        for (int i = 0; i < LIMIT; ++i)
            cout << digits[i];
    }
};

int main()
{
    HugeInt a{INT_MAX}, b{INT_MAX};
    HugeInt c = a * b;
    c.print();

    return 0;
}