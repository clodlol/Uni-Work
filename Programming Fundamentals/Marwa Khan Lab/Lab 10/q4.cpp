#include <iostream>
using namespace std;

void replaceSubstring(char str[], const char oldSub[], const char newSub[])
{
    // asuming null terminated char arrays
    int strLen = 0, oldsubLen = 0, newsubLen = 0;
    while (str[strLen] != '\0')
        strLen++;
    while (oldSub[oldsubLen] != '\0')
        oldsubLen++;
    while (newSub[newsubLen] != '\0')
        newsubLen++;

    for (int i = 0; i <= (strLen - oldsubLen); i++)
    {
        bool found = true;
        for (int j = i; j < (i + oldsubLen); j++)
        {
            if (str[j] != oldSub[j - i])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            if (newsubLen < oldsubLen)
            {
                for (int j = (i + newsubLen); j < strLen; j++)
                {
                    str[j] = str[j + (oldsubLen - newsubLen)];
                }

                strLen -= (oldsubLen - newsubLen);
            }
            else if (newsubLen > oldsubLen)
            {
                for (int j = strLen; j >= (i + oldsubLen); j--)
                {
                    str[j + (newsubLen - oldsubLen)] = str[j];
                }

                strLen += (newsubLen - oldsubLen);
            }

            for (int j = i; j < (i + newsubLen); j++)
            {
                str[j] = newSub[j - i];
            }
        }
    }

    str[strLen] = '\0';
}

int main()
{
    const int n = 300;
    char str[n] = "A quick brown brown fox jumps over brown dog.";

    replaceSubstring(str, "brown", "yello");

    cout << str << endl;
    system("pause");
    return 0;
}