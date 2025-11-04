#include <iostream>
using namespace std;

int main()
{
    int arr[] = {-10, -10, 0, 1, 70, 90};
    int n = sizeof(arr)/sizeof(int);

    int index = 0;
    int a = -10;
    
    
    int left = 0;
    int right = n-1;
    while(left <= right)
    {
        int mid = left + (right-left)/2;
        if(arr[mid] > a)
        {
            right = mid-1;
        } else if(arr[mid] < a)
        {
            left = mid+1;
        } else {
            index = mid;
            cout << "Found " << a << " at index " << index << endl;
            break;
        }
    }
}