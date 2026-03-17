#include <iostream>
using namespace std;

int stringLen(const char *s)
{
    int c = 0;
    while (s[c] != '\0')
        c++;

    return c;
}

class StringInfo
{
    char *str;
    int length;

public:
    StringInfo(const char *s)
    {
        int len = stringLen(s);
        this->length = len;
        this->str = new char[len + 1];
        for (int i = 0; i < len; ++i)
        {
            this->str[i] = s[i];
        }
        this->str[len] = '\0';
    }

    ~StringInfo()
    {
        delete[] str;
    }

    void display() const
    {
        cout << "The string length is: " << this->length << "\n";
        cout << "The string is: " << str << "\n";
    }
};

int main()
{
    const char *s = "mystring123";
    StringInfo strInfo(s);
    strInfo.display();

    return 0;
}