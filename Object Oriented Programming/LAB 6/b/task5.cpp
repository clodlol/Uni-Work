#include <iostream>
using namespace std;

class Student
{
    string m_name{};
    static string m_name_static;
    static int totalStudents;

public:
    Student(const string &name) : m_name{name}
    {
        m_name_static = name;
        totalStudents++;
    }
    Student(const Student &student)
    {
        m_name = student.m_name;
        totalStudents++;
    }

    static const string& getNameStatic() { return m_name_static; }
    const string &getName() const { return m_name; }
    void setName(const string &name) { m_name = name; }
    static int getTotalStudents() { return totalStudents; }
};

int Student::totalStudents = 0;
string Student::m_name_static{};

int main()
{
    Student s1{"Alex"}, s2{"Bob"};
    Student s3 = s1;
    const Student s4{"Charlie"};
    // s4.setName("Larry"); //Compiler error: Cannot change member of const object

    cout << "Value of const object static name member: " << Student::getNameStatic() << "\n"; //Prints the name of the last object created
    cout << "Total students created: " << Student::getTotalStudents() << "\n";
    return 0;
}