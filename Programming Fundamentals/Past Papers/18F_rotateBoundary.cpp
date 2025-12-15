#include <iostream>
using namespace std;

int main()
{
    const int m = 5, n = 5;
    char arr[m][n] = {{'A', 'B', 'C', 'D', 'E'},
                      {'F', 'A', 'B', 'C', 'D'},
                      {'G', 'F', 'A', 'B', 'C'},
                      {'H', 'G', 'F', 'A', 'B'},
                      {'I', 'H', 'G', 'F', 'A'}};

    char topLeft = arr[0][0];
    char botRight = arr[m - 1][n - 1];
    for (int j = 0; j < n - 1; j++)
    {
        arr[0][j] = arr[0][j + 1];
        arr[m - 1][n - j - 1] = arr[m - 1][n - j - 2];
    }
    for (int i = 0; i < m - 2; i++)
    {
        arr[i][n - 1] = arr[i + 1][n - 1];
        arr[n - i - 1][0] = arr[n - i - 2][0];
    }

    arr[1][0] = topLeft;
    arr[m - 2][n - 1] = botRight;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }

    system("pause");
    return 0;
}