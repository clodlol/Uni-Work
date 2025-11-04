#include <iostream>
#include <math.h>
using namespace std;

void merge(int left[], int right[], int size, int merged[]) {
    int leftCounter = 0;
    int rightCounter = 0;
    int counter = 0;
    while(leftCounter < size && rightCounter < size) {
        if(left[leftCounter] < right[rightCounter]) {
            merged[counter++] = left[leftCounter++];
        } else if(left[leftCounter] > right[rightCounter]) {
            merged[counter++] = right[rightCounter++];
        } else {
            merged[counter++] = left[leftCounter++];
            merged[counter++] = right[rightCounter++];
        }
    }

    while (leftCounter < size)
        merged[counter++] = left[leftCounter++];

    while (rightCounter < size)
        merged[counter++] = right[rightCounter++];
}

int main()
{
    int arr[] = {0, 4, 5, 3, -1, -11, 0, 80};
    int n = sizeof(arr)/sizeof(int);
    int sorted[n];

    for(int subArrSize = 1; subArrSize < n; subArrSize*=2) {
        for(int i = 0; i < subArrSize; i++) {
            
        }
    }
}