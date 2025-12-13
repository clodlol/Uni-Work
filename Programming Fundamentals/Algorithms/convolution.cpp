#include <iostream>
using namespace std;

int main()
{
    const int n = 8, filterLen = 3;
    int arr[n] = {1, 2, 3, 4, 5, 6, 7, 8};
    int filter[filterLen] = {3, 4, 5};

    int left = 0, right = filterLen - 1;
    while (right <= n - 1)
    {
        int filterCounter = 0, currentSum = 0;
        for (int i = left; i < right; i++)
        {
            currentSum += (arr[i] * filter[filterCounter]);
            filterCounter++;
        }

        cout << currentSum << endl;

        left++;
        right++;
    }

    cout << endl;
    system("pause");
    return 0;
}