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
    float radius{7.86};
    Circle c1{radius};
    cout << "Area of a circle with radius " << radius << ": " << c1.getArea() << "\n";
    return 0;
}