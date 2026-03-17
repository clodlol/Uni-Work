#include <iostream>
using namespace std;

int stringLen(const char *s)
{
    int c = 0;
    while (s[c] != '\0')
        c++;

    return c;
}

class StringHolder
{
    char *stringPtr;

public:
    StringHolder(const char *s)
    {
        int len = stringLen(s);
        stringPtr = new char[len + 1];
        for (int i = 0; i < len; ++i)
        {
            stringPtr[i] = s[i];
        }
        stringPtr[len] = '\0';
    }

    StringHolder(StringHolder &obj)
    {
    }

    ~StringHolder()
    {
        delete[] stringPtr;
    }

    void setString(const char *s)
    {
        int len = stringLen(s);
        delete[] stringPtr;
        stringPtr = new char[len + 1];
        for (int i = 0; i < len; ++i)
        {
            stringPtr[i] = s[i];
        }
        stringPtr[len] = '\0';
    }

    void display() const
    {
        cout << "Current stored string: " << stringPtr << "\n";
    }
};