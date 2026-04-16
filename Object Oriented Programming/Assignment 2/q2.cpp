#include <iostream>
#include "string_utils.h"
#include "math_utils.h"
using namespace std;

const int MAX_INPUT_SIZE = 100;

char *intToCString(int x);                      // caller must delete[]
char *doubleToCString(double x, int precision); // caller must delete[], known limitation: truncates if all of the fractional part is 0

class String
{
private:
    char *m_str{};
    int m_len{};

public:
    String(char *str = "")
    {
        if (!str)
        {
            str = "";
        }
        m_len = calculateLen(str);
        m_str = new char[m_len + 1];
        copyString(m_str, m_len + 1, str);
    }
    ~String() { delete[] m_str; }
    String(const String &obj) { *this = obj; }
    String(String &&obj) : m_str{obj.m_str}, m_len{obj.m_len}
    {
        obj.m_str = nullptr;
        obj.m_len = 0;
    }

    int length() const { return m_len; }

    String &upper()
    {
        for (int i = 0; i < m_len; ++i)
        {
            if (m_str[i] >= 'a' && m_str[i] <= 'z')
                m_str[i] -= ('a' - 'A');
        }

        return *this;
    }

    String &lower()
    {
        for (int i = 0; i < m_len; ++i)
        {
            if (m_str[i] >= 'A' && m_str[i] <= 'Z')
                m_str[i] += ('a' - 'A');
        }

        return *this;
    }

    char at(int i) const
    {
        if (i < 0 || i >= m_len)
        {
            cout << "Bounds error while accessing string element.\n";
            return 0;
        }

        return m_str[i];
    }

    int findIndex(char *substr) const
    {
        int subLen = calculateLen(substr);
        for (int i = 0; i <= m_len - subLen; ++i)
        {
            bool found = true;
            for (int j = i; j < i + subLen; ++j)
            {
                if (m_str[j] != substr[j - i])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                return i;
            }
        }

        return -1;
    }

    int compare(const String &obj) const
    {
        int range = min(m_len, calculateLen(obj.m_str));
        for (int i = 0; i < range; ++i)
        {
            if (m_str[i] > obj.m_str[i])
                return 1;
            else if (m_str[i] < obj.m_str[i])
                return -1;
        }

        return 0;
    }

    String substring(int start, int end) const
    {
        if ((start < 0 || start >= m_len) || (end < 0 || end >= m_len))
        {
            cout << "Out of bounds error while calculating substring!\n";
            return String{};
        }

        if (start > end)
        {
            cout << "Starting index can't be greater than ending index!\n";
            return String{};
        }

        char *resStr = new char[(end - start + 1) + 1];
        int resCounter = 0;
        // indices end and start are inclusive, extra 1 for null terminator
        for (int i = start; i <= end; ++i)
        {
            resStr[resCounter++] = m_str[i];
        }

        resStr[resCounter] = '\0';

        String res{resStr};

        delete[] resStr;
        return res;
    }

    String &append(const char *substr)
    {
        int subLen = strlen(substr);
        char *temp = m_str;
        int tempLen = m_len;

        m_len += subLen;
        m_str = new char[m_len + 1];

        for (int i = 0; i < tempLen; ++i)
            m_str[i] = temp[i];
        for (int i = tempLen; i < m_len; ++i)
        {
            m_str[i] = substr[i - tempLen];
        }
        m_str[m_len] = '\0';

        delete[] temp;

        return *this;
    }
    String &append(const string &s) { return append(s.c_str()); }
    String &append(int x)
    {
        const char *substr = intToCString(x);
        append(substr);

        delete[] substr;

        return *this;
    }
    String &append(double x)
    {
        const char *substr = doubleToCString(x, 10);
        append(substr);

        delete[] substr;

        return *this;
    }

    String &prepend(const char *substr)
    {
        int subLen = strlen(substr);
        char *temp = m_str;
        int tempLen = m_len;

        m_len += subLen;
        m_str = new char[m_len + 1];

        for (int i = 0; i < subLen; ++i)
        {
            m_str[i] = substr[i];
        }
        for (int i = subLen; i < m_len; ++i)
        {
            m_str[i] = temp[i - subLen];
        }
        m_str[m_len] = '\0';

        delete[] temp;

        return *this;
    }
    String &prepend(const string &s) { return prepend(s.c_str()); }
    String &prepend(int x)
    {
        const char *substr = intToCString(x);
        prepend(substr);

        delete[] substr;

        return *this;
    }
    String &prepend(double x)
    {
        const char *substr = doubleToCString(x, 10);
        prepend(substr);

        delete[] substr;

        return *this;
    }

    String &operator=(const String &obj)
    {
        if (this == &obj)
        {
            return *this;
        }

        if (m_str)
            delete[] m_str;

        m_len = obj.m_len;
        m_str = new char[m_len + 1];
        strcpy(m_str, obj.m_str);

        return *this;
    }

    char operator[](int i) { return at(i); }

    bool operator>(const String &obj) const { return compare(obj) > 0; }
    bool operator<(const String &obj) const { return compare(obj) < 0; }
    bool operator==(const String &obj) const { return compare(obj) == 0; }
    bool operator!=(const String &obj) const { return compare(obj) != 0; }

    String operator+(const String &obj) const { return (String{m_str}.append(obj.m_str)); }
    String operator+(const char *substr) const { return (String{m_str}.append(substr)); }
    String operator+(const string &s) const { return (String{m_str}.append(s)); }
    String operator+(int i) const { return (String{m_str}.append(i)); }
    String operator+(double d) const { return (String{m_str}.append(d)); }

    friend String operator+(const char *substr, const String &obj) { return (String{obj.m_str}.prepend(substr)); }
    friend String operator+(const string &s, const String &obj) { return (String{obj.m_str}.prepend(s)); }
    friend String operator+(int i, const String &obj) { return (String{obj.m_str}.prepend(i)); }
    friend String operator+(double d, const String &obj) { return (String{obj.m_str}.prepend(d)); }

    String &operator+=(const String &obj) { return append(obj.m_str); }
    String &operator+=(const char *substr) { return append(substr); }
    String &operator+=(const string &s) { return append(s); }
    String &operator+=(int i) { return append(i); }
    String &operator+=(double d) { return append(d); }

    friend ostream &operator<<(ostream &out, const String &obj);
    friend istream &operator>>(istream &in, String &obj);
};

ostream &operator<<(ostream &out, const String &obj)
{
    return out << obj.m_str;
}

istream &operator>>(istream &in, String &obj)
{
    string s;

    while (true)
    {
        in >> s;
        if (!in)
        {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores failing data
            continue;
        }
        in.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores extraneous data
        break;
    }

    String temp{(char *)s.c_str()};
    obj = temp;

    return in;
}

int main()
{
    String s1{"12"};
    String s2 = s1;
    String s3 = s2 + 3.99;
    cout << s3 << "\n";

    system("pause");
    return 0;
}

char *intToCString(int x) // caller must delete[]
{
    bool neg = x < 0;
    if (neg)
        x = -x;

    const int digits = countDigits(x), size = (neg ? digits + 1 : digits);
    char *temp = new char[size + 1];

    for (int i = size - 1, a = x; a != 0 && i >= 0; --i, a /= 10)
    {
        temp[i] = '0' + (a % 10);
    }

    if (neg)
        temp[0] = '-';

    temp[size] = '\0';

    return temp;
}

char *doubleToCString(double x, int precision) // caller must delete[], known limitation: truncates if all of the fractional part is 0
{
    if (equals(x, 0.00))
    {
        char *res = new char[2];
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    int fractionalDigits = 0, integralDigits = countDigits(x);

    for (double i = posFractionalPart(x) * 10; !equals(i, 0.00) && fractionalDigits < precision; i *= 10, ++fractionalDigits)
    {
        i = posFractionalPart(i);
    }

    char *res = new char[(fractionalDigits + integralDigits + 1) + (fractionalDigits > 0 ? 1 : 0) + (x < 0 ? 1 : 0)];
    // integral digits+fractional digits+null terminator+point+minus sign(if negative)
    int resCounter = 0;

    char *integralPart = intToCString(x);

    for (int i = 0; i < integralDigits + (x < 0 ? 1 : 0); ++i)
    {
        res[resCounter++] = integralPart[i];
    }

    if (fractionalDigits > 0)
    {
        res[resCounter++] = '.';
    }

    for (double i = posFractionalPart(x) * 10, c = 0; c < fractionalDigits; i *= 10, ++c)
    {
        res[resCounter++] = '0' + (int)i;
        i = posFractionalPart(i);
    }

    res[resCounter] = '\0';

    delete[] integralPart;
    return res;
}