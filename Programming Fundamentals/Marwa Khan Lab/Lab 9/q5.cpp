#include <iostream>
using namespace std;

int main()
{
    const int n = 6;
    int arr[n] = {1, 7, 1, 4, 7, 3};
    bool appeared[n] = {false};

    for (int i = 0; i < n; i++)
    {
        bool found = false;
        if (appeared[i])
            continue;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] == arr[i])
            {
                appeared[j] = true;
                found = true;
            }
        }

        if (found)
            cout << "Duplicate found: " << arr[i] << endl;
    }

    system("pause");
    return 0;
}