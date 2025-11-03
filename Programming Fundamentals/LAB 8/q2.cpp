//This algorithm works for unsorted inputs as well, since the overall approach to the problem is same
#include <iostream>

using namespace std;

void swap(int &a, int &b) {
    a = a+b;
    b = a-b;
    a = a-b;
}

void mergeSortedArrays(int a[], int b[], int merged[], int lenA, int lenB) {
    int mergedLen = lenA + lenB;
    for(int i = 0; i < lenA; i++)
        merged[i] = a[i];
    for(int j = lenA; j < mergedLen; j++)
        merged[j] = b[j - lenA];
    
    //We use bubble sort for sorting
    int left = 0;
    int right = mergedLen-1;
    while(right > left) {
        for(int i = 0; i < mergedLen - 1; i++) {
            if(merged[i] > merged[i+1]) {
                swap(merged[i], merged[i+1]);
            }
        }
        right--;
    }
    
}

int main() {
    const int arrLen = 5;
    int first[arrLen];
    int second[arrLen];
    
    cout << "Enter first array elements: ";
    for(int i = 0; i < arrLen; i++)
        cin >> first[i];
        
    cout << "Enter second array elements: ";
    for(int i = 0; i < arrLen; i++)
        cin >> second[i];
    
    const int mergedLen = arrLen + arrLen;
    int merged[mergedLen];
    mergeSortedArrays(first, second, merged, arrLen, arrLen);
    for(int i = 0; i < mergedLen; i++)
        cout << merged[i] << " ";
}