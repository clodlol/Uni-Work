#include <iostream>
using namespace std;

int countWords(const char *const &input)
{
    int words = 1;
    int counter = 0;
    while (input[counter] != '\0')
    {
        if (input[counter] == ' ')
            words++;
        counter++;
    }

    return words;
}

void printDict(const char *const *const &dict, const int &words)
{
    for (int i = 0; i < words; i++)
    {
        cout << dict[i] << endl;
    }
}

int main()
{
    // program that takes input a sentence, and makes a dynamically allocated dictionary

    char *input = "if you can dream it you can achieve it";
    int wordCount = countWords(input);
    char **dict = new char *[wordCount];

    int i = 0, currentWordCounter = 0;
    while (input[i] != '\0')
    {
        int currentLetterCounter = 0;
        if (input[i] == ' ' || i == 0)
        {
            int j = (i == 0) ? (i) : (i + 1);
            while (input[j] != ' ' && input[j] != '\0')
            {
                currentLetterCounter++;
                j++;
            }
            dict[currentWordCounter] = new char[currentLetterCounter + 1];

            for (int k = 0; k < currentLetterCounter; k++)
            {
                dict[currentWordCounter][k] = input[((i == 0) ? (i) : (i + 1)) + k];
            }
            dict[currentWordCounter][currentLetterCounter] = '\0';

            currentWordCounter++;
        }
        i++;
    }

    // todo: remove duplicates from dict OR implement duplicate logic in the upper loop

    printDict(dict, wordCount);
    return 0;
}