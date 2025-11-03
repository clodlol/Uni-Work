#include <iostream>
using namespace std;

int main() {
    int rows = 0, columns = 0;
    
    do {
        cout << "Enter total rows: ";
        cin >> rows;
    } while (rows <= 1);
    
    do {
        cout << "Enter total columns: ";
        cin >> columns;
    } while (columns <= 1);
    
    int res1row = 0;
    int res1col = 0;
    
    do {
        cout << "Enter first reserved seat row: ";
        cin >> res1row;
    } while (res1row < 1 || res1row > rows);
    do {
        cout << "Enter first reserved seat column: ";
        cin >> res1col;
    } while (res1col < 1 || res1col > columns);
    
    int res2row = 0;
    int res2col = 0;
    
    do {
        cout << "Enter second reserved seat row: ";
        cin >> res2row;
    } while (res2row < 1 || res2row > rows);
    do {
        cout << "Enter first reserved seat column: ";
        cin >> res2col;
    } while (res2col < 1 || res2col > columns || (res2row == res1row && res2col == res1col));
    
    for(int i = 1; i <= rows; i++) {
        for(int j = 1; j <= columns; j++) {
            if((res1col == j && res1row == i) || (res2col == j && res2row == i)) {
                cout << "[X, X] ";
            } else {
                cout << "[" << i << ", " << j << "] ";
            }
        }
        cout << endl;
    }
}