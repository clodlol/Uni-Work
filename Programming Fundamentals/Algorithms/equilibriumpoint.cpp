#include <iostream>
using namespace std;

int main()
{
    int arr[] = {1, 2, 3, -1, 5, 1};
    int n = sizeof(arr)/sizeof(int);

    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += arr[i];
    
    int eqIndex = -1, rightSum = 0;
    for(int i = n-1; i >= 0; i--)
    {
        rightSum += arr[i];
        sum -= arr[i];
        if(sum == rightSum)
        {
            eqIndex = i;
            break;
        }
    }
    if(eqIndex == -1)
        cout << "No equilibrium point found!" << endl;
    else
        cout << "Equilibrium point at index " << eqIndex << endl;
}