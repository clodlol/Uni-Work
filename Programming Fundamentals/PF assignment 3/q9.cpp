#include <iostream>
#include <limits>
#include <cstring>
using namespace std;

bool getInt(int &input, int rangeStart, int rangeEnd);
void getCourseCode(char input[]);

const int ROOM_LIMIT = 100;
const int TIMESLOT_LIMIT = 100;

int main()
{
    string timeTable[TIMESLOT_LIMIT][ROOM_LIMIT];
    int r = 0, c = 0;

    while (true)
    {
        cout << "Enter the number of time slots: ";
        if (!getInt(r, 0, TIMESLOT_LIMIT))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the number of rooms: ";
        if (!getInt(c, 0, ROOM_LIMIT))
            continue;
        else
            break;
    }

    cin.ignore(7, '\n');
    cin.clear();

    for (int i = 0; i < r; i++)
    {
        cout << "Timeslot " << (i + 1) << ": " << endl;
        for (int j = 0; j < c; j++)
        {
            cout << "Room " << (j + 1) << ": ";
            char currentCode[7];
            getCourseCode(currentCode);

            timeTable[i][j] = currentCode;
        }
    }

    cout << "---------------------TIMETABLE---------------------" << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << timeTable[i][j] << "     ";
        }
        cout << endl;
    }
    cout << "---------------------------------------------------" << endl;

    int emptySlots = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int courseCount = 0;

            if (timeTable[i][j] == "--")
            {
                emptySlots++;
                continue;
            }

            for (int k = 0; k < c; k++)
            {
                if ((timeTable[i][k] == timeTable[i][j]))
                {
                    courseCount++;
                }
            }

            if (courseCount > 1)
            {
                cout << "Conflict: " << timeTable[i][j] << " appears " << courseCount << " times in timeslot " << (i + 1) << endl;
            }
        }
    }

    int longest = INT_MIN;
    string mostFreqCourse;
    for (int i = 0; i < r * c; i++)
    {
        string currentElement = timeTable[i / c][i % c];
        if (currentElement == "--")
            continue;

        int currentElementCount = 0;
        for (int j = 0; j < r * c; j++)
        {
            if (timeTable[j / c][j % c] == currentElement)
            {
                currentElementCount++;
            }
        }

        if (currentElementCount > longest)
        {
            longest = currentElementCount;
            mostFreqCourse = currentElement;
        }
    }

    cout << "Most frequent course: " << mostFreqCourse << endl;
    cout << "Total empty slots: " << emptySlots << endl;

    cout << endl;
    system("pause");
    return 0;
}

bool getInt(int &input, int rangeStart, int rangeEnd)
{
    if (cin >> input)
    {
        return (input >= rangeStart && input <= rangeEnd);
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

void getCourseCode(char input[])
{
    cin.getline(input, 7);
}