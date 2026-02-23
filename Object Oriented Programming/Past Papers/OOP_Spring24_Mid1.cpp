#include <iostream>
using namespace std;

void FilterData(int **&listIntArrays, int *&sizeIntArrays, const int *const &targetSubArray, const int &lenSubArray, const int &lenListIntArrays)
{
    for (int i = 0; i < lenListIntArrays; i++)
    {
        int *temp = new int[sizeIntArrays[i]]{0};
        int tempCounter = 0;
        for (int j = 0; j < sizeIntArrays[i];)
        {
            bool found = true;
            for (int k = j; k < (j + lenSubArray); k++)
            {
                if (listIntArrays[i][k] != targetSubArray[k - j])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                j += lenSubArray;
            }
            else
            {
                temp[tempCounter++] = listIntArrays[i][j];
                j++;
            }
        }
        int *newListElement = new int[tempCounter];
        sizeIntArrays[i] = tempCounter;
        for (int j = 0; j < tempCounter; j++)
        {
            newListElement[j] = temp[j];
        }

        delete[] temp;
        temp = nullptr;
        delete[] listIntArrays[i];
        listIntArrays[i] = newListElement;
    }
}

int main()
{
    int lenList = 3;
    int *sizes = new int[lenList]{6, 5, 7};

    int **list = new int *[lenList];

    list[0] = new int[sizes[0]]{1, 2, 3, 2, 3, 4};

    list[1] = new int[sizes[1]]{2, 3, 5, 2, 3};

    list[2] = new int[sizes[2]]{9, 2, 3, 8, 2, 3, 7};

    int lenTarget = 2;
    int *target = new int[lenTarget]{2, 3};

    FilterData(list, sizes, target, lenTarget, lenList);

    for (int i = 0; i < lenList; i++)
    {
        cout << "Array " << i << ": ";
        for (int j = 0; j < sizes[i]; j++)
            cout << list[i][j] << " ";
        cout << endl;
    }

    for (int i = 0; i < lenList; i++)
        delete[] list[i];
    delete[] list;
    delete[] sizes;
    delete[] target;

    return 0;
}