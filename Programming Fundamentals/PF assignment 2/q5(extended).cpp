#include <iostream>
#include <iomanip>

using namespace std;

void counterClockwiseSpiral(int n);
void clockwiseSpiral(int n);

int main() {
    int n;
    cout << "Enter the width and height of spiral: ";
    cin >> n;
    
    counterClockwiseSpiral(n);
    
    return 0;
}

void counterClockwiseSpiral(int n) {
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
}

void clockwiseSpiral(int n) {
    int spiral[n][n];
    int counter = n*n;
    int left = 0;
    int right = n-1;
    int top = 0;
    int bottom = n-1;
    
    while(right >= left && bottom >= top) {
        for(int j = right; j >= left; j--) {
            spiral[top][j] = counter--;
        }
        top++;
        for(int i = top; i <= bottom; i++) {
            spiral[i][left] = counter--;
        }
        left++;
        for(int j = left; j <= right; j++) {
            spiral[bottom][j] = counter--;
        }
        bottom--;
        for(int i = bottom; i >= top; i--) {
            spiral[i][right] = counter--;
        }
        right--;
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << setw(4) << spiral[i][j];
        }
        cout << endl;
    }
}