#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX_INPUT_SIZE = 5;

void outputSum(int matrixA[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsA, int colsA, int matrixB[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsB, int colsB);
void outputProduct(int matrixA[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsA, int colsA, int matrixB[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsB, int colsB);
void outputTranspose(int matrixA[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsA, int colsA);

bool getInt(int &input, int rangeStart, int rangeEnd);

int main()
{
    int matrixA[MAX_INPUT_SIZE][MAX_INPUT_SIZE] = {0};
    int matrixB[MAX_INPUT_SIZE][MAX_INPUT_SIZE] = {0};
    int l = 0, m = 0, n = 0, o = 0; // matrixA: lxm, matrixB: nxo

    while (true)
    {
        cout << "Enter the number of rows of matrix A: ";
        if (!getInt(l, 1, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the number of columns of matrix A: ";
        if (!getInt(m, 1, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the number of rows of matrix B: ";
        if (!getInt(n, 1, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter the number of columns of matrix B: ";
        if (!getInt(o, 1, MAX_INPUT_SIZE))
            continue;
        else
            break;
    }

    cout << endl
         << "Matrix A: " << l << "x" << m << endl;
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m;)
        {
            if (!getInt(matrixA[i][j], INT_MIN, INT_MAX))
                continue;
            else
                j++;
        }
    }

    cout << endl
         << "Matrix B: " << n << "x" << o << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < o;)
        {
            if (!getInt(matrixB[i][j], INT_MIN, INT_MAX))
                continue;
            else
                j++;
        }
    }

    cout << endl
         << "Addition: " << endl;
    outputSum(matrixA, l, m, matrixB, n, o);

    cout << endl
         << "Multiplication: " << endl;
    outputProduct(matrixA, l, m, matrixB, n, o);

    cout << endl
         << "Transpose of first matrix: " << endl;
    outputTranspose(matrixA, l, m);

    cout << endl
         << "Transpose of second matrix: " << endl;
    outputTranspose(matrixB, n, o);

    system("pause");
    return 0;
}

void outputTranspose(int matrixA[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsA, int colsA)
{
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            cout << setw(4) << matrixA[j][i] << " ";
        }
        cout << endl;
    }
}

void outputProduct(int matrixA[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsA, int colsA, int matrixB[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsB, int colsB)
{
    if (colsA != rowsB)
    {
        cout << "The no. of columns of first matrix must be equal to the no. of rows of second matrix for multiplication." << endl;
        return;
    }

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            int exp = 0;
            for (int k = 0; k < colsA; k++)
            {
                exp += (matrixA[i][k] * matrixB[k][j]);
            }
            cout << setw(4) << exp << " ";
        }
        cout << endl;
    }
}

void outputSum(int matrixA[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsA, int colsA, int matrixB[MAX_INPUT_SIZE][MAX_INPUT_SIZE], int rowsB, int colsB)
{
    if ((rowsA != rowsB) || (colsA != colsB))
    {
        cout << "Both matrices must have the same order to be eligible for addition." << endl;
        return;
    }

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            cout << setw(4) << (matrixA[i][j] + matrixB[i][j]) << " ";
        }
        cout << endl;
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