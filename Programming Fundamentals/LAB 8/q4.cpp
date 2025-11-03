#include <iostream>

using namespace std;

int main() {
    const int arrLen = 10;
    int arr[arrLen] = {10, 8, 6, 4, 2, 0, -2, -4, -6, -8};
    for(int i = 0; i < arrLen/2; i++) {
        int temp = arr[i];
        arr[i] = arr[arrLen-1-i];
        arr[arrLen-1-i] = temp;
    }
    for(int i = 0; i < arrLen; i++) {
        cout << arr[i] << " ";
    }
}