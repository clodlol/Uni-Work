#include <iostream>
using namespace std;

int main()
{
    const int n = 6;
    int arr[n] = {1, 7, 5, 4, 6, 3};

    int rangeStart = 0;
    int rangeEnd = 7;
    int sum = 0;

    for (int i = rangeStart; i <= rangeEnd; i++)
        sum += i;

    for (int i = 0; i < n; i++)
    {
        sum -= arr[i];
    }

    cout << "Missing number: " << sum << endl;

    system("pause");
    return 0;
}