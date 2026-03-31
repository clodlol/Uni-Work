#include <iostream>
using namespace std;

class Author
{
    string m_name{};
    string m_email{};
    char m_gender{};

public:
    Author() {}
    Author(const string &name, const string &email, char gender)
        : m_name{name}, m_email{email}, m_gender{gender} {}

    const string &getName() const { return m_name; }
    const string &getEmail() const { return m_email; }
    void setEmail(const string &email) { m_email = email; }
    const char &getGender() const { return m_gender; }
    void print() const
    {
        cout << m_name << " (" << m_gender << ") at " << m_email << "\n";
    }
};

class Book
{
    string m_name{};
    Author m_author{};
    double m_price{};
    int m_qty{};

public:
    Book(const string &name, const Author &author, double price, int qty = 0)
        : m_name{name}, m_author{author}, m_price{price}, m_qty{qty} {}

    const string &getName() const { return m_name; }
    const Author &getAuthor() const { return m_author; }
    Author &getAuthor() { return m_author; }
    double getPrice() const { return m_price; }
    void setPrice(double price) { m_price = price; }
    int getQty() const { return m_qty; }
    void setQty(int qty) { m_qty = qty; }
    void print() const
    {
        cout << m_name << " by ";
        m_author.print();
    }
};

int main()
{
    Author peter{"Peter Jones", "peter@somewhere.com", 'm'};
    peter.print();

    Book book{"C++ for Dummies", peter, 19.99};
    book.print();

    peter.setEmail("peter@xyz.com");
    peter.print();
    book.print();

    book.getAuthor().setEmail("peter@abc.com");
    book.print();

    return 0;
}