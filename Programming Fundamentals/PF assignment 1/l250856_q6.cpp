// Name: Abdul Rehman
// Roll No: L25-0856
// Question 6: Cheapest item finder
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
    
    int burgerCost = burgerPrice * burgers;
    int pizzaCost = pizzaPrice * pizzas;
    int sandwichCost = sandwichPrice * sandwiches;
    
    cout << "Burgers = " << burgers << ", Pizza slices = " << pizzas << ", Sandwiches = " << sandwiches << endl;
    cout << "Burger cost: Rs. " << burgerCost << endl << "Pizza cost: Rs. " << pizzaCost << endl << "Sandwich cost: Rs. " << sandwichCost << endl;

    if(burgerCost < pizzaCost) {
        if(burgerCost < sandwichCost)
            cout << "Cheapest item(s): Burgers" << endl;
        else
            cout << "Cheapest item(s): Sandwiches" << endl;
    } else if (pizzaCost < sandwichCost)
        cout << "Cheapest item(s): Pizzas" << endl;

    return 0;
}