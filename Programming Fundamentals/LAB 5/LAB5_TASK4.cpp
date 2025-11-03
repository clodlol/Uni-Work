#include <iostream>
using namespace std;

int main() {
    int roomsVisited = 0;
    for(int i = 1; i <= 10; i++) {
        if(roomsVisited >= 6) {
            cout << "Tom gets tired and quits...";
            break;
        }
        if (i % 3 == 0) {
            cout << "Room " << i << ": " << "Tom skips this room because it has a trap. Press Enter to continue... ";
            cin.get();
            continue;
        }
        cout << "Room " << i << ": " << "Tom walks through this room. Press Enter to continue...";
        cin.get();
        roomsVisited++;
    }
    return 0;
}