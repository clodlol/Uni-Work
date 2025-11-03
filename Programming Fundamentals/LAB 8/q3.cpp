#include <iostream>

using namespace std;

int findSecondLargest(int arr[], int size) {
    int largest = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] > largest) {
            largest = arr[i];
        }
    }
        
    for(int i = 0; i < size; i++) {
        if(arr[i] == largest)
            arr[i] = 0;
    }
    
    largest = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] > largest) {
            largest = arr[i];
        }
    }
    
    return largest;
}

int main() {
    const int size = 10;
    int arr[size];
    
    cout << "Enter the array elements: ";
    for(int i = 0; i < size; i++)
        cin >> arr[i];
        
    bool allDuplicates = true;
    for(int i = 0; i < size - 1; i++) 
        if(arr[i] != arr[i + 1]) allDuplicates = false;
        
    if(allDuplicates) {
        cout << "No second largest found!" << endl;
    } else {
        cout << "The second largest element is: " << findSecondLargest(arr, size) << endl;
    }
}