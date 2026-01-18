#include <iostream>
using namespace std;

int main()
{
    int arr[] = {0, 70, -11, -100, 85};
    int n = sizeof(arr) / sizeof(int);

    for (int i = 1; i < n; i++)
    {
        int temp = arr[i];
        int leftBound = i - 1;

        bool inserted = false;
        for (int j = leftBound; j >= 0; j--)
        {
            if (arr[j] > temp)
            {
                arr[j + 1] = arr[j];
            }
            else
            {
                arr[j + 1] = temp;
                inserted = true;
                break;
            }
        }

        if (!inserted)
        {
            arr[0] = temp;
        }
    }

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    system("pause");
    return 0;
}