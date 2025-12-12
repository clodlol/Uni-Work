#include <iostream>
using namespace std;

int main()
{
    int arr[] = {-10, 2, 0, 1, 70, 90};
    int n = sizeof(arr) / sizeof(int);

    int index = 0;
    int a = 90;

    int left = 0, right = n - 1;
    int iterationCounter = 0;
    while (true)
    {
        int mid = (right - left) / 2 + left;
        if (arr[mid] > a)
        {
            right = mid - 1;
        }
        else if (arr[mid] < a)
        {
            left = mid + 1;
        }

        if (arr[mid] == a)
        {
            cout << "Index of " << a << " is " << mid << endl;
            break;
        }

        iterationCounter++;
        if (iterationCounter > n)
        {
            cout << "Index not found" << endl;
            break;
        }
    }

    system("pause");
    return 0;
}