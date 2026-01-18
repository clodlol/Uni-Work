#include <iostream>
using namespace std;

void findOccurrences(char str[], char subStr[], int index[], int sizeIndex)
{
    // assuming str and subStr are null terminated
    int strLen = 0;
    while (str[strLen] != '\0')
    {
        strLen++;
    }

    int substrLen = 0;
    while (subStr[substrLen] != '\0')
    {
        substrLen++;
    }

    int indexCounter = 0;
    for (int i = 0; i <= (strLen - substrLen); i++)
    {
        bool found = true;
        for (int j = i; j < (i + substrLen); j++)
        {
            if (str[j] != subStr[j - i])
            {
                found = false;
                break;
            }
        }

        if (found && indexCounter < (sizeIndex - 1))
        {
            index[indexCounter++] = i;
        }
    }

    index[indexCounter] = -1;
}

int main()
{
    const int sizeIndex = 4;
    int index[sizeIndex] = {0};
    findOccurrences("hello, hello hi, hello", "hello", index, sizeIndex);

    for (int i = 0; i < sizeIndex; i++)
        cout
            << index[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}