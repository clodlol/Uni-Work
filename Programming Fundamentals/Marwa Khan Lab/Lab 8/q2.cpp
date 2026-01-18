#include <iostream>
using namespace std;

void addCustomer(int queue[], const int &size, int newToken)
{
    bool full = true;

    for (int i = 0; i < size; i++)
    {
        if (queue[i] == -1)
        {
            full = false;
        }
    }

    for (int i = size - 1; i > 0; i--)
    {
        queue[i] = queue[i - 1];
    }
    queue[0] = newToken;

    if (full)
        cout << "Queue was already full -> Overwrote customers." << endl;
}

void serveCustomer(int queue[], const int &size)
{
    bool empty = true;

    for (int i = 0; i < size; i++)
    {
        if (queue[i] != -1)
            empty = false;
    }

    for (int i = 0; i < size - 1; i++)
    {
        queue[i] = queue[i + 1];
    }

    if (empty)
        cout << "Queue is empty -> No change." << endl;

    queue[size - 1] = -1;
}

void displayQueue(int queue[], int size)
{
    cout << "========= CURRENT QUEUE =========" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << queue[i] << " ";
    }

    cout << endl;
}

int main()
{
    const int size = 6;
    int arr[size] = {100, 101, 102, 103, 104, -1};

    displayQueue(arr, size);

    addCustomer(arr, size, 500);

    displayQueue(arr, size);

    serveCustomer(arr, size);

    displayQueue(arr, size);

    system("pause");
    return 0;
}