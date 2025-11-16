#include <iostream>

using namespace std;

int main()
{
    const int l = 3, m = 3;
    int arr[l][m] = {{3, 7, 2}, {8, 1, 5}, {6, 9, 4}};
    int largest = arr[0][0];
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] > largest)
                largest = arr[i][j];
        }
    }

    cout << "Largest element: " << largest << endl;

    system("pause");
    return 0;
}