#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    const int l = 2, m = 9;
    char arr[l][m] = {"abcdefgh", "ijklmnop"};
    char out[l][m] = {{'_'}};

    const int rotationAmount = 1;

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            if (j < rotationAmount)
            {
                out[i][j] = arr[i][m - 1 + j - rotationAmount]; // m-1 points to empty character string, subtracting rotationAmount leads us to the start of the rotated string char, and adding j allows us to paste it in
            }
            else
            {
                out[i][j] = arr[i][j - rotationAmount];
            }
        }
    }

    for (int i = 0; i < l; i++)
        out[l][m - 1] = '\0';

    cout << "Before rotation: " << endl;

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << "After rotation: " << endl;

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << out[i][j];
        }
        cout << endl;
    }
    system("pause");
    return 0;
}