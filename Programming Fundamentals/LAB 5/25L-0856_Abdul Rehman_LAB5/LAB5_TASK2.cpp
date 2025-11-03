#include <iostream>
using namespace std;

int main() {
    int counter = 0, totalCheese = 0;
    bool slipped = false;
    while (counter < 20) {
        int cheeseAmount;
        cout << "Enter the amount of cheese Tom collects from this tile: ";
        cin >> cheeseAmount;
        if(cheeseAmount <= 0) {
            cout << "Tom refuses to collect this amount of cheese!" << endl;
            continue;
        }
        totalCheese += cheeseAmount;
        if(totalCheese % 7 == 0) {
            cout << "Tom falls into Jerry's trap and slips..." << endl;
            slipped = true;
            break;
        }
        counter++;
    }
    if (!slipped)
        cout << "Tom collected " << totalCheese << " number of cheese..." << endl;
    return 0;
}