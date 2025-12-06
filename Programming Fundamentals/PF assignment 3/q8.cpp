#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX_INPUT_SIZE = 100;

void rotateRight(int arr[], int n, int k, int out[]);
void rotateLeft(int arr[], int n, int k, int out[]);
void insertOne(int arr[], int n, int a, int indexA, int out[]);
void removeOne(int arr[], int n, int indexA, int out[]);

bool getInt(int &input, int rangeStart, int rangeEnd);

int main()
{
    int items[MAX_INPUT_SIZE] = {0};
    int n = 0;

    while (true)
    {
        cout << "Enter the length of the shelf: ";
        if (!getInt(n, 1, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    cout << "Enter shelf items: " << endl;
    for (int i = 0; i < n;)
    {
        if (!getInt(items[i], INT_MIN, INT_MAX))
            continue;
        else
            i++;
    }

    int k = 1;

    cout << endl;
    while (true)
    {
        cout << "Enter rotation constant k: ";
        if (!getInt(k, 0, INT_MAX))
            continue;
        else
            break;
    }

    int rightRotated[MAX_INPUT_SIZE] = {0};
    rotateRight(items, n, k, rightRotated);

    cout << endl
         << "Right rotated by " << k << " items: " << endl;
    for (int i = 0; i < n; i++)
        cout << setw(4) << rightRotated[i] << " ";

    int leftRotated[MAX_INPUT_SIZE] = {0};
    rotateLeft(items, n, k, leftRotated);

    cout << endl
         << "Left rotated by " << k << " items: " << endl;
    for (int i = 0; i < n; i++)
        cout << setw(4) << leftRotated[i] << " ";

    int indexA = 0;
    int a = 0;

    cout << endl
         << endl;
    while (true)
    {
        cout << "Enter index to insert element at: ";
        if (!getInt(indexA, 0, n))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the new element: ";
        if (!getInt(a, INT_MIN, INT_MAX))
            continue;
        else
            break;
    }

    int afterInsertion[MAX_INPUT_SIZE + 1] = {0};
    insertOne(items, n, a, indexA, afterInsertion);

    cout << endl
         << "Inserted " << a << " at index " << indexA << ": " << endl;
    for (int i = 0; i < n + 1; i++)
        cout << setw(4) << afterInsertion[i] << " ";

    int indexB = 0;

    cout << endl
         << endl;
    while (true)
    {
        cout << "Enter index to remove element from: ";
        if (!getInt(indexB, 0, n - 1))
            continue;
        else
            break;
    }

    int afterRemoval[MAX_INPUT_SIZE - 1] = {0};
    removeOne(items, n, indexA, afterRemoval);

    cout << endl
         << "Removed element at index " << indexA << ": " << endl;
    for (int i = 0; i < n - 1; i++)
        cout << setw(4) << afterRemoval[i] << " ";

    cout << endl;
    system("pause");
    return 0;
}

void removeOne(int arr[], int n, int indexA, int out[])
{
    // length of out is n-1
    for (int i = 0; i < n - 1; i++)
    {
        if (i < indexA)
        {
            out[i] = arr[i];
        }
        else if (i >= indexA)
        {
            out[i] = arr[i + 1];
        }
    }
}

void insertOne(int arr[], int n, int a, int indexA, int out[])
{
    // length of out is n+1
    for (int i = 0; i < n + 1; i++)
    {
        if (i < indexA)
        {
            out[i] = arr[i];
        }
        else if (i == indexA)
        {

            out[i] = a;
        }
        else if (i > indexA)
        {
            out[i] = arr[i - 1];
        }
    }
}

void rotateRight(int arr[], int n, int k, int out[])
{
    k %= n;

    // length of out must be equal to n
    // 1234 -> 4123 (rotated by k = 1)
    // we divide into two sections (4), (123)

    for (int i = 0; i < n; i++)
    {
        if (i < k)
        {
            out[i] = arr[n - k + i];
        }
        else
        {
            out[i] = arr[i - k];
        }
    }
}

void rotateLeft(int arr[], int n, int k, int out[])
{
    k %= n;

    // length of out must be equal to n
    // 1234 -> 2341 (rotated by k = 1)
    // we divide into two sections (234), (1)

    for (int i = 0; i < n; i++)
    {
        if (i < n - k)
        {
            out[i] = arr[i + k];
        }
        else
        {
            out[i] = arr[i - n + k];
        }
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