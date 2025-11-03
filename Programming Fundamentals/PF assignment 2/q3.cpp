#include <iostream>
using namespace std;

int main() {
    int n;
    do {
        cout << "Enter a number: ";
        cin >> n;
    } while (n < 1);
    
    for(int i = 1; i <= n; i++) {
        cout << "-----------------------------------" << endl;
        cout << "Table of " << i << endl;
        for(int j = 1; j <= 10; j++) {
            if((i * j) % 2 == 0) {
                cout << i << " x " << j << " = " << (i*j) << endl;
            }
        }
    }
}