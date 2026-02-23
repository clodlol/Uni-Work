#include <iostream>
using namespace std;

const int MAX_WORD_LEN = 50, MAX_WORD_COUNT = 50, MAX_POSITION_COUNT = 50;

char *extractWord(char str[], int index)
{
    int tempWordCounter = 0;
    char tempWord[MAX_WORD_LEN];
    for (int i = index; (str[i] != ' ' && str[i] != '\0'); i++)
    {
        tempWord[tempWordCounter++] = str[i];
    }
    tempWord[tempWordCounter] = '\0';

    char *word = new char[tempWordCounter + 1];
    strcpy(word, tempWord);

    return word;
}

int **Word_Positions(char input[], int &wordCount)
{
    char tempWords[MAX_WORD_COUNT][MAX_WORD_LEN];
    int tempPositions[MAX_WORD_COUNT][MAX_POSITION_COUNT] = {-1};

    for (int i = 0; i < MAX_WORD_COUNT; ++i)
        for (int j = 0; j < MAX_POSITION_COUNT; ++j)
            tempPositions[i][j] = -1;

    int i = 0;
    wordCount = 0;
    while (i < strlen(input))
    {
        bool dupe = false;
        char *currentWord = extractWord(input, i);

        for (int j = 0; j < wordCount; j++)
        {
            if (strcmp(tempWords[j], currentWord) == 0)
            {
                dupe = true;
                break;
            }
        }

        if (!dupe)
        {
            strcpy(tempWords[wordCount++], currentWord);
        }

        for (int j = 0; j < wordCount; j++)
        {
            if (strcmp(currentWord, tempWords[j]) == 0)
            {
                // push position to tempPositions[j]
                int positionsCount = 0;
                for (int k = 0; tempPositions[j][k] != -1; k++)
                    positionsCount++;
                tempPositions[j][positionsCount] = i;
                tempPositions[j][positionsCount + 1] = -1;
            }
        }

        i += (strlen(currentWord) + 1); // skip space as well
    }

    int **positions = new int *[wordCount];
    for (int i = 0; i < wordCount; i++)
    {
        int c = 0;
        for (int j = 0; tempPositions[i][j] != -1; j++)
            c++;
        positions[i] = new int[c + 1];
        for (int j = 0; j < c; j++)
            positions[i][j] = tempPositions[i][j];
        positions[i][c] = -1;
    }

    return positions;
}

int main()
{
    int wordCount = 0;
    char str[] = "hello world hello world hello nigger baka kutta";
    int **positions = Word_Positions(str, wordCount);

    for (int i = 0; i < wordCount; i++)
    {
        for (int j = 0; positions[i][j] != -1; j++)
        {
            cout << positions[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}