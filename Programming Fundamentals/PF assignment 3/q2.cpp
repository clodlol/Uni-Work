#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

double calculateStdDev(double dataSet[], int n, double mean);
int calculateAboveAvg(double dataSet[], double mean, int n);

bool getInt(int &input, int rangeStart, int rangeEnd);
bool getDouble(double &input, double rangeStart, double rangeEnd);

int main()
{
    int n = 0;
    double marks[100] = {0};

    while (true)
    {
        cout << "Enter the number of students: ";
        if (!getInt(n, 1, INT_MAX))
            continue;
        else
            break;
    }

    //double dataSet[n] = {0};
    double largest = 0;
    int lowest = 100;
    double average = 0;

    cout << "Student marks array: " << endl;
    for (int i = 0; i < n;)
    {
        cout << "[" << i << "]: ";
        if (!getDouble(marks[i], 0, 100))
            continue;
        else
        {
            double currentMarks = marks[i];
            lowest = (currentMarks < lowest ? currentMarks : lowest);
            largest = (currentMarks > largest ? currentMarks : largest);
            average += currentMarks;
            i++;
        }
    }

    average /= double(n);

    cout << "Highest: " << largest << endl;
    cout << "Lowest: " << lowest << endl;
    cout << "Average: " << average << endl;
    cout << "Standard Deviation: " << calculateStdDev(marks, n, average) << endl;
    cout << "Above Average: " << calculateAboveAvg(marks, average, n) << endl;

    system("pause");
    return 0;
}

double calculateStdDev(double dataSet[], int n, double mean)
{
    double variance = 0;
    for (int i = 0; i < n; i++)
    {
        variance += ((dataSet[i] - mean) * (dataSet[i] - mean));
    }
    variance /= double(n);
    return sqrt(variance);
}

int calculateAboveAvg(double dataSet[], double mean, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (dataSet[i] > mean)
            count++;
    }
    return count;
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