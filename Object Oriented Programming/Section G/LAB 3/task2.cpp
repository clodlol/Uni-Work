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
            int input = -1;
            while (input < 0 || input > 1)
            {
                cout << "[" << i << "][" << j << "]: ";
                cin >> input;
            }

            mat[i][j] = input;
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
    for (int i = 0; i < m; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (mat[j][i] == 1)
                count++;
        }

        cout << count << " ";
    }
    cout << endl;
    return 0;
}