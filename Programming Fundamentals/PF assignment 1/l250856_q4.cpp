// Name: Abdul Rehman
// Roll No: L25-0856
// Question 4: Student eigibility for meal deal
#include <iostream>
using namespace std;

int main() {
    int burgers, pizzas, sandwiches;
    cout << "Enter Burgers: ";
    cin >> burgers;
    cout << "Enter Pizza slices: ";
    cin >> pizzas;
    cout << "Enter Sandwiches: ";
    cin >> sandwiches;
    
    const int burgerPrice = 200;
    const int pizzaPrice = 150;
    const int sandwichPrice = 100;
    
    int bill = (burgers * burgerPrice) + (pizzas * pizzaPrice) + (sandwichPrice * sandwiches);
    bool freeDrink = false;
    if((burgers >= 2 && pizzas >= 1) || bill > 700)
        freeDrink = true;
    
    cout << "Burgers = " << burgers << ", Pizza slices = " << pizzas << ", Sandwiches = " << sandwiches << endl;
    cout << "Final bill: Rs. " << bill << endl;
    if(freeDrink)
        cout << "Eligible for free drink" << endl;
    else {
        cout << "Not eligible for free drink" << endl;
    }

    return 0;
}