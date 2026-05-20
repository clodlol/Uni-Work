#include <iostream>

char *extractWord(char *str, int currPos) // caller must delete[]
{
    int len = strlen(str + currPos);
    char *res = new char[len + 1];
    strcpy(res, (str + currPos));
    return res;
}

bool isUnique(int row, int N, int col, char **data, char *target)
{
    for (int i = row; i < N; ++i)
    {

        for (int j = col; data[i][j] != '\0';)
        {
            char *currWord = extractWord(data[i], j);
            if (!currWord)
                break;

            if (strcmp(currWord, target) == 0)
            {
                delete[] currWord;
                return false;
            }

            delete[] currWord;
            j += strlen(currWord) + 1;
        }
    }

    return true;
}

int countOccurrences(char *word, char **data, int N)
{
    int occurrences = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; data[i][j] != '\0';)
        {
            char *currentWord = extractWord(data[i], j);
            if (!currentWord)
                break;
            if (strcmp(currentWord, word) == 0)
            {
                occurrences++;
            }

            delete[] currentWord;
            j += strlen(currentWord) + 1;
        }
    }
}

bool occurs(char *str, char *word)
{
    int j = 0;
    while (str[j] != '\0')
    {
        char *currentWord = extractWord(str, j);
        if (!currentWord)
            break;

        if (strcmp(currentWord, word) == 0)
        {
            delete[] currentWord;
            return true;
        }

        delete[] currentWord;
        j += strlen(currentWord) + 1;
    }

    return false;
}

int createIndex(char **tweets, int N)
{
    int wordCount = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; tweets[i][j] != '\0';)
        {
            char *currentWord = extractWord(tweets[i], j);
            int wordLen = strlen(currentWord);

            if (isUnique(i, N, j, tweets, currentWord))
            {
                wordCount++;
            }

            delete[] currentWord;
            j += wordLen + 1;
        }
    }

    char **words = new char *[wordCount];
    int wordsCounter = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; tweets[i][j] != '\0';)
        {
            char *currentWord = extractWord(tweets[i], j);
            int wordLen = strlen(currentWord);
            if (isUnique(i, N, j, tweets, currentWord))
            {
                words[wordsCounter] = new char[wordLen + 1];
                strcpy(words[wordsCounter], currentWord);
                wordsCounter++;
            }

            delete[] currentWord;
            j += wordLen + 1;
        }
    }

    int **freq = new int *[wordCount];
    for (int i = 0; i < wordCount; ++i)
    {
        freq[i] = new int[countOccurrences(words[i], tweets, N) + 1];
        int occurrencesCounter = 0;

        for (int j = 0; j < N; ++j)
        {
            if (occurs(tweets[j], words[i]))
            {
                freq[i][occurrencesCounter] = (j + 1);
                occurrencesCounter++;
            }
        }

        freq[i][occurrencesCounter] = -1;
    }
}