#include <iostream>
using namespace std;

int calculateLen(char *arr)
{
    int c = 0;
    while (arr[c] != '\0')
        c++;

    return c;
}

void copyString(char *destination, int destAllocSize, char *source)
// we have to know the amount of allocated memory here, else the program throws
{
    if (destAllocSize <= 0)
    {
        cout << "Not enough allocated memory to copy string. \n"; // return an error here?
        return;
    }

    int sourceLen = calculateLen(source);
    destination[destAllocSize - 1] = '\0';
    for (int i = 0; i < destAllocSize - 1; ++i)
        destination[i] = source[i];
}

int countDigits(int x)
{
    if (x < 0)
        x = -x;

    int c = 0;
    for (int i = x; i != 0; i /= 10)
    {
        c++;
    }

    return c;
}

char *intToCString(int x) // caller must delete[]
{
    const int digits = countDigits(x), size = (x < 0 ? digits + 1 : digits);
    char *temp = new char[size + 1];

    for (int i = size - 1, a = (x < 0 ? -x : x); a != 0 && i >= 0; --i, a /= 10)
    {
        temp[i] = '0' + (a % 10);
    }

    if (x < 0)
        temp[0] = '-';

    temp[size] = '\0';

    return temp;
}

char *doubleToCString(double x, int precision) // caller must delete[]
{
    int fractionalDigits = 0, integralDigits = countDigits(x);
    int a = ((int)x);

    for (double i = (x - ((int)x)) * 10; (i - (int)i) > 1e-20 && fractionalDigits <= precision; i *= 10, ++fractionalDigits)
    {
        i = i - ((int)i);
    }

    char *res = new char[(fractionalDigits + integralDigits + 1) + (1) + (x < 0 ? 1 : 0)];
    int resCounter = 0;
    if (x < 0)
        res[resCounter++] = '-';

    char *integralPart = intToCString(x);

    for (int i = 0; i < integralDigits; ++i)
    {
        res[resCounter++] = integralPart[i];
    }

    res[resCounter++] = '.';

    for (double i = (x - ((int)x)) * 10, c = 0; c < fractionalDigits; i *= 10, ++c)
    {
        res[resCounter++] = '0' + (int)i;
        i = i - ((int)i);
    }

    res[resCounter] = '\0';

    delete[] integralPart;
    return res;
}

class String
{
private:
    char *m_str{};
    int m_len{};

    char circularAt(int index)
    {
        if (m_len == 0)
            return '\0';
        index %= m_len;

        if (index < 0)
            index = m_len + index;

        return m_str[index];
    }

public:
    String(char *str)
    {
        m_len = calculateLen(str);
        m_str = new char[m_len + 1];
        copyString(m_str, m_len + 1, str);
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

    char at(int i)
    {
        if (i < 0 || i >= m_len)
        {
            cout << "Bounds error while accessing string element.\n";
            return 0;
        }

        return m_str[i];
    }

    int *findIndexAll(char *substr) // caller must delete[]
    {
        int subLen = calculateLen(substr), totalFound = 0;
        if (subLen == 0)
            return nullptr;

        int *indices = new int[1];
        indices[0] = -1;

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
                totalFound++;

                int *temp = new int[totalFound + 1];
                for (int j = 0; j < totalFound - 1; ++j)
                    temp[j] = indices[j];

                temp[totalFound - 1] = i;
                temp[totalFound] = -1;
                delete[] indices;

                indices = temp;
            }
        }

        return indices;
    }

    int findIndex(char *substr)
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

    int compare(const String &obj)
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
        const char *substr = intToCString(x);
        concat(substr);

        delete[] substr;

        return *this;
    }
    String &concat(double x)
    {
        const char *substr = doubleToCString(x, 10);
        concat(substr);

        delete[] substr;

        return *this;
    }

    String &operator=(const String &obj)
    {
        if (m_str)
            delete[] m_str;

        m_len = obj.m_len;
        m_str = new char[m_len + 1];
        strcpy(m_str, obj.m_str);
    }

    String &operator+=(const char *substr)
    {
        return concat(substr);
    }
    String &operator+=(const string &s)
    {
        return concat(s);
    }
    String &operator+=(int i)
    {
        return concat(i);
    }
    String &operator+=(double d)
    {
        return concat(d);
    }

    friend ostream &operator<<(ostream &out, const String &obj);
};

ostream &operator<<(ostream &out, const String &obj)
{
    return out << obj.m_str;
}

int main()
{
    cout << doubleToCString(-12.0000000001, 10);

    return 0;
}