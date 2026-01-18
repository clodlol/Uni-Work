#include <iostream>
using namespace std;

const int MAX_SIZE = 50;

void swap(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}

void reverseWords(char arr[])
{
    char words[MAX_SIZE][MAX_SIZE];
    int wordCounter = 0, letterCounter = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] == ' ' || arr[i + 1] == '\0')
        {
            if (arr[i + 1] == '\0')
            {
                words[wordCounter][letterCounter++] = arr[i];
            }
            words[wordCounter][letterCounter] = '\0';
            wordCounter++;
            letterCounter = 0;
            continue;
        }

        words[wordCounter][letterCounter++] = arr[i];
    }

    int arrCounter = 0;
    for (int i = wordCounter - 1; i >= 0; i--)
    {
        int j = 0;
        while (words[i][j] != '\0')
        {
            arr[arrCounter++] = words[i][j];
            j++;
        }
        arr[arrCounter++] = '\0';
    }
}

int main()
{
    char arr[] = "Welcome to programming class :)";
    reverseWords(arr);
    cout << arr << endl;
    system("pause");
}