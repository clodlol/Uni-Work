#include <iostream>
using namespace std;

const int MAX_SIZE = 10;

void input(int mat1[MAX_SIZE][MAX_SIZE], int mat2[MAX_SIZE][MAX_SIZE], int r1, int r2, int c1, int c2)
{
    // matrix 1
    cout << "======== MATRIX 1 ========" << endl;
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            cin >> mat1[i][j];
        }
    }
    cout << endl;

    // matrix 2
    cout << "======== MATRIX 2 ========" << endl;
    for (int i = 0; i < r2; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            cin >> mat2[i][j];
        }
    }
    cout << endl;
}

void printDiagonals(int mat[MAX_SIZE][MAX_SIZE], int r, int c)
{
    for (int j = c - 1; j >= 0; j--)
    {
        for (int i = 0; i <= (c - 1 - j); i++)
        {
            cout << mat[i][i + j] << " ";
        }
        cout << endl;
    }

    for (int i = 1; i < r; i++)
    {
        for (int j = 0; j <= (r - 1 - i); j++)
        {
            cout << mat[i + j][j] << " ";
        }
        cout << endl;
    }
}

void add(int mat1[MAX_SIZE][MAX_SIZE], int mat2[MAX_SIZE][MAX_SIZE],
         int res[MAX_SIZE][MAX_SIZE], int r1, int r2, int rRes, int c1, int c2, int cRes)
{
    if ((r1 != r2) || (c1 != c2))
    {
        cout << "Invalid order." << endl;
        return;
    }

    if (r1 != rRes || c1 != cRes)
    {
        cout << "Invalid resultant order." << endl;
        return;
    }

    for (int i = 0; i < rRes; i++)
    {
        for (int j = 0; j < cRes; j++)
        {
            res[i][j] = (mat1[i][j] + mat2[i][j]);
        }
    }
}

void multiply(int mat1[MAX_SIZE][MAX_SIZE], int mat2[MAX_SIZE][MAX_SIZE], int r1, int r2, int c1, int c2, int res[MAX_SIZE][MAX_SIZE], int rRes, int cRes)
{
    if (c1 != r1)
    {
        cout << "Invalid order." << endl;
        return;
    }

    if ((rRes != r1) || (cRes != c2))
    {
        cout << "Invalid resultant order." << endl;
        return;
    }

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            for (int k = 0; k < c1; k++)
            {
                res[i][j] += (mat1[i][k] * mat2[k][i]);
            }
        }
    }
}

void columnSort(int mat[MAX_SIZE][MAX_SIZE], int r, int c)
{
    for (int j = 0; j < c; j++)
    {
        bool sorted = false;
        do
        {
            sorted = true;
            for (int i = 0; i < r - 1; i++)
            {
                if (mat[i][j] > mat[i + 1][j])
                {
                    swap(mat[i][j], mat[i + 1][j]);
                    sorted = false;
                }
            }
        } while (!sorted);
    }
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    const int m = 4, n = 3;
    int mat1[MAX_SIZE][MAX_SIZE] = {{1, 2, 3},
                                    {4, 5, 6},
                                    {0, 0, 0},
                                    {7, 8, 9}};

    printDiagonals(mat1, m, n);

    system("pause");
    return 0;
}