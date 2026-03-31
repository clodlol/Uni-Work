#include <iostream>
using namespace std;

int getMagnitude(const int &real, const int &im)
{
    return sqrt(real * real + im * im);
}

class ComplexNumber
{
    int m_real;
    int m_imaginary;
    static int count;

public:
    static int countDisplay;

    ComplexNumber(const int &real, const int &imaginary) : m_real{real}, m_imaginary{imaginary} { count++; }
    ~ComplexNumber() {}

    void input()
    {
        cin >> m_real >> m_imaginary;
    }
    void output()
    {
        cout << m_real << " + " << m_imaginary << "i";
    }

    bool isEqual(const ComplexNumber &z)
    {
        return (m_real == z.m_real && m_imaginary == z.m_imaginary);
    }
    bool operator!=(const ComplexNumber &z)
    {
        return (m_real != z.m_real || m_imaginary != z.m_imaginary);
    }
    bool operator>=(const ComplexNumber &z)
    {
        return (getMagnitude(m_real, m_imaginary) >= getMagnitude(z.m_real, z.m_imaginary));
    }
    bool operator<=(const ComplexNumber &z)
    {
        return (getMagnitude(m_real, m_imaginary) <= getMagnitude(z.m_real, z.m_imaginary));
    }

    ComplexNumber conjugate()
    {
        return ComplexNumber{m_real, -m_imaginary};
    }
    ComplexNumber operator+(const ComplexNumber &z)
    {
        return ComplexNumber{m_real + z.m_real, m_imaginary + z.m_imaginary};
    }
    ComplexNumber operator-(const ComplexNumber &z)
    {
        return ComplexNumber{m_real - z.m_real, m_imaginary - z.m_imaginary};
    }
    ComplexNumber operator*(const ComplexNumber &z)
    {
        return ComplexNumber{m_real * z.m_imaginary - m_imaginary * z.m_real, m_real * z.m_imaginary + m_imaginary * z.m_real};
    }
    ComplexNumber &operator++()
    {
        m_real++;
        return *this;
    }
    ComplexNumber &operator--()
    {
        m_real--;
        return *this;
    }
    ComplexNumber operator++(int)
    {
        ComplexNumber temp = *this;
        m_real++;
        return temp;
    }
    ComplexNumber operator--(int)
    {
        ComplexNumber temp = *this;
        m_real--;
        return temp;
    }
};

int ComplexNumber::count = 0;
int ComplexNumber::countDisplay = 0;

int main()
{
    ComplexNumber z1{1, 1}, z2{0, 0};
    z1.conjugate().output();
    return 0;
}