#include <iostream>
#include <cmath>
using namespace std;

int main() {
    char choice, symbol;
    int width, height;
    cout << "Enter s for square or r for rectangle: ";
    cin >> choice;
    cout << "Enter which symbol you want to print: ";
    cin >> symbol;
    if(choice == 's' || choice == 'S') {
        cout << "Enter square side: ";
        cin >> width;
        height = width;
    } else if(choice == 'r' || choice == 'R') {
        cout << "Enter rectangle width: ";
        cin >> width;
        cout << "Enter rectangle height: ";
        cin >> height;
    } else {
        cout << "Invalid choice" << endl;
        return 0;
    }
    
    for(int i = 1; i <= height; i++) {
        for(int j = 1; j <= width; j++) {
            if(i == 1 || i == height) {
                cout << symbol;
            } else if(j == 1 || j == width) {
                cout << symbol;
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}