#include <iostream>
using namespace std;

int trailingSpaces(char row[])
{
    int len = 0;
    while (row[len] != '\0')
    {
        len++;
    }

    int trailCounter = 0;
    while (row[trailCounter] == ' ')
    {
        trailCounter++;
    }

    return trailCounter;
}

int leadingSpaces(char row[])
{
    int len = 0;
    while (row[len] != '\0')
    {
        len++;
    }

    int leadCounter = len - 1;
    while (row[leadCounter] == ' ')
    {
        leadCounter--;
    }

    return (len - leadCounter - 1);
}

int lenStr(char row[])
{
    int len = 0;
    while (row[len] != '\0')
    {
        len++;
    }

    return len;
}

int main()
{
    const int r = 5;
    char matrix[r][20] = {
        "  hello world    ",
        "    example    ",
        "      test      ",
        "      ",
        "nothingToTrim",
    };

    for (int i = 0; i < r; i++)
    {
        int leadTrimmedLen = lenStr(matrix[i]) - leadingSpaces(matrix[i]);
        int trailSpaces = trailingSpaces(matrix[i]);
        for (int j = 0; j < (leadTrimmedLen - trailSpaces); j++)
        {
            matrix[i][j] = matrix[i][j + trailSpaces];
        }

        matrix[i][leadTrimmedLen - trailSpaces] = '\0';
    }

    for (int i = 0; i < r; i++)
    {
        cout << matrix[i] << endl;
    }

    system("pause");
    return 0;
}