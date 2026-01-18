#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

int setUnion(int first[], const int sizeFirst, int second[], const int sizeSecond, int out[])
{
    int temp[MAX_SIZE] = {0};
    int tempCounter = 0;
    for (int i = 0; i < sizeFirst; i++)
        temp[tempCounter++] = first[i];

    for (int i = 0; i < sizeSecond; i++)
        temp[tempCounter++] = second[i];

    int outCounter = 0;
    for (int i = 0; i < tempCounter; i++)
    {
        int current = temp[i];
        bool dupe = false;
        for (int j = 0; j <= outCounter; j++)
        {
            if (out[j] == current)
                dupe = true;
        }

        if (!dupe)
        {
            out[outCounter++] = temp[i];
        }
    }

    return outCounter;
}

int setIntersection(int first[], const int sizeFirst, int second[], const int sizeSecond, int out[])
{
    int outCounter = 0;
    for (int i = 0; i < sizeFirst; i++)
    {
        bool found = false;
        for (int j = 0; j < sizeSecond; j++)
        {
            if (first[i] == second[j])
                found = true;
        }

        if (found)
        {
            bool dupeFound = false;
            for (int j = 0; j < outCounter; j++)
            {
                if (out[j] == first[i])
                {
                    dupeFound = true;
                    break;
                }
            }

            if (!dupeFound)
            {
                out[outCounter++] = first[i];
            }
        }
    }

    return outCounter;
}

int setDifference(int first[], const int sizeFirst, int second[], const int sizeSecond, int out[])
{
    int outCounter = 0;
    for (int i = 0; i < sizeFirst; i++)
    {
        int found = false;
        for (int j = 0; j < sizeSecond; j++)
        {
            if (first[i] == second[j])
                found = true;
        }

        if (!found)
        {
            bool dupeFound = false;
            for (int j = 0; j < outCounter; j++)
            {
                if (out[j] == first[i])
                {
                    dupeFound = true;
                    break;
                }
            }

            if (!dupeFound)
            {
                out[outCounter++] = first[i];
            }
        }
    }

    return outCounter;
}

int main()
{
    const int m = 5, n = 5;
    int first[MAX_SIZE] = {1, 2, 2, 7, 8};
    int second[MAX_SIZE] = {1, 2, 2, 9, 10};

    int U[MAX_SIZE] = {0};
    int unionSize = setUnion(first, m, second, n, U);

    cout << "============== UNION ==============" << endl;
    for (int i = 0; i < unionSize; i++)
    {
        cout << U[i] << " ";
    }
    cout << endl;

    int N[MAX_SIZE] = {0};
    int intersectionSize = setIntersection(first, m, second, n, N);

    cout << "============== INTERSECTION ==============" << endl;
    for (int i = 0; i < intersectionSize; i++)
    {
        cout << N[i] << " ";
    }
    cout << endl;

    int D[MAX_SIZE] = {0};
    int differenceSize = setDifference(first, m, second, n, D);

    cout << "============== DIFFERENCE ==============" << endl;
    for (int i = 0; i < differenceSize; i++)
    {
        cout << D[i] << " ";
    }
    cout << endl;

    system("pause");
    return 0;
}