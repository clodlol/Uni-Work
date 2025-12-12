#include <iostream>
using namespace std;

int freq(int a, int arr[], int n)
{
    int freq = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == a)
            freq++;
    }
    return freq;
}

int main()
{
    const int n = 8;
    int arr[n] = {1, 2, 3, 3, 4, 1, 5, 6};
    int freq[n] = {0};
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        int appearedIndex = -1;
        for (int j = 0; j < n; j++)
        {
            if (arr[j] == arr[i])
            {
                count++;
            }

            for (int k = j; k < n; k++)
            {
                if (arr[k] == arr[j])
                {
                    appearedIndex = k;
                    break;
                }
            }

            if (i != appearedIndex)
            {
                cout << "Element " << arr[i] << " appears " << count << " times" << endl;
            }
        }

        freq[i] = count;
    }

    system("pause");
    return 0;
}