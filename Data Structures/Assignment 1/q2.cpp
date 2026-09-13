#include <iostream>
using namespace std;

// Time Complexity: O(n^3)
void mystery1(int n)
{
    int **a = new int *[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[i * i + 1];
        for (int j = 0; j < i; j++)
        {
            int *temp = new int[j + 1];
            for (int k = 0; k <= j; k++)
                temp[k] = k;
            delete[] temp;
        }
    }
}

// Time Complexity: O(2^n)
void mystery2(int n)
{
    int size = 1;
    for (int i = 0; i < n; i++)
    {
        size *= 2;
    }
    int *arr = new int[size];
}

// Time Complexity: O(n^2)
void fun(int n)
{
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = i;
    for (int i = 0; i < n; i++)
    {
        int *row = new int[i + 1];
        for (int j = 0; j <= i; j++)
            row[j] = arr[i] + j;
        // row is NOT deleted here
        arr[i] = row[0];
    }
    int *temp = new int[n * n];
    delete[] temp;
}