#include <iostream>
#include <iomanip>
using namespace std;

int **getFactors(const int *const &numbers, const int &size)
{
    int **factorTable = new int *[size];
    for (int i = 0; i < size; i++)
    {
        int currentNumFactorCount = 0;
        for (int j = 1; j <= numbers[i]; j++)
        {
            if (numbers[i] % j == 0)
                currentNumFactorCount++;
        }

        factorTable[i] = new int[currentNumFactorCount + 1];

        int c = 0;
        for (int j = 1; j <= numbers[i]; j++)
        {
            if (numbers[i] % j == 0)
                factorTable[i][c++] = j;
        }

        factorTable[i][currentNumFactorCount] = '-1'; // sentinel value
    }

    return factorTable;
}

void inputNumbers(int *const &numbers, const int &size)
{
    for (int i = 0; i < size; i++)
    {
        int x = 0;
        cout << "Enter a number x (6 <= x <= 100): ";
        while (x < 6 || x > 100)
        {
            cin >> x;
        }

        numbers[i] = x;
    }
}

void printFactorTable(const int *const *const &table, const int &size)
{
    for (int i = 0; i < size; i++)
    {
        int j = 0;
        while (table[i][j] != '-1')
        {
            cout << left << setw(4) << table[i][j];
            j++;
        }
        cout << endl;
    }
}

int main()
{
    int n = 0;
    cout << "How many numbers do you want to calculate factors of? ";
    cin >> n;
    int *numbers = new int[n];

    inputNumbers(numbers, n);
    int **table = getFactors(numbers, n);

    delete[] numbers;
    numbers = nullptr;

    printFactorTable(table, n);

    return 0;
}