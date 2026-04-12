#include <iostream>
#include <limits>
#include "math_utils.h"
using namespace std;

class VectorType
{
private:
    double *m_x{};
    double *m_y{};
    double *m_z{};

public:
    VectorType(double x = 0.00, double y = 0.00, double z = 0.00)
        : m_x{new double(x)}, m_y{new double(y)}, m_z{new double(z)} {}
    ~VectorType()
    {
        delete m_x;
        delete m_y;
        delete m_z;
    }
    VectorType(const VectorType &vec)
    {
        *this = vec;
    }

    double dotProduct(const VectorType &vec) const
    {
        return (*m_x * (*vec.m_x) + *m_y * (*vec.m_y) + *m_z * (*vec.m_z));
    }
    double length() const
    {
        return square_root(*m_x * (*m_x) + *m_y * (*m_y) + *m_z * (*m_z));
    }
    double angle(const VectorType &vec) const
    {
        double denom = length() * vec.length();
        if (equals(denom, 0))
        {
            cout << "Division by zero while calculating angles between null vectors. \n";
            return -1;
        }

        return arccos(
            dotProduct(vec) / (length() * vec.length())); // division by zero hogai agar ya phir domain se bahir hua to
    }

    VectorType &operator=(const VectorType &vec)
    {
        if (m_x)
            delete m_x;
        if (m_y)
            delete m_y;
        if (m_z)
            delete m_z;

        m_x = new double(*vec.m_x);
        m_y = new double(*vec.m_y);
        m_z = new double(*vec.m_z);

        return *this;
    }
    VectorType operator+(const VectorType &vec) const
    {
        return VectorType{*m_x + *vec.m_x, *m_y + *vec.m_y, *m_z + *vec.m_z};
    }
    VectorType operator-(const VectorType &vec) const
    {
        return VectorType{*m_x - *vec.m_x, *m_y - *vec.m_y, *m_z - *vec.m_z};
    }
    VectorType &operator++()
    {
        ++(*m_x), ++(*m_y), ++(*m_z);

        return *this;
    }
    VectorType &operator--()
    {
        --(*m_x), --(*m_y), --(*m_z);

        return *this;
    }
    VectorType operator++(int)
    {
        VectorType tempVec{*m_x, *m_y, *m_z};
        ++(*this);
        return tempVec;
    }
    VectorType operator--(int)
    {
        VectorType tempVec{*m_x, *m_y, *m_z};
        --(*this);
        return tempVec;
    }
    double operator*(const VectorType &vec) const
    {
        return dotProduct(vec);
    }
    bool operator==(const VectorType &vec2) const
    {
        return (equals(*m_x, *vec2.m_x) &&
                equals(*m_y, *vec2.m_y) &&
                equals(*m_z, *vec2.m_z));
    }
    bool operator!=(const VectorType &vec2) const { return !(*this == vec2); }

    friend ostream &operator<<(ostream &out, const VectorType &vec);
    friend istream &operator>>(istream &in, VectorType &vec);
    friend VectorType operator*(const VectorType &vec, double k);
    friend VectorType operator*(double k, const VectorType &vec);
};

ostream &operator<<(ostream &out, const VectorType &vec)
{
    return out << *vec.m_x << "i "
               << (*vec.m_y < 0 ? "- " : "+ ") << (*vec.m_y < 0 ? (-*vec.m_y) : *vec.m_y) << "j "
               << (*vec.m_z < 0 ? "- " : "+ ") << (*vec.m_z < 0 ? (-*vec.m_z) : *vec.m_z) << "k ";
}

istream &operator>>(istream &in, VectorType &vec)
{
    double x{}, y{}, z{};

    while (true)
    {
        in >> x >> y >> z;
        if (!in)
        {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores failing data
            continue;
        }
        in.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores extraneous data
        break;
    }

    *vec.m_x = x;
    *vec.m_y = y;
    *vec.m_z = z;
    return in;
}

VectorType operator*(const VectorType &vec, double k)
{
    return VectorType{*vec.m_x * k, *vec.m_y * k, *vec.m_z * k};
}
VectorType operator*(double k, const VectorType &vec)
{
    return vec * k;
}

int main()
{
    cout << "Enter driver program...\n";
    return 0;
}