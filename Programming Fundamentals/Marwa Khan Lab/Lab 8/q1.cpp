#include <iostream>
using namespace std;

void copy(int in[], int sizeIn, int out[], int sizeOut)
{
    for (int i = 0; i < sizeOut; i++)
    {
        out[i] = in[i];
    }
}

int main()
{

    system("pause");
    return 0;
}