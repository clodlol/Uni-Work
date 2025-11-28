#include <iostream>
#include <limits>
using namespace std;

bool getInt(int &input, int rangeStart, int rangeEnd);

const int MAX_MATRIX_SIZE = 100;

int main()
{
    int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = {0};
    int m = 0, n = 0;

    while (true)
    {
        cout << "Enter matrix rows: ";
        if (!getInt(m, 0, MAX_MATRIX_SIZE))
            continue;
        else
            break;
    }

    while (true)
    {
        cout << "Enter matrix columns: ";
        if (!getInt(n, 0, MAX_MATRIX_SIZE))
            continue;
        else
            break;
    }

    cout << "Enter the elements: ";
    for (int i = 0; i < m * n;)
    {
        if (!getInt(matrix[i / n][i % n], INT_MIN, INT_MAX))
            continue;
        else
            i++;
    }

    int right = 1, bottom = 1, largestSubMatrixArea = INT_MIN;
    for (int i = bottom; i < m; i++)
    {
        for (int j = right; j < n; j++)
        {
            int subMatrixOdds = 0, subMatrixEvens = 0, subMatrixArea = 0;
            for (int k = 0; k <= i; k++)
            {
                for (int l = 0; l <= j; l++)
                {
                    if (matrix[k][l] % 2 == 0)
                    {
                        subMatrixEvens++;
                    }
                    else
                    {
                        subMatrixOdds++;
                    }
                }
            }

            if (subMatrixEvens == subMatrixOdds)
            {
                subMatrixArea = (i) * (j);
                if (subMatrixArea > largestSubMatrixArea)
                    largestSubMatrixArea = subMatrixArea;
            }
        }
    }

    cout << "Largest balanced submatrix has area: " << largestSubMatrixArea << endl;
    cout << endl;
    system("pause");
    return 0;
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