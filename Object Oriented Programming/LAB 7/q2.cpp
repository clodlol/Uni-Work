#include <iostream>
using namespace std;

class Quadratic
{
    int m_a;
    int m_b;
    int m_c;

public:
    Quadratic() {}
    Quadratic(const int &a, const int &b, const int &c) : m_a{a}, m_b{b}, m_c{c} {}
    Quadratic(const Quadratic &obj)
    {
        m_a = obj.m_a;
        m_b = obj.m_b;
        m_c = obj.m_c;
    }

    Quadratic operator+(const Quadratic &obj)
    {
        return Quadratic(m_a + obj.m_a, m_b + obj.m_b, m_c + obj.m_c);
    }
    //friend Quadratic operator+(const Quadratic &obj1, const Quadratic& obj2);
    Quadratic operator-(const Quadratic &obj)
    {
        return Quadratic(m_a - obj.m_a, m_b - obj.m_b, m_c - obj.m_c);
    }
    //friend Quadratic operator-(const Quadratic &obj1, const Quadratic& obj2);
    Quadratic operator*(const int &k)
    {
        return Quadratic(m_a * k, m_b * k, m_c * k);
    }
    bool operator==(const Quadratic &obj)
    {
        return (m_a == obj.m_a && m_b == obj.m_b && m_c == obj.m_c);
    }
    bool operator!=(const Quadratic &obj)
    {
        return (m_a != obj.m_a || m_b != obj.m_b || m_c != obj.m_c);
    }
    Quadratic &operator=(const Quadratic &obj)
    {
        m_a = obj.m_a;
        m_b = obj.m_b;
        m_c = obj.m_c;

        return *this;
    }
    friend istream &operator>>(istream &in, Quadratic &obj);
    friend ostream &operator<<(ostream &out, const Quadratic &obj);
};

// Quadratic operator+(const Quadratic &obj1, const Quadratic& obj2)
// {
//     return Quadratic(obj1.m_a + obj2.m_a, obj1.m_b + obj2.m_b, obj1.m_c + obj2.m_c);
// }

// Quadratic operator-(const Quadratic &obj1, const Quadratic& obj2)
// {
//     return Quadratic(obj1.m_a - obj2.m_a, obj1.m_b - obj2.m_b, obj1.m_c - obj2.m_c);
// }

istream &operator>>(istream &in, Quadratic &obj)
{
    in >> obj.m_a >> obj.m_b >> obj.m_c;
    return in;
}
ostream &operator<<(ostream &out, const Quadratic &obj)
{
    out << obj.m_a << "x^2 + " << obj.m_b << "x + " << obj.m_c;
    return out;
}

int main()
{
    Quadratic q1(2, 3, 4), q2, q3(6, 7, 8);
    q2 = q1 = q3;

    cout << q3 << "\n" << q2 << "\n" << q1;

    return 0;
}