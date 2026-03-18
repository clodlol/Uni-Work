#include <iostream>
using namespace std;

int stringLen(const char *s)
{
    int c = 0;
    while (s[c] != '\0')
        c++;

    return c;
}

class StringArray
{
    char **strings;
    int size;

public:
    StringArray(int arraySize)
    {
        this->size = arraySize;
        this->strings = new char *[arraySize];
        for (int i = 0; i < size; ++i)
            this->strings[i] = nullptr;
    }

    ~StringArray()
    {
        for (int i = 0; i < size; ++i)
        {
            delete[] strings[i];
        }
        delete[] strings;
    }

    void setString(int index, const char *s)
    {
        if (index >= size)
            return;

        int len = stringLen(s);
        delete[] strings[index];
        strings[index] = new char[len + 1];
        for (int i = 0; i < len; ++i)
        {
            strings[index][i] = s[i];
        }

        strings[index][len] = '\0';
    }

    const char *getString(int index) const
    {
        if (index >= size)
            return nullptr;

        return strings[index];
    }
};

int main()
{
    StringArray dict(3);
    dict.setString(0, "Hello");
    cout << "String at index 0: " << dict.getString(0) << "\n";

    return 0;
}