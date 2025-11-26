#include <iostream>
#include <limits>
#include <string>
using namespace std;

const int NAME_LIMIT = 100;

struct BabyToon
{
    char name[NAME_LIMIT];
    char favToy[NAME_LIMIT];
    int freakLevel;
};

int main()
{
    const int characterCount = 4;
    BabyToon charInfo[characterCount];

    int mostFreaky = INT_MIN;
    int leastFreaky = INT_MAX;
    for (int i = 0; i < characterCount; i++)
    {
        cout << "Enter name for character " << (i + 1) << ": ";
        cin.getline(charInfo[i].name, NAME_LIMIT);

        cout << "Enter name of favourite toy for character " << (i + 1) << ": ";
        cin.getline(charInfo[i].favToy, NAME_LIMIT);

        cout << "Enter mischief level for character" << (i + 1) << ": ";
        cin >> charInfo[i].freakLevel;

        cin.ignore(NAME_LIMIT, '\n');
        cin.clear();

        if (charInfo[i].freakLevel > mostFreaky)
        {
            mostFreaky = charInfo[i].freakLevel;
        }

        if (charInfo[i].freakLevel < leastFreaky)
        {
            leastFreaky = charInfo[i].freakLevel;
        }
    }

    cout << "------------------------ LOONEY TOONS PLAYROOM ------------------------" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << charInfo[i].name << " loves " << charInfo[i].favToy << " | Mischief level: " << charInfo[i].freakLevel << endl;
    }
    cout << endl;

    system("pause");
    return 0;
}