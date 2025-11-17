#include <iostream>
using namespace std;

double transform(double x);
double transform(double base, int power);
double transform(double values[], int size);

int main()
{
    cout << transform(2.0, -3) << endl;

    system("pause");
    return 0;
}

double transform(double x)
{
    return (3*x*x)-(5*x)+12;
}

double transform(double base, int power)
{
    double ans = 1;
    if(power == 0) return 1;
    
    for(int i = 1; i <= (power < 0 ? -power : power); i++)
    {
        ans *= base;
    }

    return (power < 0 ? (1/ans) : ans);
}

double transform(double values[], int size)
{
    if(size <= 0) {
        cout << "Array size invalid." << endl;
        return 0;
    }

    double sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += values[i];
    }

    return sum/size;
}