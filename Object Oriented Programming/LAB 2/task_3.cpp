#include <iostream>
using namespace std;

bool isSymbol(char c)
{
    return !isalnum(c) && !isspace(c);
}

void inputMatrix(char **mat, const int &rows, const int &cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << "Enter element at (" << i << ", " << j << "): ";
            cin >> mat[i][j];
        }
    }
}

void displayMatrix(char **mat, const int &rows, const int &cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

char **allocateMatrix(const int &rows, const int &cols)
{
    char **mat = new char *[rows];
    for (int i = 0; i < cols; i++)
        mat[i] = new char[cols];

    return mat;
}

char *seperateAlpha(char **mat, const int &m, const int &n, int &alphaCount)
{
    alphaCount = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isalpha(mat[i][j]))
                alphaCount++;
        }
    }

    char *alphaArr = new char[alphaCount];
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isalpha(mat[i][j]))
                alphaArr[c++] = mat[i][j];
        }
    }

    return alphaArr;
}

char *seperateDigits(char **mat, const int &m, const int &n, int &digitCount)
{
    digitCount = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isdigit(mat[i][j]))
                digitCount++;
        }
    }

    char *digitArr = new char[digitCount];
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isdigit(mat[i][j]))
                digitArr[c++] = mat[i][j];
        }
    }

    return digitArr;
}

char *seperateSymbols(char **mat, const int &m, const int &n, int &symbolCount)
{
    symbolCount = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isSymbol(mat[i][j]))
                symbolCount++;
        }
    }

    char *symbolsArr = new char[symbolCount];
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isSymbol(mat[i][j]))
                symbolsArr[c++] = mat[i][j];
        }
    }

    return symbolsArr;
}
int main()
{
    int m = 3, n = 3, alphaCount = 0, digitCount = 0, symbolCount = 0;
    char **mat = allocateMatrix(m, n);
    inputMatrix(mat, m, n);
    displayMatrix(mat, m, n);

    char *alphas = seperateAlpha(mat, m, n, alphaCount);
    char *digits = seperateDigits(mat, m, n, digitCount);
    char *symbols = seperateSymbols(mat, m, n, symbolCount);

    cout << "Alphabets: ";
    for (int i = 0; i < alphaCount; i++)
        cout << alphas[i] << " ";

    cout << endl
         << "Digits: ";
    for (int i = 0; i < digitCount; i++)
        cout << digits[i] << " ";

    cout << endl
         << "Symbols: ";
    for (int i = 0; i < symbolCount; i++)
        cout << symbols[i] << " ";

    return 0;
}