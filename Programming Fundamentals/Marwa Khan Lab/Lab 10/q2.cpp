#include <iostream>
using namespace std;

int main()
{
    const int n = 30;
    char first[n];
    char second[n];

    cout << "Enter your first name: ";
    cin.getline(first, n);

    cout << "Enter your second name: ";
    cin.getline(second, n);

    char concat[n + n + 1];
    int concatCounter = 0;
    for (int i = 0; first[i] != '\0'; i++)
    {
        concat[concatCounter++] = first[i];
    }
    concat[concatCounter++] = ' ';
    for (int i = 0; second[i] != '\0'; i++)
    {
        concat[concatCounter++] = second[i];
    }

    concat[concatCounter] = '\0';

    cout << "Joined name is: " << concat << endl;
    system("pause");
    return 0;
}