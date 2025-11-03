// Name: Abdul Rehman
// Roll No: L25-0856
// Question 5: Increment/decrement challenge
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
    int adjustedPoints = loyaltyPoints;
    
    if(sandwiches > 5)
        adjustedPoints += 2;
    
    if(bill == 1000)
        adjustedPoints--;
        
    cout << "Total bill: Rs. " << bill << endl;
    cout << "Loyalty Points = " << loyaltyPoints << endl;
    cout << "After adjustment = " << adjustedPoints << endl;

    return 0;
}