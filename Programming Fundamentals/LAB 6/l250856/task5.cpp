#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int r;
    cout << "Enter dome radius ";
    cin >> r;
    for(int i = r; i >= 1; i--) {
        for(int j = 1; j <= r; j++) {
            if(j == i) {
                cout << "*";
            } else if(j > i) {
                cout << (j - i);
            } else {
                cout << "-";
            }
        }
        for(int j = (r-1); j > 0; j--) {
            if(j == i) {
                cout << "*";
            } else if(j > i) {
                cout << (j - i);
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
    for(int i = 2; i <= r; i++) { //why did this work for 2 and not 1?????
        for(int j = 1; j <= r; j++) {
            if(j == i) {
                cout << "*";
            } else if(j > i) {
                cout << (j - i);
            } else {
                cout << "-";
            }
        }
        for(int j = (r-1); j > 0; j--) {
            if(j == i) {
                cout << "*";
            } else if(j > i) {
                cout << (j - i);
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
}