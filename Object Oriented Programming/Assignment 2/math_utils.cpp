#include <cmath>
#include "math_utils.h"

const float PI = 3.14159265359;

bool equals(double a, double b, double epsilon)
{
    return abs(a - b) < epsilon;
}

double square_root(double x)
{
    if (x < 0)
    {
        return NAN;
    }

    if (x == 0)
        return 0;

    double estimate = x / 2;
    for (int i = 0; i < 10; ++i)
    {
        estimate = 0.5 * (estimate + (x / estimate));
    }

    return estimate;
}

double arccos(double x)
{
    if (x > 1 || x < -1)
    {
        return NAN;
    }

    // if x is close to 1, return sqrt(-2*(x-1))
    // if x is close to -1, return -sqrt(2*(x+1))+PI
    // if x is close to 0, return PI/2 - x
    // if x is close to 0.5, return PI/3-((x-0.5)/pow(0.75, 1/2))
    // if x is close to -0.5 return 4*PI/3-((x+0.5)/pow(0.75, 1/2))

    double taylor_denom = square_root(0.75);

    if (x > 0)
    {
        if (abs(x - 0) < abs(x - 0.5))
            return PI / 2 - x;
        else if (abs(x - 0.5) < abs(x - 1))
            return PI / 3 - ((x - 0.5) / taylor_denom);
        else
            return square_root(-2 * (x - 1));
    }
    else if (x < 0)
    {
        if (abs(x - 0) < abs(x + 0.5))
            return PI / 2 - x;
        else if (abs(x + 0.5) < abs(x + 1))
            return 2 * PI / 3 - ((x + 0.5) / taylor_denom);
        else
            return -square_root(2 * (x + 1)) + PI;
    }

    return PI / 2;
}

int countDigits(int x)
{
    if (x < 0)
        x = -x;

    int c = 0;
    for (int i = x; i != 0; i /= 10)
    {
        c++;
    }

    return c;
}

double posFractionalPart(double n)
{
    if (n < 0)
        n = -n;
    return (n - (int)n);
}

bool startsWithK(int n, int k)
{
    if (n < 0)
        return false;

    int i = n;
    while (i != 0)
    {
        if (i / 10 == 0 && i % 10 == k)
        {
            return true;
        }
        i /= 10;
    }

    return false;
}