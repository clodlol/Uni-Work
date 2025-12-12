#include <iostream>
using namespace std;

int countLongestSubarray(int arr[], int size)
{
    // we count longest subarray of 1, assuming only 1 and 0s in the array
    int longest = INT_MIN;
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = i; j < size; j++)
        {
            if (arr[j] == 0)
                break;
            else
            {
                count++;
            }
        }

        if (count > longest)
            longest = count;
    }

    return longest;
}

void removeElement(int arr[], int size, int target, int out[])
{
    for (int i = 0; i < size; i++)
    {
        if (i < target)
        {
            out[i] = arr[i];
        }
        else if (i > target)
        {
            out[i - 1] = arr[i];
        }
    }
}

int main()
{
    const int n = 9;
    int arr[n] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int longest = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int currentLongest = INT_MIN; // count if we ignore abhi wala element
        if (arr[i] == 0)              // we try to ignore i and count longest array of 1
        {
            int temp[n - 1] = {0};
            removeElement(arr, n, i, temp);
            currentLongest = countLongestSubarray(temp, n - 1);
            if (currentLongest > longest)
                longest = currentLongest;
        }
    }

    cout << (longest == INT_MIN ? n - 1 : longest) << endl;

    system("pause");
    return 0;
}