#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX_INPUT_SIZE = 100;

void rotateRight(int arr[], int n, int k, int out[]);
void rotateLeft(int arr[], int n, int k, int out[]);

bool getInt(int &input, int rangeStart, int rangeEnd);

int main()
{
    int items[MAX_INPUT_SIZE] = {0};
    int n = 0;

    while(true)
    {
        cout << "Enter the length of the shelf: ";
        if(!getInt(n, 1, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    cout << "Enter shelf items: " << endl;
    for(int i = 0; i < n; )
    {   
        if(!getInt(items[i], INT_MIN, INT_MAX))
            continue;
        else
            i++;
    }

    int k = 1;

    while(true)
    {
        cout << "Enter right rotation constant: ";
        if(!getInt(k, 0, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    int rightRotated[n] = {0};
    rotateRight(items, n, k, rightRotated);

    cout << endl << "Right rotated by " << k << " items: " << endl;
    for(int i = 0; i < n; i++)
        cout << setw(4) << rightRotated[i] << " ";

    int leftRotated[n] = {0};
    rotateLeft(items, n, k, leftRotated);

    cout << endl << "Left rotated by " << k << " items: " << endl;
    for(int i = 0; i < n; i++)
        cout << setw(4) << leftRotated[i] << " ";

    
    system("pause");
    return 0;
}

void rotateRight(int arr[], int n, int k, int out[])
{
    k %= n;

    //length of out must be the same as n
    for(int i = 0; i < n; i++)
    {
        if(i < k)
        {
            out[i] = arr[n-k+i];

        } else {
            out[i] = arr[i-k];
        }
    }
}

void rotateLeft(int arr[], int n, int k, int out[])
{
    k %= n;

    //length of out must be the same as n
    for(int i = 0; i < n; i++)
    {
        if(i < k)
        {
            out[i] = arr[i+k];

        } else {
            out[i] = arr[i-n+k];
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