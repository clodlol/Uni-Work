#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

void printArr(const int *const ptr, const int &size)
{
    for (int i = 0; i < size; i++)
        cout << ptr[i] << " ";
    cout << endl;
}

int countIntegersInFile(string filename)
{
    int count = 0;
    ifstream file(filename, ios::in);
    string s;
    while (getline(file, s))
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (isspace(s[i]))
                count++;
        }
    }

    return (count + 1);
}

void readIntegersFromFile(string filename, int *const arr)
{
    ifstream file(filename, ios::in);
    string s;
    int c = 0;
    while (getline(file, s))
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ' || i == 0)
            {
                string currentIntStr;
                for (int j = (i == 0) ? i : (i + 1); (s[j] != ' ' && s[j] != '\0'); j++)
                {
                    currentIntStr += s[j];
                }

                arr[c++] = stoi(currentIntStr);
            }
        }
    }
}

int main()
{
    string filename = "a.txt";
    int size = countIntegersInFile(filename); // The file must have integers seperated with only 1 space
    int *arr = new int[size];
    readIntegersFromFile(filename, arr);
    printArr(arr, size);
    return 0;
}