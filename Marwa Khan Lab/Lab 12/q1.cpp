#include <iostream>
using namespace std;

int main()
{
    const int m = 6, n = 6, seqLen = 5;
    char arr[m][n] = {{'B', 'B', 'M', 'B', 'B', 'B'},
                      {'C', 'M', 'A', 'G', 'I', 'C'},
                      {'I', 'B', 'G', 'B', 'B', 'B'},
                      {'G', 'B', 'I', 'B', 'B', 'B'},
                      {'A', 'B', 'C', 'B', 'B', 'B'},
                      {'M', 'C', 'I', 'G', 'A', 'M'}};
    char seq[seqLen] = {'M', 'A', 'G', 'I', 'C'};

    for (int i = 0; i < m; i++)
    {
        // left to right
        for (int j = 0; j <= n - seqLen; j++)
        {
            bool found = true;
            int seqCounter = 0;
            for (int k = j; k < j + seqLen; k++)
            {
                if (arr[i][k] != seq[seqCounter++])
                    found = false;
            }

            if (found)
                cout << "Found word at row " << (i) << " col " << j << endl;
        }

        // right to left
        for (int j = n - 1; j >= seqLen - 1; j--)
        {
            bool found = true;
            int seqCounter = 0;
            for (int k = j; k > j - seqLen; k--)
            {
                if (arr[i][k] != seq[seqCounter++])
                    found = false;
            }

            if (found)
                cout << "Found word at row " << (i) << " col " << j << endl;
        }
    }

    for (int j = 0; j < n; j++)
    {
        // top to bottom
        for (int i = 0; i < m; i++)
        {
            bool found = true;
            int seqCounter = 0;
            for (int k = i; k < i + seqLen; k++)
            {
                if (arr[k][j] != seq[seqCounter++])
                    found = false;
            }

            if (found)
                cout << "Found word at col " << (j) << " row " << i << endl;
        }

        // bottom to top
        for (int i = m; i >= seqLen - 1; i--)
        {
            bool found = true;
            int seqCounter = 0;
            for (int k = i; k > i - seqLen; k--)
            {
                if (arr[k][j] != seq[seqCounter++])
                    found = false;
            }

            if (found)
                cout << "Found word at col " << (j) << " row " << i << endl;
        }
    }

    system("pause");
    return 0;
}