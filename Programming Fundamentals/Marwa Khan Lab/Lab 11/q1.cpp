#include <iostream>
using namespace std;

const int MAX_SIZE = 10;

void outputMatrix(int mat[10][10], int m, int n)
{
    // m x n matrix
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }

        cout << endl;
    }
}

int main()
{
    const int m = 3, n = 4;
    int arr[MAX_SIZE][MAX_SIZE] = {{1, 2},
                                   {5, 9, 1}};

    outputMatrix(arr, m, n);

    system("pause");
    return 0;
}