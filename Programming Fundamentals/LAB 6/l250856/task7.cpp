#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    char symbol = '*';
    int borderWidth = 35;
    int item1Quantity, item2Quantity, item3Quantity;
    string item1Name, item2Name, item3Name;
    float item1Price, item2Price, item3Price;

    cout << "Enter the border symbol: ";
    cin >> symbol;

    cout << "Enter border width: ";
    cin >> borderWidth;
    cin.ignore(); // clear leftover newline before getline

    cout << "Enter item 1 name: ";
    getline(cin, item1Name);
    cout << "Enter item 1 quantity: ";
    cin >> item1Quantity;
    cout << "Enter item 1 price: ";
    cin >> item1Price;
    cin.ignore();

    cout << "Enter item 2 name: ";
    getline(cin, item2Name);
    cout << "Enter item 2 quantity: ";
    cin >> item2Quantity;
    cout << "Enter item 2 price: ";
    cin >> item2Price;
    cin.ignore();

    cout << "Enter item 3 name: ";
    getline(cin, item3Name);
    cout << "Enter item 3 quantity: ";
    cin >> item3Quantity;
    cout << "Enter item 3 price: ";
    cin >> item3Price;

    cout << fixed;
    cout << endl;
    cout << setw(borderWidth) << setfill(symbol) << "" << endl;
    
    cout << setw(borderWidth/4) << setfill(' ') << left << symbol;
    cout << setw(borderWidth/2) << setfill(' ') << left <<  "KRUSTY KRAB RECEIPT";
    cout << setw(borderWidth/4) << setfill(' ') << right << symbol << endl;
    cout << setw(borderWidth) << setfill(symbol) << "" << endl << endl;
    
    cout << left << setw(borderWidth/2) << setfill(' ') << "Item";
    cout << left << setw(borderWidth/6) << setfill(' ') << "Qty";
    cout << left << setw(borderWidth/4) << setfill(' ') << "Price";
    cout << left << setw(borderWidth/4) << setfill(' ') << "Total";
    
    cout << endl;
    cout << setw(borderWidth) << setfill('-') << "" << endl << endl;
    
    float item1Total = item1Quantity * item1Price;
    cout << left << setw(borderWidth/2) << setfill(' ') << item1Name;
    cout << left << setw(borderWidth/6) << setfill(' ') << item1Quantity;
    cout << left << setw(borderWidth/4) << setprecision(2) << setfill(' ') << item1Price;
    cout << left << setw(borderWidth/4) << setprecision(2) << setfill(' ') << item1Total;
    cout << endl;
    
    float item2Total = item2Quantity * item2Price;
    cout << left << setw(borderWidth/2) << setfill(' ') << item2Name;
    cout << left << setw(borderWidth/6) << setfill(' ') << item2Quantity;
    cout << left << setw(borderWidth/4) << setprecision(2) << setfill(' ') << item2Price;
    cout << left << setw(borderWidth/4) << setprecision(2) << setfill(' ') << item2Total;
    cout << endl;
    
    float item3Total = item3Quantity * item3Price;
    cout << left << setw(borderWidth/2) << setfill(' ') << item3Name;
    cout << left << setw(borderWidth/6) << setfill(' ') << item3Quantity;
    cout << left << setw(borderWidth/4) << setprecision(2) << setfill(' ') << item3Price;
    cout << left << setw(borderWidth/4) << setprecision(2) << setfill(' ') << item3Total;
    cout << endl;
    
    cout << setw(borderWidth) << setfill('-') << "" << endl << endl;
    
    cout << left << setw(borderWidth/2) << setfill(' ') << "Total Bill: ";
    cout << right << setw(borderWidth/2) << setprecision(2) << setfill(' ') << (item1Total + item2Total + item3Total) << endl;
    cout << "Thank you, see you next time!" << endl << endl;
    
    cout << setw(borderWidth) << setfill(symbol) << "" << endl << endl;

    return 0;
}