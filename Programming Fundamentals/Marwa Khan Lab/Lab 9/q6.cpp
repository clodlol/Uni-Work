#include <iostream>
using namespace std;

int main()
{
    const int n = 6;
    int arr[n] = {1, 7, 5, 4, 6, 3};
    int k = 3;

    int shifted[n] = {0};

    k %= n;
    for (int i = 0; i < n; i++)
    {
        if (i < k)
        {
            shifted[i] = arr[n - k + i];
        }
        else
        {
            shifted[i] = arr[i - k];
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << shifted[i] << " ";
    }
    cout << endl;

    system("pause");
    return 0;
}