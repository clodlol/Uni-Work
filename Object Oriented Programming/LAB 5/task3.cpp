#include <iostream>
#include <vector>
using namespace std;

class Customer
{
    int id;
    string name;
    string email;
    string phone;

public:
    Customer() {}
    Customer(int id, string n, string e, string p) : id(id), name(n), email(e), phone(p) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }

    void setId(const int &id) { this->id = id; }
    void setName(const int &n) { name = n; }
    void setEmail(const int &e) { email = e; }
    void setPhone(const int &p) { phone = p; }
};

int main()
{
    vector<Customer> customerProfiles;

    return 0;
}