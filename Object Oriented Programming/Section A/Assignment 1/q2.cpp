#include <iostream>
using namespace std;

const int MAX_ATTEMPT_SIZE = 100;

char **inputStudentNames(const int &n)
{
    char **nameDict = new char *[n];
    for (int i = 0; i < n; i++)
    {
        string tempName;
        cout << "Enter student " << (i + 1) << " name: ";
        cin >> tempName;

        nameDict[i] = new char[tempName.size() + 1];
        strcpy(nameDict[i], tempName.c_str());
    }

    return nameDict;
}

int **inputStudentAttempts(const int &n)
{
    int **attemptTable = new int *[n]; // there are n students
    for (int i = 0; i < n; i++)
    {
        int attempts = 0;
        cout << "Enter number of attempts for student " << (i + 1) << ": ";
        cin >> attempts;
        attemptTable[i] = new int[attempts + 1];
        cout << "Enter scores for student " << (i + 1) << ": ";
        for (int j = 0; j < attempts; j++)
        {
            int currentAttemptMarks = 0;
            while (currentAttemptMarks <= 0)
            {
                cin >> currentAttemptMarks;
            }

            attemptTable[i][j] = currentAttemptMarks;
        }
        attemptTable[i][attempts] = -1;
    }

    return attemptTable;
}

void printResults(const int &n, const char *const *const &studentNameDict, const int *const *const &attemptTable)
{
    for (int i = 0; i < n; i++)
    {
        float average = 0;
        int best = INT_MIN, attemptCount = 0;

        for (int j = 0; attemptTable[i][j] != -1; j++)
        {
            average += attemptTable[i][j];
            attemptCount++;
            if (attemptTable[i][j] > best)
                best = attemptTable[i][j];
        }

        average /= attemptCount;

        cout << studentNameDict[i] << " -> " << "Average: " << average << " | Best: " << best << endl;
    }
}

void updateScore(const int &n, const int &index, int **const &attemptTable, const int &newScore)
{
    int count = 0;
    for (int i = 0; attemptTable[index][i] != -1; i++)
        count++;

    const int *oldAttempts = attemptTable[index];
    attemptTable[index] = new int[(count + 1) + 1];

    for (int i = 0; i < count; i++)
        attemptTable[index][i] = oldAttempts[i];

    attemptTable[index][count] = newScore;
    attemptTable[index][count + 1] = -1;

    delete[] oldAttempts;
    oldAttempts = nullptr;
}

int main()
{
    int studentCount = 0;
    cout << "Enter number of students: ";
    cin >> studentCount;
    char **studentDict = inputStudentNames(studentCount);
    int **attemptTable = inputStudentAttempts(studentCount);
    printResults(studentCount, studentDict, attemptTable);

    while (true)
    {
        int newAttempt = -1;
        cout << "Add another attempt for a student? (1 = Yes, 0 = No): ";
        while (newAttempt < 0 || newAttempt > 1)
        {
            cin >> newAttempt;
        }

        if (!newAttempt)
            break;

        int studentIndex = -1, score = -1;

        cout << "Enter 0-based student index: ";
        while (studentIndex < 0 || (studentIndex >= studentCount))
        {
            cin >> studentIndex;
        }

        cout << "Enter new score: ";
        while (score <= 0)
        {
            cin >> score;
        }

        updateScore(studentCount, studentIndex, attemptTable, score);
        printResults(studentCount, studentDict, attemptTable);
    }

    return 0;
}