// Name: Abdul Rehman
// Roll No: L25-0856
// Question 8: Combo offer checker
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
    
    bool comboApplied = false;
    
    if(burgers == 1 && pizzas == 1 && sandwiches ==1)
        comboApplied = true;
    
    int bill = 0;
    
    cout << "Burgers = " << burgers << ", Pizza slices = " << pizzas << ", Sandwiches = " << sandwiches << endl;
    
    if(comboApplied) {
        bill = 400;
        cout << "Combo applied!" << endl;
    }
    else
        bill = (burgerPrice * burgers) + (pizzaPrice * pizzas) + (sandwichPrice * sandwiches);
        
    cout << "Final bill = " << bill << " PKR" << endl;
    
    return 0;
}