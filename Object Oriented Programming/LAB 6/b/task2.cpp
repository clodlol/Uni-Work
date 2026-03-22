#include <iostream>
using namespace std;

class Employee
{
    string name;
    static int count;

public:
    Employee(const string &s)
    {
        name = s;
        count++;
    }

    static int getCount()
    {
        return count;
    }
};

int Employee::count = 0;

int main()
{
    Employee e1("alex"), e2("bob"), e3("charlie");
    cout << Employee::getCount() << "\n";

    return 0;
}