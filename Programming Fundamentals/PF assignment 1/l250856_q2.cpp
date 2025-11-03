// Name: Abdul Rehman
// Roll No: L25-0856
// Question 2: Apply discounts
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
    float discountedPrice = bill;
    float discount = 0;
    if(bill > 500 && bill <= 1000)
        discount = 0.1;
    else if(bill > 1000)
        discount = 0.2;
        
    discountedPrice = bill * (1-discount);
    
    
    cout << "Total before discount: Rs. " << bill << endl;
    cout << "Discount: Rs. " << bill*discount << endl;
    cout << "Final bill: Rs. " << (int)discountedPrice << endl;

    return 0;
}