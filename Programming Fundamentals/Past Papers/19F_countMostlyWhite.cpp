#include <iostream>
using namespace std;

const int IMAGE_MAX = 100;

int countMostlyWhite(int image[IMAGE_MAX][IMAGE_MAX], int m, int n, int c)
{
    int mostlyWhiteCount = 0;
    int mostlyWhite = (c * c) / 2;
    for (int i = 0; i <= (m - c); i++)
    {
        for (int j = 0; j <= (n - c); j++)
        {
            int count = 0;
            for (int k = i; (k - i) < c; k++)
            {
                for (int l = j; (l - j) < c; l++)
                {
                    if (image[k][l] == 1)
                        count++;
                }
            }

            if (count >= mostlyWhite)
            {
                mostlyWhiteCount++;
            }
        }
    }

    return mostlyWhiteCount;
}

int main()
{
    const int m = 5, n = 4, k = 3;
    int image[IMAGE_MAX][IMAGE_MAX] = {{0, 0, 1, 0},
                                       {0, 1, 0, 1},
                                       {0, 0, 0, 1},
                                       {1, 0, 1, 0},
                                       {0, 1, 1, 1}};
    cout << countMostlyWhite(image, m, n, k) << endl;

    system("pause");
    return 0;
}