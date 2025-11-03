// Name: Abdul Rehman
// Roll No: L25-0856
// Question 3: Loyalty Points
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
    int loyaltyPoints = bill / 100;
    
    
    cout << "Final bill: Rs. " << bill << endl;
    cout << "Loyalty points earned: " << loyaltyPoints << endl;

    return 0;
}