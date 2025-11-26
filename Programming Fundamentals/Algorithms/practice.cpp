#include <iostream>
using namespace std;

int main()
{
    char dirty[2][9] = {{'b', '0', 'b', '-', ' ', 't', 'h', '3', '\0'}, {'b', 'u', 'i', 'l', 'd', 'e', 'r', '!', '\0'}};
    char clean[2][9] = {' '};

    for (int i = 0; i < 2; i++)
    {
        int counterDirty = 0, counterClean = 0;
        while(dirty[i][counterDirty] != '\0')
        {
            char currentChar = dirty[i][counterDirty];
            if(isalpha(currentChar))
            {
                if(islower(currentChar))
                {
                    clean[i][counterClean] = toupper(currentChar);
                    counterClean++;
                } else {
                    clean[i][counterClean] = currentChar;
                }
            }

            counterDirty++;
        }

        clean[i][counterClean + 1] = '\0';
    }

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cout << clean[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}