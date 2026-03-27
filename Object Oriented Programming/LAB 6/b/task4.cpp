#include <iostream>
using namespace std;

class Person
{
    string m_name{};
    static string m_name_static;
public:
    Person(const string& name): m_name{name} { m_name_static = m_name; }

    static const string& getNameStatic() { return m_name_static; }
    const string& getName() const { return m_name; }
    void setName(const string& name) { m_name = name; }
};

string Person::m_name_static{};

int main()
{
    Person p1{"Alex"};
    const Person p2{"Bob"};

    //p2.setName("Charlie"); //Compiler error if we try to change member of const object
    p1.setName("Charlie"); //No compiler error

    cout << "Value of static name member: " << Person::getNameStatic() << "\n"; //Prints the name of the last created person object
    return 0;
}