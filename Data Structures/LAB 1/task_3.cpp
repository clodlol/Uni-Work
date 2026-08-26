#include <iostream>
using namespace std;

template <typename T>
void displayArray(T *arr, int size)
{
    cout << "Array: ";
    for (int i = 0; i < size; ++i)
    {
        cout << *(arr + i) << " ";
    }
    cout << "\n";
}

template <typename T>
T findMaximum(T *arr, int size)
{
    T max = *(arr);
    for (int i = 1; i < size; ++i)
    {
        if (*(arr + i) > max)
            max = *(arr + i);
    }

    return max;
}

template <typename T>
T findMinimum(T *arr, int size)
{
    T min = *(arr);
    for (int i = 1; i < size; ++i)
    {
        if (*(arr + i) < min)
            min = *(arr + i);
    }

    return min;
}

template <typename T>
void reverseArray(T *arr, int size)
{
    for (int i = 0; i < size / 2; ++i)
    {
        swap(*(arr + i), *(arr + (size - 1 - i)));
    }
}

int main()
{
    int numbers[] = {10, 20, 5, 15};
    double values[] = {2.5, 8.4, 1.2, 6.7};
    char letters[] = {'D', 'A', 'C', 'B'};

    cout << "Integer ";
    displayArray(numbers, 4);
    cout << "Max: " << findMaximum(numbers, 4) << ", Min: " << findMinimum(numbers, 4) << "\n";

    cout << "Double ";
    displayArray(values, 4);
    cout << "Max: " << findMaximum(values, 4) << ", Min: " << findMinimum(values, 4) << "\n";

    cout << "Char ";
    displayArray(letters, 4);
    cout << "Max: " << findMaximum(values, 4) << ", Min: " << findMinimum(values, 4) << "\n";

    return 0;
}