#include <iostream>
using namespace std;

const int MAX_SIZE = 10;

void findOccurrences(char arr[MAX_SIZE][MAX_SIZE], int m, int n, char substr[])
{
    int substrLen = 0;
    while (substr[substrLen] != '\0')
    {
        substrLen++;
    }

    // left to right
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j <= (n - substrLen); j++)
        {
            int found = true;
            for (int k = j; k < (j + substrLen); k++)
            {
                if (arr[i][k] != substr[k - j])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                cout << "Found an occurrence at (" << i << ", " << j << ") L -> R" << endl;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = n - 1; j >= (substrLen); j--)
        {
            bool found = true;
            for (int k = j; k > (j - substrLen); k--)
            {
                if (arr[i][k] != substr[j - k])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                cout << "Found an occurrence at (" << i << ", " << j << ") R -> L" << endl;
            }
        }
    }

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i <= (m - substrLen); i++)
        {
            bool found = true;
            for (int k = i; k < (i + substrLen); k++)
            {
                if (arr[k][j] != substr[k - i])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                cout << "Found an occurrence at (" << i << ", " << j << ") T -> B" << endl;
            }
        }
    }

    for (int j = 0; j < n; j++)
    {
        for (int i = m - 1; i >= (substrLen); i--)
        {
            bool found = true;
            for (int k = i; k > (i - substrLen); k--)
            {
                if (arr[k][j] != substr[i - k])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                cout << "Found an occurrence at (" << i << ", " << j << ") B -> T" << endl;
            }
        }
    }
}

void findDiagonalOccurrences(char arr[MAX_SIZE][MAX_SIZE], int m, int n, char substr[])
{
    int substrLen = 0;
    while (substr[substrLen] != '\0')
    {
        substrLen++;
    }

    // TL -> BR
    for (int _mainCounter = -(n - 1); _mainCounter <= (m - 1); _mainCounter++)
    {
        int mainCounter = (_mainCounter < 0 ? -_mainCounter : _mainCounter);
    }
}

int main()
{
    const int m = 6, n = 6;
    char arr[MAX_SIZE][MAX_SIZE] = {{'B', 'B', 'M', 'B', 'B', 'B'},
                                    {'C', 'M', 'A', 'G', 'I', 'C'},
                                    {'I', 'B', 'G', 'B', 'B', 'B'},
                                    {'G', 'B', 'I', 'B', 'B', 'B'},
                                    {'A', 'B', 'C', 'B', 'B', 'B'},
                                    {'M', 'C', 'I', 'G', 'A', 'M'}};

    findDiagonalOccurrences(arr, m, n, "BIBI");

    system("pause");
    return 0;
}