#include <iostream>
using namespace std;

const int CITY_MAX = 100;

int countPassengers(int cityMap[CITY_MAX][CITY_MAX], int size, int startRow, int startCol)
{
    // we will assume the starting position is based on 0 index, and is valid for given size
    int count = 0;
    int i = startRow, j = startCol;
    while (i < size)
    {
        while (j < size)
        {
            count += cityMap[i][j];
            if (j + 1 == size || cityMap[i][j + 1] == -1)
            {
                break;
            }

            j++;
        }
        if (i + 1 == size || cityMap[i + 1][j] == -1)
        {
            if (i + 1 == size && j == size - 1)
            {
                return count;
            }
            return -1;
        }

        i++;
    }

    return count;
}

int main()
{
    const int size = 4;
    int map[CITY_MAX][CITY_MAX] = {{0, 1, 0, -1},
                                   {0, 2, 0, 7},
                                   {2, 5, 0, 0},
                                   {0, 3, 2, 0}};
    cout << countPassengers(map, size, 0, 0) << endl;

    system("pause");
    return 0;
}