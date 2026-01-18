#include <iostream>
using namespace std;

int main()
{
    const int n = 6;
    int arr[n] = {-999, 300, 200, -999, -999, -999};

    int largestSum = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int subCounter = 1;
        while (subCounter < n - i)
        {
            int currentSum = 0;
            for (int j = i; j <= i + subCounter; j++)
            {
                cout << arr[j] << " ";
                currentSum += arr[j];
            }

            cout << " | ";

            if (currentSum > largestSum)
                largestSum = currentSum;
            subCounter++;
        }

        cout << endl;
    }

    cout << largestSum << endl;

    system("pause");
    return 0;
}