#include <iostream>

using namespace std;

int main()
{
    const int n = 3;
    int arr[n][n] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << endl;
    
    arr[1][1] = 4;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    system("pause");
    return 0;
}