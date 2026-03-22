#include <iostream>
using namespace std;

class Student
{
    string m_name{};
    static int totalStudents;
public:
    Student(const string& name): m_name{name} { totalStudents++; }
    Student(const Student& student)
    {
        m_name = student.m_name;
        totalStudents++;
    }

    const string& getName() const { return m_name; }
    static int getTotalStudents() { return totalStudents; }
};

int Student::totalStudents = 0;

int main()
{
    Student s1{"Alice"};
    const Student s2{"Bob"};
    Student s3 = s1;
    //s2.m_name{"Something"}; Error: inaccessible data member
    //how do we use scope resolution to access non-static members?
    cout << "Total students created: " << Student::getTotalStudents() << "\n";

    return 0;
}