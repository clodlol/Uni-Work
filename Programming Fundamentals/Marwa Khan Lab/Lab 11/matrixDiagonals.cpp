#include <iostream>
using namespace std;

int main()
{
    const int m = 4, n = 4;
    int arr[m][n] = {{1, 2, 3, 5},
                     {9, 8, 2, 1},
                     {9, 5, 6, 4},
                     {3, 4, 6, 5}};

    for (int j = n - 1; j >= 0; j--)
    {
        for (int internalCounter = 0; internalCounter <= (n - j - 1); internalCounter++)
        {
            cout << arr[internalCounter][j + internalCounter] << " ";
        }

        cout << endl;
    }

    for (int i = 1; i < m; i++)
    {
        for (int internalCounter = 0; internalCounter <= (n - i - 1); internalCounter++)
        {
            cout << arr[i + internalCounter][internalCounter] << " ";
        }

        cout << endl;
    }

    system("pause");
    return 0;
}