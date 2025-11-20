#include <iostream>
#include <limits>
using namespace std;

int main()
{
    int n;
    cout << "Enter the length of intercepted message: ";
    cin >> n;

    char intMsg[n];
    cout << "Enter the intercepted message: ";
    cin.ignore();
    cin.getline(intMsg, n + 1);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int intMsgCounter = 0;
    for (int i = 0; i < n; i++)
        intMsgCounter++;
    cout << "Intercepted message length: " << intMsgCounter << endl;

    int substrLen;
    cout << "Enter the word to remove length: ";
    cin >> substrLen;
    if(substrLen > n)
    {
        cout << "Substring cannot be longer than main string!" << endl;
        system("pause");
        return -1;
    }

    char substr[substrLen];
    cout << "Enter the substring: ";
    cin.ignore();
    cin.getline(substr, substrLen + 1);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    char cleanMsg[n - substrLen];

    bool cleaned = false;
    for (int i = 0; i < n - substrLen; i++)
    {
        char temp[substrLen];
        int start = i, end = i + substrLen;
        for (int j = i; j < i + substrLen; j++)
        {
            temp[j - i] = intMsg[j];
        }

        bool found = true;
        for (int j = 0; j < substrLen; j++)
        {
            if (temp[j] != substr[j])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            for(int j = 0; j < start; j++)
            {
                cleanMsg[j] = intMsg[j];
            }

            for(int j = end; j < n; j++)
            {
                cleanMsg[j-substrLen] = intMsg[j];
            }

            cleaned = true;
        }
    }

    if(!cleaned)
    {
        cout << "After removing word: (could not find substring in intercepted message)" << endl;
        cout << "After case conversion: ";
        for(int i = 0; i < n; i++)
        {
            if(intMsg[i] >= 65 && intMsg[i] <= 90)
            {
                cout << char(intMsg[i] + 32);
            } else if(intMsg[i] >= 97 && intMsg[i] <= 122)
            {
                cout << char(intMsg[i] - 32);
            } else {
                cout << intMsg[i];
            }
        }

        cout << endl;
    } else
    {
        cout << "After removing word: ";
        for(int i = 0; i < n-substrLen; i++)
        {
            cout << cleanMsg[i];
        }
        cout << endl;

        cout << "After case conversion: ";
        for(int i = 0; i < n-substrLen; i++)
        {
            if(cleanMsg[i] >= 65 && cleanMsg[i] <= 90)
            {
                cout << char(cleanMsg[i] + 32);
            } else if(cleanMsg[i] >= 97 && cleanMsg[i] <= 122)
            {
                cout << char(cleanMsg[i] - 32);
            } else {
                cout << cleanMsg[i];
            }
        }

        cout << endl;
    }

    cout << "Townsville intelligence report generated." << endl;

    system("pause");
    return 0;
}