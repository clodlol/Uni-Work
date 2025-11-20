#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    const int l = 2, m = 9;
    char arr[l][m] = {"b0b- thE", "builDer!"};
    char clean[l][m] = {{' '}};

    for (int i = 0, ci = 0; i < l && ci < l; i++)
    {
        for (int j = 0, cj = 0; j < m && cj < m; j++)
        {
            if (isalpha(arr[i][j]))
            {
                if (islower(arr[i][j]))
                {
                    clean[ci][cj] = toupper(arr[i][j]);
                }
                else
                {
                    clean[ci][cj] = arr[i][j];
                }
                cj++;
            }
            else if (arr[i][j] == '\0')
            {
                clean[ci][cj] = arr[i][j];
                cj++;
            }
        }
        ci++;
    }
    
    cout << "Before cleaning: " << endl;
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << "After cleaning: " << endl;
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << clean[i][j];
        }
        cout << endl;
    }
    system("pause");
    return 0;
}