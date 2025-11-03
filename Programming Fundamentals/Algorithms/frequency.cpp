#include <iostream>
using namespace std;

int freq(int a, int arr[], int n) {
    int freq = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] == a)
            freq++;
    }
    return freq;
}

int main()
{
    int arr[] = {1, 2, 3, 3, 4, 1, 5, 6};
    int n = sizeof(arr)/sizeof(int);
    int freq_arr[n];

    for(int i = 0; i < n; i++) {
        freq_arr[i] = freq(arr[i], arr, n);
    }

    cout << "The corresponding frequencies are: ";
    for(int i = 0; i < n; i++)
        cout << freq_arr[i] << " ";
    cout << endl;
}