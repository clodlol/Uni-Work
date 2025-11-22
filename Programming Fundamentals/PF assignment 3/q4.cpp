#include <iostream>
#include <limits>
using namespace std;

const int MAX_INPUT_SIZE = 100;
const int n = 10;

int main()
{
    char input[MAX_INPUT_SIZE] = {' '};

    while (true)
    {
        cout << "Enter ID: ";
        cin.getline(input, MAX_INPUT_SIZE);

        int count = 0;
        while (input[count] != '\0')
        {
            count++;
        }

        if (count != n)
        {
            cout << "Invalid ID length, enter again." << endl;
            continue;
        }
        else
        {
            bool valid = true;
            for (int i = 0; i < n; i++)
            {
                if (i < 3 && !(input[i] >= 'A' && input[i] <= 'Z'))
                {
                    cout << "The first 3 characters must be capital letters. Enter the ID again." << endl;
                    valid = false;
                    break;
                }
                else if ((i == 3 || i == 8) && input[i] != '-')
                {
                    cout << "The 4th and 9th characters must be hyphens. Enter again." << endl;
                    valid = false;
                    break;
                }
                else if ((i > 3 && i < 8) && !(input[i] >= '0' && input[i] <= '9'))
                {
                    cout << "The part between hyphens must be all digits. Enter again." << endl;
                    valid = false;
                    break;
                }
                else if (i > 8 && !(input[i] >= 'A' && input[i] <= 'Z'))
                {
                    cout << "The last character must be a capital letter. Enter the ID again." << endl;
                    valid = false;
                    break;
                }
            }

            if(valid)
                break;
        }
    }

    cout << "ID accepted!" << endl;
    system("pause");
    return 0;
}