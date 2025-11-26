#include <iostream>
#include <fstream>
using namespace std;

string numbersPath = "Numbers.txt";
string oddPath = "Odd.txt";
string evenPath = "Even.txt";

const int MAX_ARR_SIZE = 100;

int main()
{
    int evens[MAX_ARR_SIZE] = {0};
    int odds[MAX_ARR_SIZE] = {0};

    ifstream numbersFile(numbersPath, ios::in);
    if (!numbersFile.is_open())
    {
        cout << "An error occured while opening the number file." << endl;
        system("pause");
        return -1;
    }

    int totalEvens = 0, totalOdds = 0;
    string numbersLine;
    while (getline(numbersFile, numbersLine))
    {
        int currentInt = stoi(numbersLine);
        if (currentInt % 2 == 0)
        {
            evens[totalEvens] = currentInt;
            totalEvens++;
        }
        else
        {
            odds[totalOdds] = currentInt;
            totalOdds++;
        }
    }

    numbersFile.close();
    cout << "Succesfully read data from numbers file!" << endl;

    ofstream oddFile(oddPath, ios::out);
    if(!oddFile.is_open())
    {
        cout << "Error occured while opening odd file!" << endl;
        system("pause");
        return -1;
    }

    for(int i = 0; i < totalOdds; i++)
    {
        oddFile << odds[i] << endl;
    }

    oddFile.close();

    ofstream evenFile(evenPath, ios::out);
    if(!evenFile.is_open())
    {
        cout << "Error occured while opening odd file!" << endl;
        system("pause");
        return -1;
    }

    for(int i = 0; i < totalEvens; i++)
    {
        evenFile << evens[i] << endl;
    }

    evenFile.close();

    cout << "Total even numbers written: " << totalEvens << endl;
    cout << "Total odd numbers written: " << totalOdds << endl; 

    cout << endl;
    system("pause");
    return 0;
}