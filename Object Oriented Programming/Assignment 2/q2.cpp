#include <iostream>
using namespace std;

int countDigits(int x)
{
    int c = 0;
    for (int i = x; i != 0; i /= 10)
    {
        c++;
    }

    return c;
}

char *intToString(int x)
{
    const int digits = countDigits(x), size = (x < 0 ? digits + 1 : digits);
    char *temp = new char[size + 1];

    for (int i = size - 1, a = x; a != 0 && i >= 0; --i, a /= 10)
    {
        temp[i] = '0' + abs(a % 10);
    }

    if (x < 0)
        temp[0] = '-';

    temp[size] = '\0';

    cout << temp << "\n";

    return temp;
}

char *doubleToString(double x)
{
    int integralDigits = countDigits(x);

    return nullptr;
}

class String
{
private:
    char *m_str{};
    int m_len{};

public:
    String(char *str)
    {
        m_len = strlen(str);
        m_str = new char[m_len + 1];
        strcpy(m_str, str);
    }
    ~String() { delete[] m_str; }
    String(const String &obj)
    {
        *this = obj;
    }

    int length() const
    {
        return m_len;
    }

    String &upper()
    {
        for (int i = 0; i < m_len; ++i)
        {
            if (m_str[i] >= 'a' && m_str[i] <= 'z')
                m_str[i] += ('a' - 'A');
        }

        return *this;
    }

    String &lower()
    {
        for (int i = 0; i < m_len; ++i)
        {
            if (m_str[i] >= 'A' && m_str[i] <= 'Z')
                m_str[i] -= ('a' - 'A');
        }

        return *this;
    }

    char at(int index)
    {
        if (m_len == 0)
            return '\0';
        index %= m_len;

        if (index < 0)
            index = m_len + index;

        return m_str[index];
    }

    int findIndex(char *substr) // multiple occurrences?
    {
        int subLen = strlen(substr);
        for (int i = 0; i < m_len - subLen; ++i)
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

    int compare(const String &obj)
    {
        return strcmp(m_str, obj.m_str);
    }

    String &concat(const char *substr)
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
    String &concat(const string &s) { return concat(s.c_str()); }
    String &concat(int x)
    {
        const char *substr = intToString(x);
        concat(substr);

        delete[] substr;

        return *this;
    }
    String &concat(double x)
    {
        const char *substr = doubleToString(x);
        concat(substr);

        delete[] substr;

        return *this;
    }

    String &operator=(const String &obj)
    {
        delete[] m_str;

        m_len = obj.m_len;
        m_str = new char[m_len + 1];
        strcpy(m_str, obj.m_str);
    }

    friend ostream &operator<<(ostream &out, const String &obj);
};

ostream &operator<<(ostream &out, const String &obj)
{
    return out << obj.m_str;
}

int main()
{
    String s1{"abdulrehmanrehmanabdul"};
    cout << s1.findIndex("rehman");
    return 0;
}