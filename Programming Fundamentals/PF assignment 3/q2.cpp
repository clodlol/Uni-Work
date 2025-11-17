#include <iostream>
#include <cmath>
using namespace std;

double calculateStdDev(double dataSet[], double mean, int n)
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

int main()
{
    int n = 0;
    int marks[100] = {0};
    while (true)
    {
        cout << "Enter the number of students: ";
        cin >> n;

        if (n < 1 || n > 100)
            continue;
        else
            break;
    }

    double dataSet[n] = {0};
    int largest = 0;
    int lowest = 100;
    double average = 0;

    for (int i = 0; i < n;)
    {
        cin >> marks[i];
        int currentMarks = marks[i];
        if (currentMarks < 0 || currentMarks > 100)
            continue;


        dataSet[i] += currentMarks;
        lowest = (currentMarks < lowest ? currentMarks : lowest);
        largest = (currentMarks > largest ? currentMarks : largest);
        average += currentMarks;
        i++;
    }
    average /= double(n);

    double variance = 0;
    for (int i = 0; i < n; i++)
    {
        variance += ((marks[i] - average) * (marks[i] - average));
    }
    variance /= double(n);

    cout << "Highest: " << largest << endl;
    cout << "Lowest: " << lowest << endl;
    cout << "Average: " << average << endl;
    cout << "Standard Deviation: " << calculateStdDev(dataSet, average, n) << endl;
    cout << "Above Average: " << calculateAboveAvg(dataSet, average, n) << endl;

    system("pause");
    return 0;
}