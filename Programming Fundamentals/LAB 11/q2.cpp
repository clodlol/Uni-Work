#include <iostream>

using namespace std;

int main()
{
    const int n = 3;
    int arr[n][n] = {{-11, 99, 48}, {7, 11, 27}, {110, 0, -1}};
    cout << "Random brick strengths: " << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int element;
            cout << "Enter brick strength at position " << "(" << i+1 << ", " << j+1 << "): ";
            cin >> element;

            arr[i][j] = element;
        }
    }

    cout << endl;
    cout << "The updated strengths are: " << endl;

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