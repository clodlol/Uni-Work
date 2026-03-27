#include <iostream>
using namespace std;

class Student
{
    int* m_marks{};
    int m_subjects{};
public:
    Student(int subjects): m_subjects{subjects} , m_marks{ new int[subjects] } {}
    ~Student() { delete[] m_marks; }

    void inputMarks()
    {
        for(int i = 0; i < m_subjects; ++i)
            cin >> m_marks[i];
    }

    void printMarks() const
    {
        for(int i = 0; i < m_subjects; ++i)
            cout << m_marks[i] << " ";
        cout << "\n";
    }
};

int main()
{
    int subjects{5};
    Student s1{subjects};
    s1.inputMarks();
    s1.printMarks();

    return 0;
}