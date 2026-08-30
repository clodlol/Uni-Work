#pragma once

#include <iostream>
using namespace std;

template <typename T>
void merge(T *arr, int low, int high, int mid)
{
    if (low >= high)
    {
        return;
    }

    int size = high - low;
    T *tempArr = new T[size + 1];
    int tempCtr = 0;

    int leftPtr = low;
    int rightPtr = mid + 1;

    while (leftPtr <= mid || rightPtr <= high)
    {
        if (leftPtr > mid && rightPtr <= high)
        {
            tempArr[tempCtr++] = arr[rightPtr++];
            continue;
        }

        if (rightPtr > high && leftPtr <= mid)
        {
            tempArr[tempCtr++] = arr[leftPtr++];
            continue;
        }

        if (arr[leftPtr] < arr[rightPtr])
        {
            tempArr[tempCtr++] = arr[leftPtr++];
        }
        else if (arr[leftPtr] > arr[rightPtr])
        {
            tempArr[tempCtr++] = arr[rightPtr++];
        }
        else
        {
            tempArr[tempCtr++] = arr[leftPtr++];
            tempArr[tempCtr++] = arr[rightPtr++];
        }
    }

    for (int i = low; i <= high; ++i)
    {
        arr[i] = tempArr[i - low];
    }

    delete[] tempArr;
}

template <typename T>
void mergeSort(T *arr, int low, int high)
{
    if (low >= high)
    {
        return;
    }

    for (int width = 1; width <= high; width *= 2)
    {
        for (int i = low; i <= high; i += (2 * width))
        {
            merge(arr, i, min(i + 2 * width - 1, high), i + width - 1);
        }
    }
}