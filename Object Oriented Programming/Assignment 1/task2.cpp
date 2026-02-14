#include <iostream>
using namespace std;

const int MAX_SYN_SIZE = 100;
const int MAX_TEMP_SIZE = 100;

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

char *inputSynonym(int &synonymSize)
{
    string input;
    cin >> input; // don't allow empty strings here

    char *inputPtr = new char[input.size() + 1];
    for (int i = 0; i < input.size(); i++)
        inputPtr[i] = input[i];
    inputPtr[input.size()] = '\0';

    synonymSize = input.size();
    return inputPtr;
}

void printSynDict(const char *const *const *const &synDict, const int &wordCount)
{
    for (int i = 0; i < wordCount; i++)
    {
        for (int j = 0; (strcmp(synDict[i][j], "\0") != 0); j++)
        {
            cout << synDict[i][j] << "  ";
        }
        cout << endl;
    }
}

int getDictSize(const char *const *const &dict)
{
    int c = 0;
    for (int i = 0; (strcmp(dict[i], "\0") != 0); i++)
        c++;
    return c;
}

int main()
{
    // TODO merge this file into task1.cpp
    char **inputDict = compileDict("coding programming billa.");
    int dictSize = getDictSize(inputDict);
    char ***synonymDict = new char **[dictSize + 1]; // storing synonyms rowwise

    for (int i = 0; i < dictSize; i++)
    {
        int x = 0;
        cout << "How many synonyms do you want to store for " << inputDict[i] << " ?";
        cin >> x; // for now, we assume x is a positive int
        synonymDict[i] = new char *[x + 1];
        for (int j = 0; j < x; j++)
        {
            int synSize = MAX_SYN_SIZE;
            char *tempSynonym = inputSynonym(synSize);

            synonymDict[i][j] = new char[synSize + 1];
            strcpy(synonymDict[i][j], tempSynonym);
        }
        synonymDict[i][x] = "\0"; // use an empty string for a sentinel value
    }

    printSynDict(synonymDict, dictSize);

    return 0;
}