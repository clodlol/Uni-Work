#include <iostream>

using namespace std;

int countAboveAverage(float arr[], int size, float average) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] > average)
            count++;
    }
    return count;
}

int main() {
    const int size = 5;
    float arr[size];
    float average = 0;
    
    cout << "Enter " << size << " floating point numbers: ";
    for(int i = 0; i < size; i++) {
        cin >> arr[i];
        average += arr[i];
    }
    average /= size;
    
    cout << "Average: " << average << endl;
        
    cout << "There are " << countAboveAverage(arr, size, average) << " elements above average." << endl;
}