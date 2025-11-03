#include <iostream>
using namespace std;

void swap(int& a, int& b) {
    a = a + b;
    b = a - b;
    a = a - b;
}

int main() {
    int arr[] = {-1, 0, 99, 100, -123, 1200};
    int n = sizeof(arr)/sizeof(int);

    int left = 0;
    int right = n-1;
    while(left <= right) {
        for(int i = left; i < right; i++) {
            if(arr[i+1] < arr[i])
                swap(arr[i+1], arr[i]);
        }
        right--;
    }

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}