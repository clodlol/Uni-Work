#include <iostream>
#include <limits>
using namespace std;

const double DOUBLE_MAX = std::numeric_limits<double>::max();
const double DOUBLE_MIN = std::numeric_limits<double>::min();

int countIncDecStreak(double dataSet[], int n, int mode); // mode = 0: Decreasing, mode = 1: Increasing
int calculateCost(double dataSet[], int n, const int price = 270);
int aboveAvgDays(double dataSet[], int n, const int threshold = 20);

bool getInt(int &input, int rangeStart, int rangeEnd);
bool getDouble(double &input, double rangeStart, double rangeEnd);

int main()
{
    double distances[200] = {0};
    int n = 0;

    while (true)
    {
        cout << "Enter the number of distances: ";
        if (!getInt(n, 1, 200))
            continue;
        else
            break;
    }

    cout << "Distances of " << n << " days: " << endl;
    for (int i = 0; i < n;)
    {
        cout << "[" << (i + 1) << "th day]: ";
        if (!getDouble(distances[i], 0, DOUBLE_MAX))
            continue;
        else
            i++;
    }

    cout << "Longest increasing streak: " << countIncDecStreak(distances, n, 1) << " days" << endl;
    cout << "Longest decreasing streak: " << countIncDecStreak(distances, n, 0) << " days" << endl;
    cout << "Fuel Cost: Rs. " << calculateCost(distances, n) << endl;
    cout << "Above Avg +20\% Days: " << aboveAvgDays(distances, n) << endl;

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

int countIncDecStreak(double dataSet[], int n, int mode) // mode = 0: Decreasing, mode = 1: Increasing
{
    if (mode != 0 && mode != 1)
    {
        cout << "Invalid mode given to countIncDecStreak(). " << endl;
        system("pause");
        return -1;
    }

    int longest = 0;
    int count = 0;
    for (int i = 1; i < n; i++)
    {
        if (mode == 0 ? (dataSet[i] < dataSet[i - 1]) : (dataSet[i] > dataSet[i - 1]))
        {
            count++;
            if (count > longest)

                longest = count;
        }

        else
        {
            count = 0;
        }
    }

    return longest;
}

int calculateCost(double dataSet[], int n, const int price)
{
    double total = 0;
    for (int i = 0; i < n; i++)
    {
        total += dataSet[i];
    }
    return (total * price);
}

int aboveAvgDays(double dataSet[], int n, const int threshold)
{

    double total = 0;
    for (int i = 0; i < n; i++)
        total += dataSet[i];

    double average = total / double(n);
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        double currentElement = dataSet[i];
        if (currentElement >= average * (double)(1.0 + threshold / 100.0))
            count++;
    }
    return count;
}