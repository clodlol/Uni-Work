#include <iostream>
using namespace std;

int main()
{
    int arr[] = {1, 2, 3, 99, 388, -1, -111};
    int n = sizeof(arr)/sizeof(int);

    int index = 0;
    int a = -1;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == a)
        {
            index = i;
            break;
        }
    }

    cout << "The index of required element is: " << index << endl;
}