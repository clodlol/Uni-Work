#include <iostream>
using namespace std;

int main() {
    int students, burgers = 0, sandwiches = 0, drinks = 0;
    
    do {
        cout << "Enter number of students: ";
        cin >> students;
    } while(students < 1);
    
    cout << "------------------------------" << endl;
    for(int i = 1; i <= students; i++) {
        cout << "Student " << i << ":\nBurgers: ";
        for(int currentBurgers = 0; true; ) {
            cin >> currentBurgers;
            if(currentBurgers < 0) {
                continue;
            } else {
                burgers += currentBurgers;
                break;
            }
        }
        
        cout << "Sandwiches: ";
        for(int currentSandwiches = 0; true; ) {
            cin >> currentSandwiches;
            if(currentSandwiches < 0) {
                continue;
            } else {
                sandwiches += currentSandwiches;
                break;
            }
        }
        
        cout << "Drinks: ";
        for(int currentDrinks = 0; true; ) {
            cin >> currentDrinks;
            if(currentDrinks < 0) {
                continue;
            } else {
                drinks += currentDrinks;
                cout << "------------------------------" << endl;
                break;
            }
        }
    }
    
    cout << "Total burgers sold: " << burgers << endl;
    cout << "Total sandwiches sold: " << sandwiches << endl;
    cout << "Total drinks sold: " << drinks << endl;
    
    cout << "------------------------------" << endl;
    
    if(burgers == sandwiches && burgers == drinks) {
        cout << "All items are sold equally." << endl;
    } else if(burgers == sandwiches && burgers > drinks) {
        cout << "Most sold item: Burgers tied with Sandwiches" << endl;
    } else if(burgers == drinks && burgers > sandwiches) {
        cout << "Most sold item: Burgers tied with Drinks" << endl;
    } else if(sandwiches == drinks && sandwiches > burgers) {
        cout << "Most sold item: Sandwiches tied with Drinks" << endl;
    } else if(burgers > sandwiches && burgers > drinks) {
        cout << "Most sold item: Burgers" << endl;
    } else if(sandwiches > drinks && sandwiches > burgers) {
        cout << "Most sold item: Sandwiches" << endl;
    } else {
        cout << "Most sold item: Drinks" << endl;
    }
}