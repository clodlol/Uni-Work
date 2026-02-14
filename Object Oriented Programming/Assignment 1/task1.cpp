#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;

const int MAX_TEMP_SIZE = 100;

void printDict(const char *const *const &dict)
{
    for (int i = 0; (strcmp(dict[i], "\0") != 0); i++)
    {
        cout << dict[i] << endl;
    }
}

bool checkDupeInDict(const char *const *const &dict, const int &checkingRange, const char *targetWord)
{
    bool dupe = false;
    for (int i = 0; i < checkingRange; i++)
    {
        if (strcmp(dict[i], targetWord) == 0)
            dupe = true;
    }

    return dupe;
}

char **compileDict(const char *const &input)
{
    char **temp = new char *[MAX_TEMP_SIZE];

    int wordCount = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == ' ' || i == 0)
        {
            string currentWord;
            int letterCount = 0;
            for (int j = ((i == 0) ? (i) : (i + 1)); (input[j] != ' ' && input[j] != '\0' && input[j] != '.'); j++)
            {
                letterCount++;
                currentWord += input[j];
            }

            bool dupe = checkDupeInDict(temp, wordCount, currentWord.c_str());

            if (!dupe)
            {
                temp[wordCount] = new char[letterCount + 1];

                for (int k = 0; k < letterCount; k++)
                {
                    temp[wordCount][k] = input[((i == 0) ? (i) : (i + 1)) + k];
                }
                temp[wordCount][letterCount] = '\0';

                wordCount++;
            }
        }
    }

    char **dict = new char *[wordCount + 1];
    for (int i = 0; i < wordCount; i++)
    {
        dict[i] = new char[strlen(temp[i]) + 1];
        strcpy(dict[i], temp[i]);
        delete[] temp[i];
    }
    delete[] temp;
    temp = nullptr;

    dict[wordCount] = "\0";
    return dict;
}

// char *readInputFromFile(string filename)
// {
//     int size = 0, c = 0; // null terminator
//     fstream file(filename, ios::in);
//     string s;

//     while (getline(file, s))
//     {
//         size += s.size();
//     }

//     char *input = new char[size + 1];
//     while (getline(file, s))
//     {
//         for (int i = 0; i < s.size(); i++)
//             input[c++] = s[i];
//     }
//     input[c] = '\0';

//     cout << input << endl;

//     return input;
// }

int main()
{
    // char *input = readInputFromFile("input.txt");
    char *input = "If you can dream it you can achieve it.";
    int dictSize = MAX_TEMP_SIZE; // subject to change
    char **dict = compileDict(input);
    printDict(dict);
    return 0;
}