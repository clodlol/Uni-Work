#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;

const int MAX_DICT_SIZE = 100;
const int MAX_SYN_SIZE = 100;
const int MAX_SENTENCE_SIZE = 1000;
const int MAX_WORD_SIZE = 100;

int getRandomNum(int min, int max);
void printDict(const char *const *const &dict);
bool checkDupeInDict(const char *const *const &dict, const int &checkingRange, const char *const &targetWord);
char **compileDict(const char *const &input);
char *inputSynonym();
void printSynDict(const char *const *const *const &synDict, const int &wordCount);
int getDictSize(const char *const *const &dict);
int getSynCount(const char *const *const *const &synDict, const int &index);
char ***compileSynDict(const char *const *const &inputDict);
char **dictIntersection(const char *const *const &dictA, const char *const *const &dictB);
char *replaceSyn(const char *const &input, const char *const *const *const &synDict);

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
    char *input = "This is my assignment";
    char **dict = compileDict(input);
    char ***synDict = compileSynDict(dict);
    char *data = "This is my assignment";

    cout << replaceSyn(data, synDict) << endl;

    return 0;
}

char *extractWord(const char str[], int index)
{
    int tempWordCounter = 0;
    char tempWord[MAX_WORD_SIZE];
    for (int i = index; (str[i] != ' ' && str[i] != '\0'); i++)
    {
        tempWord[tempWordCounter++] = str[i];
    }
    tempWord[tempWordCounter] = '\0';

    char *word = new char[tempWordCounter + 1];
    strcpy(word, tempWord);

    return word;
}

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

bool checkDupeInDict(const char *const *const &dict, const int &checkingRange, const char *const &targetWord)
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

    int i = 0, wordCount = 0;
    while (i < strlen(input))
    {
        char *currentWord = extractWord(input, i);
        bool dupe = checkDupeInDict(temp, wordCount, currentWord);

        if (!dupe)
        {
            temp[wordCount] = new char[strlen(currentWord) + 1];
            strcpy(temp[wordCount++], currentWord);
        }

        i += (strlen(currentWord) + 1); // +1 for whitespace
    }

    char **dict = new char *[wordCount + 1];
    for (int j = 0; j < wordCount; j++)
    {
        dict[j] = new char[strlen(temp[j]) + 1];
        strcpy(dict[j], temp[j]);
        delete[] temp[j];
    }
    delete[] temp;
    temp = nullptr;

    dict[wordCount] = "\0";
    return dict;
}

char *inputSynonym()
{
    string input;
    while (input.size() <= 0)
    {
        cin >> input;
    }

    int inputSize = input.size();
    char *inputPtr = new char[inputSize + 1];
    strcpy(inputPtr, input.c_str());
    inputPtr[inputSize] = '\0';

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
            char *inputSyn = inputSynonym();

            synonymDict[i][j] = new char[strlen(inputSyn) + 1];
            strcpy(synonymDict[i][j], inputSyn);
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
            strcpy(tempInter[sizeInter++], dictA[i]);
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

    for (int i = 0; i < strlen(input);)
    {
        int foundIndex = -1;
        char *currentWord = extractWord(input, i);
        for (int i = 0; i < getDictSize(inputDict); i++)
        {
            if (strcmp(inputDict[i], currentWord) == 0)
            {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == -1)
        {
            for (int i = 0; i < strlen(currentWord); i++)
            {
                temp[tempCounter++] = currentWord[i];
            }

            temp[tempCounter++] = ' ';
        }
        else
        {
            int synCount = getSynCount(synDict, foundIndex);
            if (synCount == 0)
            {
                for (int i = 0; i < strlen(currentWord); i++)
                {
                    temp[tempCounter++] = currentWord[i];
                }

                temp[tempCounter++] = ' ';
            }
            else
            {
                int randomSynIndex = getRandomNum(0, synCount - 1); // i have to change this randomized ahh logic
                for (int i = 0; i < strlen(synDict[foundIndex][randomSynIndex]); i++)
                {
                    temp[tempCounter++] = synDict[foundIndex][randomSynIndex][i];
                }

                temp[tempCounter++] = ' ';
            }
        }

        i += (strlen(currentWord) + 1); // +1 for space
    }

    temp[tempCounter] = '\0';

    char *output = new char[strlen(temp) + 1];
    strcpy(output, temp);

    delete[] temp;
    temp = nullptr;

    return output;
}
