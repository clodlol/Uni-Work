#include <iostream>
using namespace std;

void populateMatrix(int **mat, const int &m, const int &n)
{
    for (int i = 0; i < (m * n); i++)
        mat[i / n][i % n] = rand();
}

void displayMatrix(int **mat, const int &m, const int &n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int **transposeMatrix(int **mat, const int &m, const int &n)
{
    int **trans = new int *[n];
    for (int i = 0; i < m; i++)
        trans[i] = new int[m];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            trans[j][i] = mat[i][j];
        }
    }

    return trans;
}

int main()
{
    int m = 3, n = 3;

    int **mat = new int *[m];
    for (int i = 0; i < n; i++)
        mat[i] = new int[n];

    populateMatrix(mat, m, n);
    displayMatrix(mat, m, n);

    int **trans = transposeMatrix(mat, m, n);
    displayMatrix(trans, n, m);
    return 0;
}