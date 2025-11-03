#include <iostream>
using namespace std;

int main() {
    for(int i = 1; i <= 10; i++) {
        int code = (i * i) + (5 * i) - 7;
        if ((code % 3 == 0) && (code % 4 == 0)) {
            cout << "Trap triggered in room " << i << " at code " << code << "!" << endl;
            exit(0);
        }
    }
    cout << "Tom passes through all of the rooms safely!" << endl;
    return 0;
}