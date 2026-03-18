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

    StringHolder(StringHolder &obj) // shallow copies
    {
        this->stringPtr = obj.stringPtr;
    }

    StringHolder(const StringHolder &obj) // deep copies
    {
        int len = stringLen(obj.stringPtr);
        this->stringPtr = new char[len + 1];
        for (int i = 0; i < len; ++i)
        {
            this->stringPtr[i] = obj.stringPtr[i];
        }
        this->stringPtr[len] = '\0';
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

int main()
{
    StringHolder s1("Hello");
    const StringHolder s2("World");
    StringHolder s3 = s1; // s3 has a shallow copy
    StringHolder s4 = s2; // s4 has a deep copy

    s3.setString("Something else");
    s3.display();
    s1.display(); // This will produce an error since s3 just deleted the memory s1 is trying to access

    s4.setString("Something else as well");
    s2.display(); // s2 still retains its contents
    return 0;
}