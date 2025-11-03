
#include <iostream>

using namespace std;

int main() {
    const int arrLen = 10;
    int arr[arrLen];
    cout << "Enter the array elements: ";
    for(int i = 0; i < arrLen; i++)
        cin >> arr[i];
    
    int uniqueArr[arrLen];
    
    for(int i = 0; i < arrLen; i++) {
        bool currentUnique = true;
        for(int j = i+1; j < arrLen; j++) {
            if(arr[j] == arr[i]) {
                currentUnique = false;
                break;
            }
        }
        
        if(currentUnique) {
            uniqueArr[i] = arr[i];
        } else {
            uniqueArr[i] = 0;
        }
    }
    
    for(int i = 0; i < arrLen; i++)
        cout << uniqueArr[i] << " ";
    cout << endl << "All the duplicate elements are removed and replaced by 0" << endl;
    
    return 0;
}