#include <iostream>
#include <limits>
using namespace std;

const double DOUBLE_MAX = std::numeric_limits<double>::max();
const double DOUBLE_MIN = std::numeric_limits<double>::min();

double transform(double x);
double transform(double base, int power);
double transform(double values[], int size);

bool getDouble(double &input, double rangeStart, double rangeEnd);
bool getInt(int &input, int rangeStart, int rangeEnd);

int main()
{
    double x = 0, base = 0;
    int power = 0, n = 0;
    double arr[100] = {0};

    while (true)
    {
        cout << "Enter a real number x: ";
        if (!getDouble(x, DOUBLE_MIN, DOUBLE_MAX))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the exponentiation base: ";
        if (!getDouble(base, DOUBLE_MIN, DOUBLE_MAX))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the exponent: ";
        if (!getInt(power, INT_MIN, INT_MAX))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the array size: ";
        if (!getInt(n, 1, INT_MAX))
            continue;
        else
            break;
    }

    cout << "Array: " << endl;
    for (int i = 0; i < n;)
    {
        cout << "[" << i << "]: ";
        if (!getDouble(arr[i], DOUBLE_MIN, DOUBLE_MAX))
            continue;
        else
            i++;
    }

    cout << "Expression result: " << transform(x) << endl;
    cout << "Power result: " << transform(base, power) << endl;
    cout << "Average: " << transform(arr, n) << endl;

    system("pause");
    return 0;
}

double transform(double x)
{
    return (3 * x * x) - (5 * x) + 12;
}

double transform(double base, int power)
{
    double ans = 1;
    if (power == 0)
        return 1;

    for (int i = 1; i <= (power < 0 ? -power : power); i++)
    {
        ans *= base;
    }

    return (power < 0 ? (1 / ans) : ans);
}

double transform(double values[], int size)
{
    if (size <= 0)
    {
        cout << "Array size invalid." << endl;
        return 0;
    }

    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += values[i];
    }

    return sum / size;
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