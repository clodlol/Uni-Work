#include <iostream>
using namespace std;

int *inputArray(int &size)
{
    cout << "Enter size of array: ";
    cin >> size;
    int *ptr = new int[size]{0};
    for (int i = 0; i < size; i++)
    {
        cout << "Enter element no. " << (i) << ": ";
        cin >> ptr[i];
    }
    return ptr;
}

void outputArray(const int *const &ptr, const int &size)
{
    for (int i = 0; i < size; i++)
    {
        cout << ptr[i] << " ";
    }
    cout << endl;
}

int countSortedDistinct(const int *const &arr, const int &size)
{
    int c = 1;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] != arr[i - 1])
            c++;
    }
    return c;
}

int *compressArray(int *&arr, int &size)
{
    int count = countSortedDistinct(arr, size), c = 0;

    int *compressed = new int[count]{0};

    compressed[c++] = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] != arr[i - 1])
            compressed[c++] = arr[i];
    }

    size = count;
    return compressed;
}

int *intersection(int *setA, const int &sizeA, int *setB, const int &sizeB, int &sizeInter)
{
    sizeInter = 0;

    int tempSize = min(sizeA, sizeB);
    int *temp = new int[tempSize]{0};

    for (int i = 0; i < sizeA; i++)
    {
        bool found = false, dupe = false;
        for (int j = 0; j < sizeB; j++)
        {
            if (setB[j] == setA[i])
            {
                found = true;
                break;
            }
        }

        for (int j = 0; j < sizeInter; j++)
        {
            if (temp[j] == setA[i])
            {
                dupe = true;
                break;
            }
        }

        if (found && !dupe)
        {
            temp[sizeInter++] = setA[i];
        }
    }

    int *inter = new int[sizeInter]{0};
    for (int i = 0; i < sizeInter; i++)
        inter[i] = temp[i];

    delete[] temp;
    temp = nullptr;

    return inter;
}

int main()
{
    int sizeA = 0, sizeB = 0, sizeInter = 0;
    int *setA = inputArray(sizeA);
    int *setB = inputArray(sizeB);
    int *inter = intersection(setA, sizeA, setB, sizeB, sizeInter);
    outputArray(inter, sizeInter);
    return 0;
}