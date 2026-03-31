#include <iostream>
#include <string>
using namespace std;

class Operation
{
    int m_a{};
    int m_b{};

public:
    Operation() {}
    Operation(int a, int b) : m_a{a}, m_b{b} {}

    int getA() const { return m_a; }
    void setA(const int &x) { m_a = x; }
    int getB() const { return m_a; }
    void setB(const int &x) { m_a = x; }

    void sum() { cout << "The sum of the two stored numbers is: " << (m_a + m_b) << "\n"; }
    void difference() { cout << "The difference of the two stored numbers is: " << (m_a - m_b) << "\n"; }
    void product() { cout << "The product of the two stored numbers is: " << (m_a * m_b) << "\n"; }
    void quotient() { cout << "The quotient of the two stored numbers is: " << (m_b == 0 ? "undefined" : to_string((float)m_a / m_b)) << "\n"; }
};

int main()
{
    Operation o1(1, 0);

    o1.sum();
    o1.difference();
    o1.product();
    o1.quotient();
    return 0;
}