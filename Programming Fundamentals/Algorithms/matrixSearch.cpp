#include <iostream>
using namespace std;

int matrixSearch(int matrix[][4], int numRows, int numCols, int seq[], int seqLen)
{
    int count = 0;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            bool found = true;
            for (int k = j; k < j + seqLen; k++)
            {
                if (matrix[i][k] != seq[k - j])
                {
                    found = false;
                }
            }

            if (found)
                count++;
        }
    }

    return count;
}

int main()
{
    const int m = 3, n = 4, seqLen = 2;
    int arr[m][n] = {{1, 2, 0, 3},
                     {0, 1, 2, 0},
                     {1, 2, 1, 2}};
    int seq[seqLen] = {1, 2};

    cout << matrixSearch(arr, m, n, seq, seqLen) << endl;

    system("pause");
    return 0;
}