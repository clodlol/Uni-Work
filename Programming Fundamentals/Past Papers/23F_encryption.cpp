#include <iostream>
using namespace std;

int main()
{
    const int n = 14;
    char plainText[n + 1] = "MY.NAME.IS.DON";
    char cipherText[n + 1];
    int cipherTextCounter = 0;
    const int k = 2;

    int counter = 0;
    while (counter < k)
    {
        for (int i = 0; ((i * k) + counter) <= n; i++)
        {
            cout << "Adding " << "t[" << (i * k) << "+" << counter << "]" << endl;
            cipherText[cipherTextCounter++] = plainText[(i * k) + counter];
        }
        counter++;
    }

    for (int i = 0; i <= cipherTextCounter; i++)
    {
        cout << cipherText[i];
    }

    cout << endl;
    system("pause");
    return 0;
}