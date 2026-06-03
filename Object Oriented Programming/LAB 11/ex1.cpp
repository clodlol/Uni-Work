#include <iostream>
using namespace std;

template <typename T1, typename T2>
T1 GetMax(T1 a, T2 b)
{
    return (a > b) ? a : b;
}

template <typename T1, typename T2>
T1 GetMin(T1 a, T2 b)
{
    return (a < b) ? a : b;
}

int main()
{
    char i = 'z';
    int j = 6, k;
    long l = 10, m = 5, n;
    k = GetMax<int, long>(i, m);
    n = GetMin<int, char>(j, l);
    cout << k << endl;
    cout << n << endl;
    return 0;
}