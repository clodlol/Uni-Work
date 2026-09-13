#include <iostream>
using namespace std;

// Time Complexity: O(n)
void p1(int n)
{
    int count = 0;
    for (int i = 1; i < n; i = i * 3)
    {
        for (int j = 0; j < i; ++j)
        {
            count++;
        }
    }
    cout << count << endl;
}

// Time Complexity: O(log^2 n)
void p2(int n)
{
    int i = 1;
    while (i <= n)
    {
        int j = 1;
        while (j <= i)
        {
            cout << ".";
            j = j * 2;
        }
        i = i * 2;
    }
}

// Time Complexity: O(n log n)
void mystery(int n)
{
    for (int i = 1; i <= n; i *= 2)
    {
        for (int j = i; j <= n; j += i)
        {
            int k = j;
            while (k > 0)
            {
                k /= 2;
            }
        }
    }
}

// Time Complexity: O(log^2 n)
void p4(int n)
{
    int i = 1;
    while (i <= n)
    {
        int j = 1;
        while (j <= i)
        {
            cout << ".";
            j = j * 2;
        }
        i = i * 2;
    }
}

// Time Complexity: O(n^2)
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Time Complexity: O(n^5)
void p6(int n)
{
    int sum = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < i * i; j++)
        {
            for (int k = 0; k < j; k++)
            {
                sum++;
            }
        }
    }
}

// Time Complexity: O(log^3 n)
void mystery7(int n)
{
    for (int i = 1; i <= n; i *= 2)
    {
        int x = 1;
        while (x <= n)
        {
            for (int j = 1; j <= x; j *= 2)
            {
                cout << "*";
            }
            x *= 2;
        }
    }
}

// Time Complexity: O(n)
int sqrt(int N)
{
    int d;
    for (d = 0; d * d <= N; d++)
    {
    }
    return d - 1;
}
bool primeNumber(int n)
{
    bool isPrime = true;
    for (int d = 2; d <= sqrt(n); ++d)
    {
        if (n % d == 0)
            return false;
    }
    return true;
}