#include <iostream>
using namespace std;

int longestIncStreak(int dataSet[], int size)
{
    int longest = 0;
    int count = 0;
    for (int i = 1; i < size; i++)
    {
        if (dataSet[i] > dataSet[i - 1])
            count++;
        else
        {
            if (count > longest)
                longest = count;
            count = 0;
        }
    }

    if (count > longest)
        longest = count;

    return longest;
}

int longestDecStreak(int dataSet[], int size)
{
    int longest = 0;
    int count = 0;
    for (int i = 1; i < size; i++)
    {
        if (dataSet[i] < dataSet[i - 1])
            count++;
        else
        {
            if (count > longest)
                longest = count;
            count = 0;
        }
    }

    if (count > longest)
        longest = count;

    return longest;
}

int totalDistance(int dataSet[], int size)
{
    int total = 0;
    for (int i = 0; i < size; i++)
    {
        total += dataSet[i];
    }
    return total;
}

int totalCost(int totalDistance, const int price = 270)
{
    return totalDistance * price;
}

int aboveAvgDays(int dataSet[], int size, const int threshold = 20)
{
    double average = (double)totalDistance(dataSet, size) / size;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        double currentElement = (double)dataSet[i];
        if (currentElement >= average * (1 + threshold / 100.0))
            count++;
    }
    return count;
}

int main()
{
    int n = 0;
    while (true)
    {
        cout << "Enter the number of distances: ";
        cin >> n;

        if (n < 1 || n > 200)
            continue;
        else
            break;
    }

    int distances[n] = {0};

    for (int i = 0; i < n;)
    {
        cin >> distances[i];
        if (distances[i] < 0)
            continue;

        i++;
    }

    cout << "Longest increasing streak: " << longestIncStreak(distances, n) << " days" << endl;
    cout << "Longest decreasing streak: " << longestDecStreak(distances, n) << " days" << endl;
    cout << "Fuel Cost: Rs. " << totalCost(totalDistance(distances, n)) << endl;
    cout << "Above Avg +20\% Days: " << aboveAvgDays(distances, n) << endl;

    system("pause");
    return 0;
}