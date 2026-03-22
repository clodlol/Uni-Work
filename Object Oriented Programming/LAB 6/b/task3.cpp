#include <iostream>
using namespace std;

class Circle
{
    const float PI = 3.14;
    float m_radius{};
public:
    Circle(float radius) : m_radius{radius} {}

    float getArea() const { return PI*m_radius*m_radius; }
};

int main()
{
    Circle c1{7.86};
    cout << c1.getArea() << "\n";
    return 0;
}