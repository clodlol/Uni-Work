#include <iostream>
using namespace std;

int main()
{
    const int n = 9;
    int arr[n] = {1, 2, 3, 4, 6, 6, 7, 8, 9};
    int a = 6;
    int foundIndex = -1;

    int start = 0;
    int end = n - 1;
    int subLen = end - start;
    int p1 = start + (subLen / 3);
    int p2 = end - (subLen / 3);
    while (subLen >= 0)
    {
        cout << "P1: " << p1 << " P2: " << p2 << endl;

        if (a == arr[p1])
        {
            foundIndex = p1;
            break;
        }
        else if (a == arr[p2])
        {
            foundIndex = p2;
            break;
        }

        if (a < arr[p1])
        {
            // search 0...p1-1
            end = p1 - 1;
        }
        else if (a > arr[p1] && a < arr[p2])
        {
            // search p1+1...p2-1
            start = p1 + 1;
            end = p2 - 1;
        }
        else if (a > arr[p2])
        {
            // search p2+1...n-1
            start = p2 + 1;
        }

        subLen = end - start;
        p1 = start + (subLen / 3);
        p2 = end - (subLen / 3);
    }

    if (foundIndex >= 0)
    {
        cout << "Found element at " << foundIndex << endl;
    }
    else
    {
        cout << "Element not found. " << endl;
    }

    system("pause");
    return 0;
}