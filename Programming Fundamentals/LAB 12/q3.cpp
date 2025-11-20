#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    const int l = 3, m = 3;
    int arr[l][m] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    if (l != m)
    {
        cout << "Invalid matrix order!" << endl;
        system("pause");
        return 0;
    }

    cout << "Before: " << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < l; j++)
        {
            cout << setw(3) << arr[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << "After: " << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < l; j++)
        {
            if (i <= j)
            {
                cout << setw(3) << arr[i][j];
            }
            else
            {
                cout << setw(3) << " ";
            }
        }
        cout << endl;
    }
    system("pause");
    return 0;
}