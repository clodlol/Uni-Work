#include <iostream>
using namespace std;

int main() {
    for(int i = 1, flag = false; i <= 10 && !flag; i++) {
        if(i == 7) {
            cout << "Tom returns..." << endl;
            flag = true;
            continue;
        }
        
        cout << "Room " << i << ": " << "Tom walks through this room. Press Enter to continue...";
        cin.get();
    }
    return 0;
}