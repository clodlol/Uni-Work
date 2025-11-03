// Name: Abdul Rehman
// Roll No: L25-0856
// Question 7: Daily sales target
#include <iostream>
using namespace std;

int main() {
    int sales;
    cout << "Enter today's sales: ";
    cin >> sales;
    
    const int target = 5000;
    if(sales >= target) {
        cout << "Target achieved." << endl;
    } else {
        cout << "Target not achieved. Short by " << target-sales << " PKR" << endl;
    }
    
    return 0;
}