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

void createCustomerProfile(vector<Customer> &customers, const int &id, const string &n, const string &e, const string &p)
{
    Customer c({id, n, e, p});
    customers.push_back(c);
}

void printCustomerProfiles(const vector<Customer> &customers)
{
    cout << "\n";
    for (int i = 0; i < customers.size(); i++)
    {
        cout << customers[i].getId() << "   " << customers[i].getName() << "  " << customers[i].getEmail() << "   " << customers[i].getPhone() << "\n";
    }
    cout << "\n";
}

int main()
{
    vector<Customer> customerProfiles;
    char choice = 'y';
    while (true)
    {
        cout << "Enter y to create a new profile or q to quit: ";
        cin >> choice;
        if (choice != 'y' && choice != 'q')
            continue;

        if (choice == 'q')
            break;

        int id;
        string n, e, p;
        cout << "\n";
        cout << "ID: ";
        cin >> id;
        cout << "Name: ";
        cin >> n;
        cout << "Email: ";
        cin >> e;
        cout << "Phone: ";
        cin >> p;

        createCustomerProfile(customerProfiles, id, n, e, p);
    }

    printCustomerProfiles(customerProfiles);

    return 0;
}