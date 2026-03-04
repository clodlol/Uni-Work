#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;

const int MAX_DICT_SIZE = 100;
const int MAX_SENTENCE_SIZE = 1000;
const int MAX_SYN_SIZE = 100;
const int MAX_WORD_SIZE = 100;

bool checkDupeInDict(const char *const *const &dict, const int &checkingRange, const char *const &targetWord);
bool stringCmp(const char *const &a, const char *const &b, const int &rangeStart, const int &rangeEnd);
char **compileDict(const char *const &input);
char ***compileSynDict(const char *const *const &inputDict);
char **dictIntersection(const char *const *const &dictA, const char *const *const &dictB);
char *inputSynonym();
char *readInput(const char *const &filename);
char *replaceSyn(const char *const &input, const char *const *const &inputDict, const char *const *const *const &synDict);
int getDictSize(const char *const *const &dict);
int getSynCount(const char *const *const *const &synDict, const int &index);
void printDict(const char *const *const &dict);
void printSynDict(const char *const *const *const &synDict, const int &wordCount);
void writeOutput(const char *const &filename, const char *const &output);

int main()
{
    char *input = readInput("in.txt");
    char **dict = compileDict(input);
    char ***synDict = compileSynDict(dict);
    char *data = readInput("data.txt");
    writeOutput("out.txt", replaceSyn(data, dict, synDict));
    cout << "Ouput generated!" << "\n";
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
        int wordLen = strlen(currentWord);
        bool dupe = checkDupeInDict(temp, wordCount, currentWord);

        if (currentWord[wordLen - 1] == '.') // If the word contains a fullstop, remove it
        {
            char *temp = new char[wordLen - 1];
            for (int i = 0; i < wordLen - 1; i++)
            {
                temp[i] = currentWord[i];
            }
            temp[wordLen - 1] = '\0';
            delete[] currentWord;
            currentWord = temp;
        }

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
        getline(cin, input);
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

char *replaceSyn(const char *const &data, const char *const *const &inputDict, const char *const *const *const &synDict)
{
    int tempCounter = 0;
    char *temp = new char[MAX_SENTENCE_SIZE];

    printDict(inputDict);

    for (int i = 0; i < strlen(data);)
    {
        char *currentWord = extractWord(data, i);
        int foundIndex = -1, wordLen = strlen(currentWord), dictSize = getDictSize(inputDict);
        for (int j = 0; j < dictSize; j++)
        {
            // exclude fullstop if it exists in currentWord while comparing
            if (currentWord[wordLen - 1] == '.')
            {
                if (stringCmp(inputDict[j], currentWord, 0, wordLen - 2))
                {
                    foundIndex = j;
                    break;
                }
            }
            else
            {
                if (stringCmp(inputDict[j], currentWord, 0, wordLen - 1))
                {
                    foundIndex = j;
                    break;
                }
            }
        }

        if (foundIndex == -1)
        {
            for (int j = 0; j < wordLen; j++)
            {
                temp[tempCounter++] = currentWord[j];
            }

            temp[tempCounter++] = ' ';
        }
        else
        {
            int synCount = getSynCount(synDict, foundIndex), synIndex = -1;
            if (synCount == 0)
            {
                for (int j = 0; j < wordLen; j++)
                {
                    temp[tempCounter++] = currentWord[j];
                }

                temp[tempCounter++] = ' ';
                i += (wordLen + 1); // +1 for space
                continue;
            }
            else if (synCount == 1)
            {
                synIndex = 0;
            }
            else if (synCount > 1)
            {
                cout << "Synonyms found for " << currentWord << ": ";
                for (int j = 0; j < synCount; j++)
                    cout << (j) << ". " << synDict[foundIndex][j] << " ";
                cout << "\n"
                     << "Choose your option: ";
                while (synIndex < 0 || synIndex >= synCount)
                {
                    cin >> synIndex;
                }
            }

            for (int j = 0; j < strlen(synDict[foundIndex][synIndex]); j++)
            {
                temp[tempCounter++] = synDict[foundIndex][synIndex][j];
            }

            if (currentWord[wordLen - 1] == '.') // If the original word contains a fullstop, add a fullstop to the synonym
            {
                temp[tempCounter++] = '.';
            }

            temp[tempCounter++] = ' ';
        }

        i += (wordLen + 1); // +1 for space
    }

    temp[tempCounter] = '\0';

    char *output = new char[strlen(temp) + 1];
    strcpy(output, temp);

    delete[] temp;
    temp = nullptr;

    return output;
}

char *readInput(const char *const &filename)
{
    int tempCounter = 0;
    char temp[MAX_SENTENCE_SIZE];
    fstream file(filename, ios::in);
    string l;

    if (!file.is_open())
        return nullptr;

    while (getline(file, l))
    {
        for (int i = 0; i < l.size(); i++)
            temp[tempCounter++] = l[i];
    }

    temp[tempCounter] = '\0';
    char *input = new char[tempCounter + 1];
    strcpy(input, temp);

    file.close();
    return input;
}

void writeOutput(const char *const &filename, const char *const &output)
{
    fstream file(filename, ios::out);
    if (!file.is_open())
        return;

    file << output;

    file.close();
}

bool stringCmp(const char *const &a, const char *const &b, const int &rangeStart, const int &rangeEnd) // this function assumes [rangeStart..., rangeEnd] is valid allocated memory
{
    bool equal = true;
    for (int i = rangeStart; i <= rangeEnd; i++)
    {
        if (a[i] != b[i])
        {
            equal = false;
            break;
        }
    }

    return equal;
}