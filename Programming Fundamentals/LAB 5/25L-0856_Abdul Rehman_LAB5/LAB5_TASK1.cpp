#include <iostream>
using namespace std;

int main() {
    int choice, eatenCount = 0;
    bool sniffed = false;
    do {
        cout << "1. Sniff the cheese\n2. Eat the cheese\n3. Check energy\n4. Exit Vault\nChoose an option: ";
        cin >> choice;
        if(choice == 1) {
            sniffed = true;
            cout << "Tom sniffed the cheese. It smells delicious..." << endl;
            continue;
        } else if (choice == 2) {
            if(!sniffed) {
                cout << "Alarm triggered! Tom ate the cheese without sniffing it..." << endl;
                exit(0);
            }
            if(eatenCount > 3) {
                cout << "Tom is full! He decides to escape before Jerry arrives..." << endl;
                break;
            }
            eatenCount++;
            cout << "Tom eats the cheese. Yummy..." << endl;
            continue;
        } else if (choice == 3) {
            cout << "Tom's current energy is: " << eatenCount << endl;
            continue;
        } else if (choice == 4) {
            cout << "Tom sneaks out of the vault quietly...";
            break;
        } else {
            cout << "Invalid input! Try again..." << endl;
        }
    } while (true);
    return 0;
}