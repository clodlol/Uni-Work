#include <iostream>
using namespace std;

class Person
{
    string m_name{};
public:
    Person(const string& name): m_name{name} {}

    const string& getName() const { return m_name; }
};

int main()
{
    Person p1{"Alex"};
    const Person p2{"Bob"};

    //Person::getName()
}