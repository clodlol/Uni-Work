#include <iostream>
using namespace std;

int main() {
    int secretNumber = 123;
    int attempts = 0;
    while(true) {
        int guess = 0;
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;
        if(attempts == 5) {
            cout << "You lose! The number is: " << secretNumber << endl;
            break;
        } else if(guess == secretNumber) {
            cout << "You win! The number is: " << secretNumber << endl;
            break;
        } else {
            cout << "Wrong guess, try again." << endl;
        }
    }
}