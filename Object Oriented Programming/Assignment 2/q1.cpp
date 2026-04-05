#include <iostream>
#include <limits>
using namespace std;

const float PI = 3.14159265359;

bool equals(double a, double b, double epsilon = 1e-9);
double arccos(double x);
double square_root(double x);

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
    VectorType v1{5.2, 6.1, 7.0};
    VectorType v2{5.2, 6.1, 7.0};
    cout << (v1 == v2);
    return 0;
}

bool equals(double a, double b, double epsilon)
{
    return abs(a - b) < epsilon;
}

double square_root(double x)
{
    if (x < 0)
    {
        return NAN;
    }

    if (x == 0)
        return 0;

    double estimate = x / 2;
    for (int i = 0; i < 10; ++i)
    {
        estimate = 0.5 * (estimate + (x / estimate));
    }

    return estimate;
}

double arccos(double x)
{
    if (x > 1 || x < -1)
    {
        cout << "Invalid input to arccos function.\n";
        return 0.00;
    }

    // if x is close to 1, return sqrt(-2*(x-1))
    // if x is close to -1, return -sqrt(2*(x+1))+PI
    // if x is close to 0, return PI/2 - x
    // if x is close to 0.5, return PI/3-((x-0.5)/pow(0.75, 1/2))
    // if x is close to -0.5 return 4*PI/3-((x+0.5)/pow(0.75, 1/2))

    double taylor_denom = square_root(0.75);

    if (x > 0)
    {
        if (abs(x - 0) < abs(x - 0.5))
            return PI / 2 - x;
        else if (abs(x - 0.5) < abs(x - 1))
            return PI / 3 - ((x - 0.5) / taylor_denom);
        else
            return square_root(-2 * (x - 1));
    }
    else if (x < 0)
    {
        if (abs(x - 0) < abs(x + 0.5))
            return PI / 2 - x;
        else if (abs(x + 0.5) < abs(x + 1))
            return 2 * PI / 3 - ((x + 0.5) / taylor_denom);
        else
            return -square_root(2 * (x + 1)) + PI;
    }

    return PI / 2;
}