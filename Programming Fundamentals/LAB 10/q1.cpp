#include <iostream>
#include <limits>
using namespace std;

int main()
{
    int n;

    cout << "Enter code length: ";
    cin >> n;

    char charArr[n];
    int powLevel;

    cout << "Enter secret code as characters: ";
    cin.ignore();
    cin.getline(charArr, n + 1);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter power level: ";
    cin >> powLevel;

    string s = charArr;
    cout << "Converted to string: " << s << endl;

    for (int i = 0; i < n; i++)
        charArr[i] = s[i];
    cout << "Converted back to array: ";
    for (int i = 0; i < n; i++)
        cout << charArr[i];
    cout << endl;

    string powLevelStr = to_string(powLevel);
    cout << "Power level as string: " << powLevelStr << endl;

    char powerLvlChar[powLevelStr.size() + 1];
    for (int i = 0; i < powLevelStr.size(); i++)
        powerLvlChar[i] = powLevelStr[i];
    cout << "Power level as char array: ";
    for (int i = 0; i < powLevelStr.size(); i++)
        cout << powerLvlChar[i];
    cout << endl;

    char intCharArr[] = {'1', '2', '3', '\0'};
    int a = stoi(string(intCharArr));
    cout << "Code converted to int: " << a << endl;

    cout << "Final Message: " << endl
         << "Blossom, Bubbles and Buttercup's total power = " << a << endl
         << "Townsville is safe again!" << endl;
}