#include <iostream>
using namespace std;

class Employee
{
    string m_name{};
    static int m_count;

public:
    Employee(const string &name): m_name{name}
    {
        m_count++;
    }

    static int getCount() { return m_count; }
};

int Employee::m_count = 0;

int main()
{
    Employee e1{"alex"}, e2{"bob"}, e3{"charlie"};
    cout << "Number of objects created: " << Employee::getCount() << "\n";

    return 0;
}