#include <iostream>
using namespace std;

const int M = 20;
const int N = 100;
const int DICT_MAX_SIZE = 100;

void printHashtagDict(const char *const *const &dict)
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

char **extractHashtags(const char tweets[][N], const int &M)
{
    int hashtagCounter = 0;
    char **tempDict = new char *[DICT_MAX_SIZE];
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; (tweets[i][j] != '\0'); j++)
        {
            if (tweets[i][j] == '#')
            {
                string currHashtag;
                for (int k = j + 1; (tweets[i][k] != ' ' && tweets[i][k] != '#' && tweets[i][k] != '\0'); k++)
                {
                    currHashtag += tweets[i][k];
                }

                bool dupe = checkDupeInDict(tempDict, hashtagCounter, currHashtag.c_str());

                if (!dupe)
                {
                    int currentHashtagSize = currHashtag.size();
                    tempDict[hashtagCounter] = new char[currentHashtagSize + 1];
                    strcpy(tempDict[hashtagCounter], currHashtag.c_str());
                    tempDict[hashtagCounter][currentHashtagSize] = '\0';
                    hashtagCounter++;
                }
            }
        }
    }

    char **hashtagDict = new char *[hashtagCounter + 1];
    for (int i = 0; i < hashtagCounter; i++)
    {
        hashtagDict[i] = new char[strlen(tempDict[i]) + 1];
        strcpy(hashtagDict[i], tempDict[i]);
        delete[] tempDict[i];
    }
    hashtagDict[hashtagCounter] = "\0";
    delete[] tempDict;
    tempDict = nullptr;

    return hashtagDict;
}

int main()
{
    char tweets[M][N] = {
        "I love programming! #coding #developer #tech",
        "Just read a great book about AI! #reading #AI #books",
        "The weather today is fantastic! #sunny #beautiful",
        "Had an amazing workout session! #fitness #health #motivation",
        "Finally, coffee time! #coffee #morning #energy",
        "Learning C programming! #coding #learning",
        "Can't wait for the weekend! #weekendvibes #excited",
        "Enjoying a relaxing day at the beach! #vacation #beach #relax",
        "New project starting today! #work #project #goals",
        "Running in the park! #fitness #nature",
        "Loving this tech conference! #tech #developer #AI",
        "Weekend vibes and relaxation time! #weekendvibes #vacation #relax",
        "Fitness goals achieved today! #fitness #health #motivation",
        "Finally got my first coffee today! #coffee #morning #energy",
        "Building a new app with C! #coding #developer",
        "Taking a walk at the beach. #beach #vacation #nature",
        "Just finished an AI course! #AI #learning #tech",
        "Work is so rewarding today! #work #project #goals",
        "A morning walk to clear my mind! #morning #fitness #nature",
        "Amazing sunny day! #sunny #beautiful #weekendvibes",
    };

    char **hashtagDict = extractHashtags(tweets, M);
    printHashtagDict(hashtagDict);

    return 0;
}