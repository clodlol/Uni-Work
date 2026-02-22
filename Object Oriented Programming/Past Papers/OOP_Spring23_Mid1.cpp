#include <iostream>
using namespace std;

const int M = 10, N = 10, MAX_PEST_DIV_SIZE = 100;

void printResults(const int &n, const int *const *const &pestDiv)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; pestDiv[i][j] != -1; j++)
        {
            cout << pestDiv[i][j] << " ";
        }
        cout << endl;
    }
}

int **determinePestDiv(const int p_Count[M][N], const int &startX, const int &startY)
{
    int tempStartX = startX, tempStartY = startY;
    int temp[4][MAX_PEST_DIV_SIZE] = {0};
    int p = 0, q = 0, r = 0, s = 0;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (tempStartX < 0 && tempStartY > 0)
            {
                temp[0][p++] = p_Count[i][j];
            }
            else if (tempStartX >= 0 && tempStartY > 0)
            {
                temp[1][q++] = p_Count[i][j];
            }
            else if (tempStartX < 0 && tempStartY <= 0)
            {
                temp[2][r++] = p_Count[i][j];
            }
            else if (tempStartX >= 0 && tempStartY <= 0)
            {
                temp[3][s++] = p_Count[i][j];
            }

            tempStartX++;
        }

        tempStartY--;
        tempStartX = startX;
    }

    cout << p << " " << q << " " << r << " " << s << " " << endl;

    int **pestDiv = new int *[4];
    pestDiv[0] = new int[p + 1];
    pestDiv[1] = new int[q + 1];
    pestDiv[2] = new int[r + 1];
    pestDiv[3] = new int[s + 1];

    for (int i = 0; i < p; i++)
        pestDiv[0][i] = temp[0][i];

    for (int i = 0; i < q; i++)
        pestDiv[1][i] = temp[1][i];

    for (int i = 0; i < r; i++)
        pestDiv[2][i] = temp[2][i];

    for (int i = 0; i < s; i++)
        pestDiv[3][i] = temp[3][i];

    pestDiv[0][p] = -1;
    pestDiv[1][q] = -1;
    pestDiv[2][r] = -1;
    pestDiv[3][s] = -1;

    return pestDiv;
}

int main()
{
    const int p_Count[M][N] = {{2, 9, 8, 9, 5, 25, 0, 12, 16, 3},
                               {9, 3, 5, 16, 2, 5, 16, 12, 25, 8},
                               {3, 6, 2, 25, 9, 5, 25, 12, 19, 0},
                               {6, 15, 9, 6, 3, 16, 5, 3, 19, 16},
                               {25, 8, 3, 8, 6, 25, 2, 8, 9, 9},
                               {0, 5, 6, 5, 9, 6, 9, 0, 3, 3},
                               {0, 2, 12, 2, 3, 8, 3, 16, 6, 6},
                               {0, 9, 12, 9, 6, 5, 6, 25, 25, 25},
                               {0, 3, 12, 3, 25, 2, 4, 12, 18, 18},
                               {0, 6, 12, 6, 18, 9, 4, 12, 19, 25}};

    int **pestDiv = determinePestDiv(p_Count, -4, 2);
    printResults(4, pestDiv);

    return 0;
}