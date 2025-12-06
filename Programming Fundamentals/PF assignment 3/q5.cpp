#include <iostream>
#include <limits>
using namespace std;

const int MAX_SET_SIZE = 100;

bool getInt(int &input, int rangeStart, int rangeEnd);

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int calculateUnion(int setA[], int sizeA, int setB[], int sizeB, int out[]);
int calculateIntersection(int setA[], int sizeA, int setB[], int sizeB, int out[]);
int calculateDifference(int setA[], int sizeA, int setB[], int sizeB, int out[]);

int main()
{
    int first[MAX_SET_SIZE] = {0}, second[MAX_SET_SIZE] = {0};
    int m = 0, n = 0;

    while (true)
    {
        cout << "Enter the size of first set: ";
        if (!getInt(m, 1, MAX_SET_SIZE))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the size of second set: ";
        if (!getInt(n, 1, MAX_SET_SIZE))
            continue;
        else
            break;
    }

    cout << "First set: " << endl;
    for (int i = 0; i < m;)
    {
        cout << "[" << i << "]: ";
        if (!getInt(first[i], INT_MIN, INT_MAX))
            continue;
        else
            i++;
    }

    cout << "Second set: " << endl;
    for (int i = 0; i < n;)
    {
        cout << "[" << i << "]: ";
        if (!getInt(second[i], INT_MIN, INT_MAX))
            continue;
        else
            i++;
    }

    int setUnion[MAX_SET_SIZE + MAX_SET_SIZE] = {0};
    int unionLen = calculateUnion(first, m, second, n, setUnion);

    int setIntesection[MAX_SET_SIZE] = {0};
    int intersectionLen = calculateIntersection(first, m, second, n, setIntesection);

    int setDifference[MAX_SET_SIZE] = {0};
    int differenceLen = calculateDifference(first, m, second, n, setDifference);

    cout << endl;
    cout << "Union: " << endl
         << "[";
    for (int i = 0; i < unionLen; i++)
    {
        cout << setUnion[i] << " ";
    }
    cout << "]" << endl;

    cout << endl;
    cout << "Intersection: " << endl
         << "[";
    for (int i = 0; i < intersectionLen; i++)
    {
        cout << setIntesection[i] << " ";
    }
    cout << "]" << endl;

    cout << endl;
    cout << "Difference: " << endl
         << "[";
    for (int i = 0; i < differenceLen; i++)
    {
        cout << setDifference[i] << " ";
    }
    cout << "]" << endl;

    system("pause");
    return 0;
}

int calculateUnion(int setA[], const int sizeA, int setB[], const int sizeB, int out[])
{
    int temp[MAX_SET_SIZE + MAX_SET_SIZE] = {0};

    for (int i = 0; i < sizeA; i++)
    {
        temp[i] = setA[i];
    }

    for (int i = 0; i < sizeB; i++)
    {
        temp[i + sizeA] = setB[i];
    }

    int outCounter = 0;

    for (int i = 0; i < sizeA + sizeB; i++)
    {
        bool found = false;
        for (int j = 0; j < outCounter; j++)
        {
            if (out[j] == temp[i])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            out[outCounter] = temp[i];
            outCounter++;
        }
    }

    return outCounter;
}

int calculateIntersection(int setA[], int sizeA, int setB[], int sizeB, int out[])
{
    int outCounter = 0;

    for (int i = 0; i < sizeA; i++)
    {
        bool found = false;
        for (int j = 0; j < sizeB; j++)
        {
            if (setA[i] == setB[j])
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            bool dupeFound = false;
            for (int j = 0; j < outCounter; j++)
            {
                if (out[j] == setA[i])
                {
                    dupeFound = true;
                    break;
                }
            }

            if (!dupeFound)
            {
                out[outCounter] = setA[i];
                outCounter++;
            }
        }
    }

    return outCounter;
}

int calculateDifference(int setA[], int sizeA, int setB[], int sizeB, int out[])
{
    int outCounter = 0;

    for (int i = 0; i < sizeA; i++)
    {
        bool found = false;
        for (int j = 0; j < sizeB; j++)
        {
            if (setA[i] == setB[j])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            bool dupeFound = false;
            for (int j = 0; j < outCounter; j++)
            {
                if (out[j] == setA[i])
                {
                    dupeFound = true;
                    break;
                }
            }

            if (!dupeFound)
            {
                out[outCounter] = setA[i];
                outCounter++;
            }
        }
    }

    return outCounter;
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
