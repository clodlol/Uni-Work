#include <iostream>

class Date
{
    int Day, Month, Year;

public:
    Date(int d = 1, int m = 1, int y = 1960) : Day{d}, Month{m}, Year{y} {}
    void Print() { std::cout << Day << "-" << Month << "-" << Year; }

    int &operator[](int idx)
    {
        if (idx == 0)
            return Day;
        else if (idx == 1)
            return Month;
        else if (idx == 2)
            return Year;
        else
            throw std::runtime_error("Invalid index provided.");
    }
};

class Employee
{
    std::string Name;
    Date DOB;
    Date JoiningDate;

public:
    Employee(std::string name = "", int d1 = 1, int m1 = 1, int y1 = 1960, int d2 = 1, int m2 = 1, int y2 = 1960) : Name{name}, DOB{d1, m1, y1}, JoiningDate{d2, m2, y2} {}
    void Print()
    {
        std::cout << "Name: " << Name << "\n";
        std::cout << "DOB: ";
        DOB.Print();
        std::cout << "\n";
        std::cout << "Joining Date: ";
        JoiningDate.Print();
        std::cout << "\n";
    }

    Date &operator[](std::string fieldName)
    {
        if (fieldName == "DOB")
            return DOB;
        else if (fieldName == "JoiningDate")
            return JoiningDate;
        else
            throw std::runtime_error("Invalid field name provided.");
    }
};

class Person
{
    std::string Name;
    Date *DOB;

public:
    Person(std::string name) : Name{name}, DOB{nullptr} {}
    Person(const Person &other)
    {
        *this = other;
    }
    ~Person()
    {
        if (DOB)
            delete DOB;
    }

    Person &operator=(const Person &obj)
    {
        if (&obj == this)
            return *this;

        if (DOB)
            delete DOB;

        if (obj.DOB)
        {
            DOB = new Date(*obj.DOB);
        }
        else
        {
            DOB = nullptr;
        }
        Name = obj.Name;

        return *this;
    }

    void Print()
    {
        std::cout << "Name: " << Name << "\n";
        if (DOB)
        {
            std::cout << "DOB: ";
            DOB->Print();
            std::cout << "\n";
        }
    }

    void setDOB(Date *dateptr)
    {
        if (DOB)
            delete DOB;

        if (!dateptr)
        {
            DOB = nullptr;
            return;
        }

        DOB = new Date(*dateptr);
    }
};

int main()
{
    Date dob(18, 5, 2005);
    Person p1{"Dummy employee"};
    p1.setDOB(&dob);

    p1.Print();

    return 0;
}