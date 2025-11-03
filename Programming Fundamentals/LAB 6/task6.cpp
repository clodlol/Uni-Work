#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int start, end, columns, elements, rows;
    do {
        cout << "Enter starting ASCII value (33-126): ";
        cin >> start;
    } while(start < 33 || start > 126);
    
    do {
        cout << "Enter ending ASCII value (33-126): ";
        cin >> end;
    } while((end < 33 || end > 126) || (end <= start));
    
    do {
        cout << "Enter number of columns: ";
        cin >> columns;
    } while(columns <= 0);
    elements = end - start + 1;
    rows = (elements / columns) + (rows % elements != 0);
    for(int i = 1; i <= rows; i++) {
        for(int j = 1; j <= columns; j++) {
            if(start <= end)
                cout << (char)start++ << "(" << (start - 1) << ")" << " ";
        }
        cout << endl;
    }
}