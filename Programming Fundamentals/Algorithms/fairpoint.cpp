#include <iostream>
using namespace std;

int main()
{
    int arr[] = {1, 2, 3, -1, 5, 1};
    int n = sizeof(arr)/sizeof(int);

    int index = -1;
    int cursor = 1;
    while(cursor <= n-2)
    {
        float leftAvg = 0, rightAvg = 0;
        for(int i = 0; i < cursor; i++)
        {
            leftAvg += arr[i];
        }
        leftAvg /= (cursor);
        for(int i = cursor+1; i <= n-1; i++)
        {
            rightAvg += arr[i];
        }
        rightAvg /= (n-1-cursor);
        if(leftAvg == rightAvg)
        {
            index = cursor;
            break;
        }
        cursor++;
    }

    if(index == -1)
    {
        cout << "No fair point found!" << endl;
    } else
    {
        cout << "Fair point found at index " << index << endl;
    }
}