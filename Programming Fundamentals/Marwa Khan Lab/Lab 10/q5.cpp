#include <iostream>
using namespace std;

void removeChar(char str[], char ch)
{
    int strLen = 0;
    while (str[strLen] != '\0')
    {
        strLen++;
    }

    for (int i = 0; i <= strLen; i++)
    {
        if (str[i] == ch)
        {
            for (int j = i; j <= strLen - 1; j++)
            {
                str[j] = str[j + 1];
            }
            strLen--;
        }
    }

    str[strLen] = '\0';
}

int main()
{
    const int n = 30;
    char str[n] = "Quick brown fox fox dogs.";

    removeChar(str, 'o');

    cout << str << endl;

    system("pause");
    return 0;
}