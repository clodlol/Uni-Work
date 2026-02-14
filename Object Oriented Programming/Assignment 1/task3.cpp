#include <iostream>
using namespace std;

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

char **compileDict(const char *const &input, int &dictSize)
{
    char **temp = new char *[dictSize];

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

    char **dict = new char *[wordCount];
    for (int i = 0; i < wordCount; i++)
    {
        dict[i] = new char[strlen(temp[i]) + 1];
        strcpy(dict[i], temp[i]);
        delete[] temp[i];
    }
    delete[] temp;
    temp = nullptr;

    dictSize = wordCount;
    return dict;
}

void printDict(const char *const *const &dict, const int &words)
{
    for (int i = 0; i < words; i++)
    {
        cout << dict[i] << endl;
    }
}

char **dictIntersection(const char *const *const &dictA, const int &sizeA, const char *const *const &dictB, const int &sizeB, int &sizeInter)
{
    sizeInter = 0;
    char **temp = new char *[min(sizeA, sizeB)];
    for (int i = 0; i < sizeA; i++)
    {
        bool found = false;
        for (int j = 0; j < sizeB; j++)
        {
            if (dictA[i] == dictB[j])
            {
                found = true;
                break;
            }
        }

        bool dupe = checkDupeInDict(temp, sizeInter, dictA[i]);

        if (!dupe && found)
        {
            temp[sizeInter] = new char[strlen(dictA[i]) + 1];
            strcpy(temp[sizeInter], dictA[i]);
            sizeInter++;
        }
    }

    char **inter = new char *[sizeInter];
    for (int i = 0; i < sizeInter; i++)
    {
        inter[i] = new char[strlen(temp[i]) + 1];
        strcpy(inter[i], temp[i]);
        delete[] temp[i];
    }
    delete[] temp;
    temp = nullptr;

    return inter;
}

int main()
{
    int sizeA = 100, sizeB = 100, sizeInter = 0;
    char **dictA = compileDict("I love Pakistan.", sizeA);
    char **dictB = compileDict("They love Pakistan.", sizeB);
    char **inter = dictIntersection(dictA, sizeA, dictB, sizeB, sizeInter);
    printDict(inter, sizeInter);
    cout << "Size of intersection: " << sizeInter << endl;
    return 0;
}