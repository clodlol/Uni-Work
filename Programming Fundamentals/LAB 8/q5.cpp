#include <iostream>

using namespace std;

void countFrequencies(int arr[], int size, int freq[], int& uniqueCount) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(arr[i] == arr[j] && i != j)
                freq[i]++;
        }
        freq[i]++;
    }
    
    for(int i = 0; i < size; i++)
        if(freq[i] == 1) uniqueCount++;
}

int main() {
    const int size = 5;
    int arr[size];
    
    cout << "Enter the array elements: ";
    for(int i = 0; i < size; i++)
        cin >> arr[i];
        
    int uniqueCount = 0;
    int freq[size];
    for(int i = 0; i < size; i++)
        freq[i] = 0;
    
    countFrequencies(arr, size, freq, uniqueCount);
    
    cout << endl << "The number of unique elements in the array is: " << uniqueCount << endl;
} 