#include <iostream>

using namespace std;

int main()
{
    const int l = 2, m = 3, n = 3, o = 2;

    const int constOrd = 3;

    int matrixA[l][m] = {{1, 2, 3}, {4, 5, 6}};
    int matrixB[n][o] = {{7, 8}, {9, 10}, {11, 12}};
    int resultant[l][o] = {0};

    if(m != n)
    {
        cout << "Matrices not eligible for multiplication!" << endl;
        return -1; 
    }

    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < o; j++)
        {
            int counter = 1;
            
            while(counter <= constOrd)
            {
                resultant[i][j] += (matrixA[i][counter-1] * matrixB[counter-1][j]);
                counter++;
            }
        }
    }

    cout << endl;

    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < o; j++)
        {
            cout << resultant[i][j] << " ";
        }
        cout << endl;
    }

    system("pause");
    return 0;
}