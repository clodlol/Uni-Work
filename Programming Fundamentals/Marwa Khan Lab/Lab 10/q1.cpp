#include <iostream>
using namespace std;

int main()
{
    const int n = 30;
    char str[n];
    cout << "Enter a string: ";
    cin.getline(str, 30);

    int vowelCount = 0;
    for (int i = 0; i < n; i++)
    {
        switch (str[i])
        {
        case 'A':
        case 'a':
        case 'E':
        case 'e':
        case 'I':
        case 'i':
        case 'O':
        case 'o':
        case 'U':
        case 'u':
            vowelCount++;
            break;
        default:
            break;
        }
    }

    cout << vowelCount << endl;

    system("pause");
    return 0;
}