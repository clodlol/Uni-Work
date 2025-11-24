#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = b;
    b = a;
    a = temp;
}

int main()
{
    int matA[3][3] = {{3, 2, 1}, {6, 5, 4}, {99, 101, 100}};

    // row wise
    for (int i = 0; i < 3; i++)
    {
        int left = 0, right = 3 - 1;
        while (right > left)
        {
            for (int j = left; j < right; j++)
            {
                if (matA[i][j] > matA[i][j + 1])
                    swap(matA[i][j], matA[i][j + 1]);
            }
            right--;
        }

        for (int j = 0; j < 3; j++)
        {
            cout << matA[i][j] << " ";
        }

        cout << endl;
    }

    int matB[3][3] = {{5, 99, 88}, {4, 98, 88}, {3, 97, 89}};

    // column wise
    for (int j = 0; j < 3; j++)
    {
        int top = 0, bottom = 3 - 1;
        while (top < bottom)
        {
            for (int i = top; i < bottom; i++)
            {
                if (matB[i][j] > matB[i + 1][j])
                {
                    swap(matB[i][j], matB[i + 1][j]);
                }
            }
            bottom--;
        }
    }

    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matB[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int matC[3][3] = {{5, 99, 88}, {4, 98, 88}, {3, 97, 89}};

    // entire matrix
    int left = 0, right = 3 * 3 - 1;
    while (right > left)
    {
        for (int i = left; i < right; i++)
        {
            if (matC[i / 3][i % 3] > matC[(i + 1) / 3][(i + 1) % 3])
            {
                swap(matC[i / 3][i % 3], matC[(i + 1) / 3][(i + 1) % 3]);
            }
        }
        right--;
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << matC[i][j] << " ";
        }
        cout << endl;
    }

    system("pause");
    return 0;
}