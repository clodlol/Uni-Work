#include <iostream>

using namespace std;

int main()
{
    const int l = 3, m = 3;
    int arr[l][m] = {{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};

    int a = 9;
    int right = m - 1;
    int top = 0;

    while (top < l && right >= 0)
    {
        int currentElement = a;

        if (arr[top][right] == currentElement)
        {
            cout << "Found element at (" << right << ", " << top << ")" << endl;
            break;
        }

        if (arr[top][right] > currentElement)
        {
            right--;
            continue;
        }

        if (arr[top][right] < currentElement)
        {
            top++;
            continue;
        }
    }

    system("pause");
    return 0;
}