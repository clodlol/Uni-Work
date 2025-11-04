#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int arr[] = {0, -123, -1, 111, 10, 99};
    int n = sizeof(arr) / sizeof(int);

    for (int i = 0; i < n; i++)
    {
        int smallestIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[smallestIndex])
                smallestIndex = j;
        }
        swap(arr[smallestIndex], arr[i]);
    }

    cout << endl;
    cout << "The sorted array is: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}