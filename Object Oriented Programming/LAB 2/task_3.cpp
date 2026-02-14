#include <iostream>
using namespace std;

bool isSymbol(char c)
{
    return !isalnum(c) && !isspace(c);
}

void inputMatrix(char *const *const &mat, const int &rows, const int &cols)
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

void displayMatrix(const char *const *const &mat, const int &rows, const int &cols)
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
    {
        mat[i] = new char[cols + 1];
        mat[i][cols] = '\0';
    }

    return mat;
}

char *seperate(const char *const *const &mat, const int &m, const int &n, const int &mode)
{
    // mode: 0 = alphabets, 1 = numbers, 2 = symbols
    if (mode < 0 || mode > 2)
        return nullptr;

    int tokenCount = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mode == 0 && isalpha(mat[i][j]))
                tokenCount++;
            else if (mode == 1 && isdigit(mat[i][j]))
                tokenCount++;
            else if (mode == 2 && isSymbol(mat[i][j]))
                tokenCount++;
        }
    }

    char *tokenArr = new char[tokenCount + 1];
    tokenArr[tokenCount] = '\0';
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mode == 0 && isalpha(mat[i][j]))
                tokenArr[c++] = mat[i][j];
            else if (mode == 1 && isdigit(mat[i][j]))
                tokenArr[c++] = mat[i][j];
            else if (mode == 2 && isSymbol(mat[i][j]))
                tokenArr[c++] = mat[i][j];
        }
    }

    return tokenArr;
}

void freeMatrix(const char *const *const &mat, const int &m)
{
    for (int i = 0; i < m; i++)
        delete[] mat[i];
    delete[] mat;
}

int main()
{
    int m = 3, n = 3, alphaCount = 0, digitCount = 0, symbolCount = 0;
    char **mat = allocateMatrix(m, n);
    inputMatrix(mat, m, n);
    displayMatrix(mat, m, n);

    char *alphas = seperate(mat, m, n, 0);
    char *digits = seperate(mat, m, n, 1);
    char *symbols = seperate(mat, m, n, 2);

    freeMatrix(mat, m);
    mat = nullptr;

    cout << "Alphabets: ";
    cout << alphas << endl;

    cout << endl
         << "Digits: ";
    cout << digits << endl;

    cout << endl
         << "Symbols: ";
    cout << symbols << endl;

    return 0;
}