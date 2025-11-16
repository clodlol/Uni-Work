#include <iostream>

using namespace std;

int main()
{
    const int l = 3, m = 3;
    int arr[l][m] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    if (l != m)
    {
        cout << "Diagonals do not exist for non square matrices!" << endl;
        return 0;
    }

    int sumPrimary = 0;
    int sumSecondary = 0;
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == j)
            {
                sumPrimary += arr[i][j];
            }
            if (i + j == l - 1)
            {
                sumSecondary += arr[i][j];
            }
        }
    }

    cout << "Primary diagonal sum: " << sumPrimary << endl;
    cout << "Secondary diagonal sum: " << sumSecondary << endl;

    system("pause");
    return 0;
}