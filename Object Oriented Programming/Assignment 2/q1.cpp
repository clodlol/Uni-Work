#include <iostream>
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
        return sqrt(*m_x * (*m_x) + *m_y * (*m_y) + *m_z * (*m_z));
    }
    double angle(const VectorType &vec) const
    {
        return acos(
            dotProduct(vec) / (length() * vec.length())); // division by zero hogai agar
    }

    VectorType &operator=(const VectorType &vec)
    {
        delete m_x;
        delete m_y;
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

    friend bool operator==(const VectorType &vec1, const VectorType &vec2);
    friend bool operator!=(const VectorType &vec1, const VectorType &vec2);
    friend ostream &operator<<(ostream &out, const VectorType &vec);
    friend istream &operator>>(istream &in, VectorType &vec);
    friend VectorType operator*(const VectorType &vec, double k);
};

bool operator==(const VectorType &vec1, const VectorType &vec2)
{
    return (*vec1.m_x == *vec2.m_x && *vec1.m_y == *vec2.m_y && *vec1.m_z == *vec2.m_z);
}

bool operator!=(const VectorType &vec1, const VectorType &vec2) { return !(vec1 == vec2); }

ostream &operator<<(ostream &out, const VectorType &vec)
{
    return out << *vec.m_x << "i "
               << (*vec.m_y < 0 ? "- " : "+ ") << (*vec.m_y < 0 ? (-*vec.m_y) : *vec.m_y) << "j "
               << (*vec.m_z < 0 ? "- " : "+ ") << (*vec.m_z < 0 ? (-*vec.m_z) : *vec.m_z) << "k ";
}

istream &operator>>(istream &in, VectorType &vec)
{
    return in >> *vec.m_x >> *vec.m_y >> *vec.m_z; // TODO: implement input validation
}

VectorType operator*(const VectorType &vec, double k)
{
    return VectorType{*vec.m_x * k, *vec.m_y * k, *vec.m_z * k};
}

int main()
{
    VectorType v1{}, v3{-99.99, -88.88, -77.77};
    VectorType v2 = v1 = v3;
    v2 = VectorType{v1} + v3;
    cout << v1 << "\n"
         << v2 << "\n"
         << v3;
    return 0;
}