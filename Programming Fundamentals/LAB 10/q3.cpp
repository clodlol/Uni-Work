#include <iostream>
#include <limits>
#include <cstring>
using namespace std;

int min(int a, int b)
{
    return a <= b ? a : b;
}

int main()
{
    int firstLen;
    cout << "Enter the length of first name: ";
    cin >> firstLen;

    char firstArr[firstLen];

    cout << "Enter the first name: ";
    cin.ignore();
    cin.getline(firstArr, firstLen + 1);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int secondLen;
    cout << "Enter the length of the second name: ";
    cin >> secondLen;

    char secondArr[secondLen];

    cout << "Enter the second name: ";
    cin.ignore();
    cin.getline(secondArr, secondLen + 1);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool equal = true;
    for(int i = 0; i < min(firstLen, secondLen); i++)
    {
        if(tolower(firstArr[i]) != tolower(secondArr[i]))
        {
            equal = false;
            break;
        }
    }

    cout << "Are they equal? " << (equal ? "Yes" : "No") << endl;

    char teamNameArr[firstLen + secondLen];

    for(int i = 0; i < firstLen; i++)
        teamNameArr[i] = firstArr[i];

    for(int i = 0; i < secondLen; i++)
        teamNameArr[i+firstLen] = secondArr[i];

    cout << "Team name: ";
    for(int i = 0; i < firstLen + secondLen; i++)
        cout << teamNameArr[i];
    cout << endl;

    bool palindrome = true;
    for(int i = 0; i < (firstLen + secondLen)/2; i++)
    {
        if(teamNameArr[i] != teamNameArr[firstLen + secondLen - 1 - i])
        {
            palindrome = false;
            break;
        }
    }

    cout << "Palindrome check: " << (palindrome ? "Yes" : "No") << endl;
    cout << "Mission unlocked: Sugar spice & everything nice!" << endl;
}