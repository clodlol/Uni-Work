#include <iostream>
using namespace std;

template <class T>
class Pair
{
private:
    T values[2];

public:
    Pair(T first, T second)
    {
        values[0] = first;
        values[1] = second;
    }

    T getmax()
    {
        return (values[0] > values[1]) ? values[0] : values[1];
    }

    T getmin();
};

template <class T>
T Pair<T>::getmin()
{
    return (values[0] < values[1]) ? values[0] : values[1];
}

int main()
{
    Pair<double> myobject(1.012, 1.01234);
    cout << myobject.getmax();
    return 0;
}