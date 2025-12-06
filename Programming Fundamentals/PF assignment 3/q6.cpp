#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX_INPUT_SIZE = 100;
const double MAX_MARKS = 10.0;

bool getDouble(double &input, double rangeStart, double rangeEnd);
bool getInt(int &input, int rangeStart, int rangeEnd);

int main()
{
    double report[MAX_INPUT_SIZE][MAX_INPUT_SIZE] = {0};
    double maxes[MAX_INPUT_SIZE] = {0}; // we will fill m max marks here
    int m = 0, n = 0;                   // students: m, quizzes: n

    while (true)
    {
        cout << "Enter the number of students: ";
        if (!getInt(m, 1, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the number of quizzes: ";
        if (!getInt(n, 1, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    cout << endl;
    for (int i = 0; i < m; i++)
    {
        cout << "Student: " << (i + 1) << endl;
        for (int j = 0; j < n;)
        {
            cout << "Quiz " << (j + 1) << ": ";
            if (!getDouble(report[i][j], 0, MAX_MARKS))
                continue;
            else
                j++;
        }
        cout << endl;
    }

    for (int i = 0; i < m; i++)
    {
        cout << "Student " << (i + 1) << " -> ";
        double min = 10, max = 0, avg = 0;
        for (int j = 0; j < n; j++)
        {
            if (report[i][j] < min)
                min = report[i][j];
            else if (report[i][j] > max)
                max = report[i][j];

            avg += report[i][j];
        }
        avg /= n;

        cout << "Min: ";
        cout << setw(2) << min << "  ";
        cout << "Max: ";
        cout << setw(2) << max << "  ";
        cout << "Avg: ";
        cout << setw(2) << avg << "  ";

        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Quiz " << (i + 1) << " -> ";
        double min = 10, max = 0;
        for (int j = 0; j < m; j++)
        {
            if (report[j][i] < min)
                min = report[j][i];
            else if (report[j][i] > max)
                max = report[j][i];
        }

        cout << "Min: ";
        cout << setw(2) << min << "  ";
        cout << "Max: ";
        cout << setw(2) << max << "  ";

        cout << endl;
    }

    int maxScore = 0;
    int maxScoreIndex = 0;
    for (int i = 0; i < m; i++)
    {
        if (maxes[i] > maxScore)
        {
            maxScore = maxes[i];
            maxScoreIndex = i;
        }
    }

    cout << "Student with highest marks: " << (maxScoreIndex + 1) << endl;
    system("pause");
    return 0;
}

bool getDouble(double &input, double rangeStart, double rangeEnd)
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