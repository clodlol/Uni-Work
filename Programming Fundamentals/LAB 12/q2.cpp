#include <iostream>
#include <iomanip>
using namespace std;

void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

int main()
{
    const int adjOrder = 2;
    int arr[adjOrder][adjOrder] = {{1, 2}, {3, 4}};

    cout << "Matrix: " << endl;
    for (int i = 0; i < adjOrder; i++)
    {
        for (int j = 0; j < adjOrder; j++)
        {
            cout << setw(3) << arr[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < adjOrder; i++)
    {
        for (int j = 0; j < adjOrder; j++)
        {
            if (i != j)
            {
                arr[i][j] = -arr[i][j];
            }

            if (i == 0 && j == 0)
            {
                swap(arr[i][i], arr[i + 1][i + 1]);
            }
        }
    }

    cout << endl;
    cout << "Adjoint: " << endl;
    for (int i = 0; i < adjOrder; i++)
    {
        for (int j = 0; j < adjOrder; j++)
        {
            cout << setw(3) << arr[i][j];
        }
        cout << endl;
    }

    system("pause");
    return 0;
}