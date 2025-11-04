#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int kthSmallest(int arr[], int n, int k)
{
    if(k > n) return INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int smallest = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[smallest])
            {
                smallest = j;
            }
        }
        swap(arr[smallest], arr[i]);
        k--;

        if (k == 0)
        {
            return arr[i];
        }
    }
}

int kthLargest(int arr[], int n, int k)
{
    if(k > n) return INT_MAX;
    for (int i = 0; i < n; i++)
    {
        int largest = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[largest])
            {
                largest = j;
            }
        }
        swap(arr[largest], arr[i]);
        k--;

        if (k == 0)
        {
            return arr[i];
        }
    }
}

int main()
{
    int k = 2;
    int arr[] = {1, 2, 3, 0, -1, -11};
    int n = sizeof(arr) / sizeof(int);

    cout << kthLargest(arr, n, k) << endl;
}