#include <iostream>
using namespace std;

template <class T>
class Container
{
private:
    T data;

public:
    Container(T val);
    T increase();
};

template <class T>
Container<T>::Container(T val) : data(val) {}

template <class T>
T Container<T>::increase()
{
    return ++data;
}

template <>
class Container<char>
{
private:
    char data;

public:
    Container(char val);
    char uppercase();
};

Container<char>::Container(char val) : data(val) {}

char Container<char>::uppercase()
{
    if (data >= 'a' && data <= 'z')
    {
        return data - 32;
    }
    return data;
}

int main()
{
    Container<int> myint(7);
    Container<char> mychar('j');
    cout << myint.increase() << endl;
    cout << mychar.uppercase() << endl;
    return 0;
}