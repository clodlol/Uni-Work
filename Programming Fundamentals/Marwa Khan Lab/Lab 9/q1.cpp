#include <iostream>
using namespace std;

int main()
{
    const int n = 7;
    int arr[n] = {101, 205, 333, 410, 512, 678, 789};
    int a = 410;
    int index = 0;

    int end = n - 1;
    int start = 0;
    int range = end - start;
    int p1 = start + (range / 3);
    int p2 = end - (range / 3);

    while ((p2 - p1) >= 0)
    {
        if (arr[p1] == a)
        {
            index = p1;
            break;
        }
        else if (arr[p2] == a)
        {
            index = p2;
            break;
        }

        if (a < arr[p1])
        {
            end = p1 - 1;
        }
        else if (a > arr[p1] && a < arr[p2])
        {
            end = p2 - 1;
            start = p1 + 1;
        }
        else if (a > arr[p2])
        {
            start = p2 + 1;
        }

        range = end - start;
        p1 = start + (range / 3);
        p2 = end - (range / 3);
    }

    cout << "Found element at index " << index << endl;

    system("pause");
    return 0;
}