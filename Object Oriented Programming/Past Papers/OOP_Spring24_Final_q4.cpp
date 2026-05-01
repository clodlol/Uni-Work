#include <iostream>

class Address
{
private:
    int Type;
    std::string Street;
    std::string City;
    std::string State;
    std::string PostCode;
    std::string Country;

public:
    Address(int type = 1, std::string street = "", std::string city = "", std::string state = "", std::string postcode = "", std::string country = "") : Type{type}, Street{street}, City{city}, State{state}, PostCode{postcode}, Country{country} {}

    void Print()
    {
        std::string addressType;
        if (Type == 1)
            addressType = "Home";
        else if (Type == 2)
            addressType = "Work";
        else
            addressType = "Other";

        std::cout << "[" << addressType << "] " << Street << "\n"
                  << City << ", " << State << " " << PostCode << "\n"
                  << Country;
    }
};

class PhoneNo
{
private:
    int Type;
    std::string Number;

public:
    PhoneNo(int type = 1, std::string number = "") : Type{type}, Number{number} {}

    void Print()
    {
        std::string phoneType;
        if (Type == 1)
            phoneType = "Mobile";
        else if (Type == 2)
            phoneType = "Home";
        else if (Type == 3)
            phoneType = "Work Fax";
        else
            phoneType = "Other";

        std::cout << "[" << phoneType << "] " << Number;
    }
};

class Contact
{
private:
    std::string Name;
    PhoneNo *Phone;
    int phoneCount;
    Address *m_Address;
    int addressCount;

public:
    Contact(std::string name = "") : Name{name}, Phone{nullptr}, m_Address{nullptr}, phoneCount{0}, addressCount{0} {}
    Contact(const Contact &other)
    {
        *this = other;
    }
    ~Contact()
    {
        if (Phone)
            delete[] Phone;

        if (m_Address)
            delete[] m_Address;
    }

    void Print()
    {
        std::cout << "[Name] " << Name << "\n";

        for (int i = 0; i < phoneCount && Phone; ++i)
        {
            Phone[i].Print();
            std::cout << "\n";
        }

        for (int i = 0; i < addressCount && m_Address; ++i)
        {
            m_Address[i].Print();
            std::cout << "\n";
        }
    }

    Contact &operator=(const Contact &other)
    {
        if (&other == this)
            return *this;

        if (Phone)
            delete[] Phone;

        if (m_Address)
            delete[] m_Address;

        phoneCount = other.phoneCount;
        addressCount = other.addressCount;

        if (other.m_Address)
        {
            m_Address = new Address[other.addressCount];
            for (int i = 0; i < addressCount; ++i)
            {
                m_Address[i] = other.m_Address[i];
            }
        }

        if (other.Phone)
        {
            Phone = new PhoneNo[other.phoneCount];
            for (int i = 0; i < phoneCount; ++i)
            {
                Phone[i] = other.Phone[i];
            }
        }

        Name = other.Name;

        return *this;
    }

    void addContactDetail(PhoneNo *phonePtr)
    {
        PhoneNo *temp = new PhoneNo[phoneCount];
        if (Phone)
        {
            for (int i = 0; i < phoneCount && temp; ++i)
                temp[i] = Phone[i];

            delete[] Phone;
        }

        phoneCount++;

        Phone = new PhoneNo[phoneCount];
        for (int i = 0; i < phoneCount - 1 && temp; ++i)
            Phone[i] = temp[i];

        Phone[phoneCount - 1] = *phonePtr;
    }

    void addContactDetail(Address *addressPtr)
    {
        Address *temp = new Address[addressCount];
        if (m_Address)
        {
            for (int i = 0; i < addressCount && temp; ++i)
                temp[i] = m_Address[i];
            delete[] m_Address;
        }

        addressCount++;

        m_Address = new Address[addressCount];
        for (int i = 0; i < addressCount - 1 && temp; ++i)
            m_Address[i] = temp[i];

        m_Address[addressCount - 1] = *addressPtr;
    }
};

int main()
{
    Contact contact1("Ali Hamza");
    contact1.Print();
    std::cout << "-------------------------\n";

    Contact contact2("Usman Khalid");
    contact2.Print();
    std::cout << "-------------------------\n";

    contact1.addContactDetail(new PhoneNo(1, "0300-1234567"));
    contact1.Print();
    std::cout << "-------------------------\n";

    contact1.addContactDetail(new PhoneNo(3, "042-111-128-128"));
    contact1.addContactDetail(new Address(2, "852-B Milaad St, Block B Faisal Town", "Lahore", "Punjab", "54770", "Pakistan"));
    contact1.addContactDetail(new Address(1, "853-B Faisal Town", "Lahore", "Punjab", "54770", "Pakistan"));

    contact2.addContactDetail(new Address(3, "123-B XYZ Town", "Gujranwala", "Punjab", "12345", "Pakistan"));

    contact1.Print();
    std::cout << "-------------------------\n";

    contact2.Print();
    std::cout << "-------------------------\n";

    return 0;
}