#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int height, width;
    char symbol;
    cout << "Enter height of pyramid: ";
    cin >> height;
    cout << "Enter symbol to use: ";
    cin >> symbol;
    width = (3*height)-1;
    int pyramidAxis = width/2;
    for(int i = 1; i <= height; i++) {
        for(int j = 1; j <= width; j++) {
            if(abs(j - pyramidAxis) <= (i-1)) {
                cout << symbol;
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}