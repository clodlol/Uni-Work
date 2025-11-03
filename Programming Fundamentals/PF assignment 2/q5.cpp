#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cout << "Enter the width and height of spiral: ";
    cin >> n;
    int spiral[n][n];
    int counter = n*n;
    int left = 0;
    int right = n-1;
    int top = 0;
    int bottom = n-1;
    
    //populate matrix
    while(bottom >= top && right >= left) {
        for(int j = left; j <= right; j++) {
            spiral[top][j] = counter--;
        }
        top++;
        for(int i = top; i <= bottom; i++) {
            spiral[i][right] = counter--;
        }
        right--;
        for(int j = right; j >= left; j--) {
            spiral[bottom][j] = counter--;
        }
        bottom--;
        for(int i = bottom; i >= top; i--) {
            spiral[i][left] = counter--;
        }
        left++;
    }
    
    //print matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << setw(4) << spiral[i][j];
        }
        cout << endl;
    }
    
    return 0;
}