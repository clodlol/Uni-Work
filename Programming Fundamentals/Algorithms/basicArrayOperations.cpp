#include <iostream>
using namespace std;

int main()
{
    const int n = 6;
    int arr[6] = {-1, 0, 99, 100, -123, 1200};

    int equilibriumIndex = 0;
    for (int right = 0; right < n; right++)
    {
        int leftSum = 0;
        int rightSum = 0;
        for (int i = 0; i <= right; i++)
        {
            leftSum += arr[i];
        }
        for (int i = right + 1; i < n; i++)
        {
            rightSum += arr[i];
        }
        if (rightSum == leftSum)
        {
            equilibriumIndex = right + 1;
            break;
        }
    }

    cout << endl;
    return 0;
}