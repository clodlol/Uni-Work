#include <iostream>
#include <limits>
using namespace std;

bool getInt(int &input, int rangeStart, int rangeEnd);

int calculateUnion(int setA[], int sizeA, int setB[], int sizeB, int out[])
{
    // size of out in input must be sizeA+sizeB(maximum possible size for union set)
    // the function returns the size of out[] array so it can be traversed easily
    for(int i = 0; i < sizeA-1; i++)
    {
        bool found = false;
        for(int j = 0; j < i; j++)
        {
            if(out[j] == setA[i])
                found = true;
                break;
        }

        if(found)
            out[i] = setA[i+1];
    }
}

int main()
{
    int first[100] = {0}, second[100] = {0}, m = 0, n = 0;
    while (true)
    {
        cout << "Enter the size of first set: ";
        if (!getInt(m, 1, INT_MAX))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the size of second set: ";
        if (!getInt(n, 1, INT_MAX))
            continue;
        else
            break;
    }

    cout << "First set: " << endl;
    for (int i = 0; i < m;)
    {
        cout << "[" << i << "]: ";
        if (!getInt(first[i], INT_MIN, INT_MAX))
            continue;
        else
            i++;
    }

    cout << "Second set: " << endl;
    for (int i = 0; i < n;)
    {
        cout << "[" << i << "]: ";
        if (!getInt(second[i], INT_MIN, INT_MAX))
            continue;
        else
            i++;
    }

    system("pause");
    return 0;
}

bool getInt(int &input, int rangeStart, int rangeEnd)
{
    if (cin >> input)
    {
        return (input >= rangeStart && input <= rangeEnd);
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}