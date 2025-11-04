#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void reverseEven(int arr[], int n)
{
    for(int i = 0; i < n/2; i++)
    {
        if(i % 2 == 0)
            swap(arr[i], arr[n-1-i]);
    }
}

void reverseOdd(int arr[], int n)
{
    for(int i = 0; i < n/2; i++)
    {
        if(i % 2 != 0)
            swap(arr[i], arr[n-1-i]);
    }
}

int main()
{
    int arr[] = {3, 2, 1, 0, -1, -2, -3, 4};
    int n = sizeof(arr)/sizeof(int);

    reverseOdd(arr, n);

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}