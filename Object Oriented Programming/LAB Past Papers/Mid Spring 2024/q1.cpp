#include <iostream>
using namespace std;

struct Weights
{
    int assignment{};
    int quiz{};
    int exam{};

public:
    Weights(int assignment = 0, int quiz = 0, int exam = 0) : assignment{assignment}, quiz{quiz}, exam{exam} {}
};

struct MaxMarks
{
    int assignment{};
    int quiz{};
    int exam{};

public:
    MaxMarks(int assignment = 0, int quiz = 0, int exam = 0) : assignment{assignment}, quiz{quiz}, exam{exam} {}
};

class Course
{
private:
    Weights weights{};
    MaxMarks maxMarks;
    string name;

public:
    Course(const Weights &weights, const MaxMarks &maxMarks, const string &name) : weights{weights}, maxMarks{maxMarks}, name{name} {}
};

class Student
{
};