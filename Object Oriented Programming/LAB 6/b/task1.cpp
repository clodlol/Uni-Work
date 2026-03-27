#include <iostream>
using namespace std;

class Student
{
    string m_name{};
    int *m_id{}; // we will assume id pointer has only one id

public:
    Student(const string &name, int id): m_name{name}
    {
        m_id = new int[1];
        m_id[0] = id;
    }
    ~Student()
    {
        delete[] m_id;
    }
    Student(const Student &obj)
    {
        m_name = obj.m_name;
        m_id = new int[1];
        m_id[0] = obj.m_id[0];
    }
    void display() const
    {
        cout << "Name: " << m_name << ", ID: " << m_id[0] << "\n";
    }
};

int main()
{
    Student s1("abdul rehman", 856);
    Student s2 = s1;

    cout << "S1: ";
    s1.display();

    cout << "S2: ";
    s2.display();

    return 0;
}