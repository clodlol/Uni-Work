#include <iostream>
using namespace std;

class Student
{
    string name;
    int *id; // we will assume id pointer has only one id

public:
    Student(const string &name, const int *const &id)
    {
        this->name = name;
        this->id = new int[1];
        this->id[0] = id[0];
    }
    ~Student()
    {
        delete[] id;
    }
    Student(const Student &obj)
    {
        this->name = obj.name;
        this->id = new int[1];
        this->id[0] = obj.id[0];
    }
    void display() const
    {
        cout << "Name: " << this->name << ", ID: " << this->id[0] << "\n";
    }
};

int main()
{
    int *id1 = new int[1], *id2 = new int[1];
    id1[0] = 856, id2[0] = 906;

    Student s1("abdul rehman", id1);
    Student s2 = s1;

    cout << "S1: ";
    s1.display();

    cout << "S2: ";
    s2.display();

    delete[] id1;
    delete[] id2;

    return 0;
}