#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;

const int MAX_DICT_SIZE = 100;
const int MAX_SYN_SIZE = 100;
const int MAX_SENTENCE_SIZE = 1000;

int getRandomNum(int min, int max)
{
    int randNum = rand() % (max - min + 1) + min;
    return randNum;
}

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
    char **temp = new char *[MAX_DICT_SIZE];

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
    while (input.size() <= 0)
    {
        cin >> input;
    }

    int inputSize = input.size();
    char *inputPtr = new char[inputSize + 1];
    for (int i = 0; i < inputSize; i++)
        inputPtr[i] = input[i];
    inputPtr[inputSize] = '\0';

    synonymSize = inputSize;
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

int getSynCount(const char *const *const *const &synDict, const int &index) // get synonym count for a specified index
{
    int c = 0;
    for (int i = 0; (strcmp(synDict[index][i], "\0") != 0); i++)
        c++;

    return c;
}

char ***compileSynDict(const char *const *const &inputDict)
{
    const int wordCount = getDictSize(inputDict);
    char ***synonymDict = new char **[wordCount + 1];
    for (int i = 0; i < wordCount; i++)
    {
        int x = -1;
        cout << "How many synonyms do you want to store for " << inputDict[i] << " ? ";
        while (x < 0)
        {
            cin >> x;
        }
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

    return synonymDict;
}

char **dictIntersection(const char *const *const &dictA, const char *const *const &dictB)
{
    int sizeInter = 0;
    const int sizeA = getDictSize(dictA), sizeB = getDictSize(dictB);

    char **tempInter = new char *[min(sizeA, sizeB)];
    for (int i = 0; i < sizeA; i++)
    {
        bool found = false;
        for (int j = 0; j < sizeB; j++)
        {
            if (strcmp(dictA[i], dictB[j]) == 0)
            {
                found = true;
                break;
            }
        }

        bool dupe = checkDupeInDict(tempInter, sizeInter, dictA[i]);

        if (!dupe && found)
        {
            tempInter[sizeInter] = new char[strlen(dictA[i]) + 1];
            strcpy(tempInter[sizeInter], dictA[i]);
            sizeInter++;
        }
    }

    char **inter = new char *[sizeInter + 1];
    for (int i = 0; i < sizeInter; i++)
    {
        inter[i] = new char[strlen(tempInter[i]) + 1];
        strcpy(inter[i], tempInter[i]);
        delete[] tempInter[i];
    }
    delete[] tempInter;
    tempInter = nullptr;

    inter[sizeInter] = "\0";

    return inter;
}

char *replaceSyn(const char *const &input, const char *const *const *const &synDict)
{
    int tempCounter = 0;
    char *temp = new char[MAX_SENTENCE_SIZE];
    char **inputDict = compileDict(input);

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == ' ' || i == 0)
        {
            int foundIndex = -1;
            string currentWord;
            for (int j = (i == 0 ? i : (i + 1)); (input[j] != ' ' && input[j] != '\0' && input[j] != '.'); j++)
            {
                currentWord += input[j];
            }

            for (int i = 0; i < getDictSize(inputDict); i++)
            {
                if (strcmp(inputDict[i], currentWord.c_str()) == 0)
                {
                    foundIndex = i;
                    break;
                }
            }

            if (foundIndex == -1)
            {
                temp[tempCounter++] = input[i];
            }
            else
            {
                int synCount = getSynCount(synDict, foundIndex);

                if (i != 0)
                    temp[tempCounter++] = ' ';

                if (synCount == 0)
                {
                    for (int i = 0; i < currentWord.size(); i++)
                    {
                        temp[tempCounter++] = currentWord[i];
                    }
                    continue;
                }

                int randomSynIndex = getRandomNum(0, synCount - 1);
                for (int i = 0; i < strlen(synDict[foundIndex][randomSynIndex]); i++)
                {
                    temp[tempCounter++] = synDict[foundIndex][randomSynIndex][i];
                }
            }
        }
    }

    temp[tempCounter] = '\0';

    char *output = new char[strlen(temp) + 1];
    strcpy(output, temp);

    delete[] temp;
    temp = nullptr;

    return output;
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
    char *input = "This is my assignment.";
    char **dict = compileDict(input);
    char ***synDict = compileSynDict(dict);

    char *replaced = replaceSyn(input, synDict);

    cout << replaced << endl;

    return 0;
}