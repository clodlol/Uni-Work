#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    const int l = 2, m = 3;
    int arr[l][m] = {{1, 2, 3}, {4, 5, 6}};
    int trans[m][l] = {{0}};

    for(int j = 0; j < m; j++)
    {
        for(int i = 0; i < l; i++)
        {
            trans[j][i] = arr[i][j];
        }
    }

    cout << "Matrix: " << endl;
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(3) << arr[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << "Transpose: " << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < l; j++)
        {
            cout << setw(3) << trans[i][j];
        }
        cout << endl;
    }
    system("pause");
    return 0;
}