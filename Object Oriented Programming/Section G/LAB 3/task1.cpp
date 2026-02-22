#include <iostream>
using namespace std;

int **inputMatrix(const int &m, const int &n)
{
    int **mat = new int *[m];

    for (int i = 0; i < m; i++)
    {
        mat[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            cout << "[" << i << "][" << j << "]: ";
            cin >> mat[i][j];
        }
    }

    return mat;
}

int main()
{
    int m = 0, n = 0;
    cout << "Enter the number of rows: ";
    while (m <= 0)
        cin >> m;
    cout << "Enter the number of columns: ";
    while (n <= 0)
        cin >> n;

    int **mat = inputMatrix(m, n);
    for (int i = 0; i < m * n; i++)
        if ((i / n) == (i % n))
            cout << *(*(mat + (i / n)) + (i % n)) << " ";

    return 0;
}