#include <iostream>
using namespace std;

int main() {
    char choice;
    int itemsEaten = 0;
    do {
        cout << "Tom eats food from the fridge. Input whether the food is good (G) or spoiled (S): ";
        cin >> choice;
        if (choice == 'G' || choice == 'g') {
            itemsEaten++;
            cout << "Tom eats food joyfully." << endl;
            if(itemsEaten > 5) {
                cout << "Tom is feeling very full..." << endl;
            }
        } else if (choice == 'S' || choice == 's') {
            cout << "Tom has eaten spoiled food and feels sick now..." << endl;
            break;
        } else {
            cout << "Invalid input! Try again." << endl;
            continue;
        }
    } while (true);
    return 0;
}