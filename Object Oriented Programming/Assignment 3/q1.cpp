#include <iostream>
#include <ctime>

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 1960)
        : day{d}, month{m}, year{y} {}

    int difference(const Date &other)
    {
        int jdn1 = day + (13 * (month + 1) / 5) + year + (year / 4) - (year / 100) + (year / 400) + 1721119;
        int jdn2 = other.day + (13 * (other.month + 1) / 5) + other.year + (other.year / 4) - (other.year / 100) + (other.year / 400) + 1721119;

        return std::abs(jdn1 - jdn2);
    }

    int operator-(const Date &other)
    {
        return difference(other);
    }

    void print()
    {
        std::cout << day << "/" << month << "/" << year;
    }
};

Date currentDate()
{
    std::time_t now = std::time(nullptr);
    std::tm *ltm = std::localtime(&now);

    return Date{ltm->tm_mday, (1 + ltm->tm_mon), (1900 + ltm->tm_year)};
}

class Item
{
protected:
    char *name;
    float originalPrice;

public:
    virtual float getPrice() = 0;
    virtual void display() = 0;
    virtual ~Item()
    {
        if (name)
            delete[] name;
    }
};

class Perishable : public Item
{
private:
    Date expiryDate;
    int quantity;

public:
    Perishable(const char *n, float p, int d, int m, int y, int q)
        : expiryDate{d, m, y}, quantity{q}
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        originalPrice = p;
    }

    float getPrice() override
    {
        if (currentDate() - expiryDate >= 0)
        {
            return 0.f;
        }

        return originalPrice;
    }

    void display() override
    {
        std::cout << "Perishable: " << name << " x" << quantity << " | Rs. " << originalPrice << " -> Rs. " << getPrice() << " | ";
        expiryDate.print();
        std::cout << "\n";
    }
};

class Permanent : public Item
{
protected:
    Date entryDate;

public:
    Permanent(const char *n, float p, int d, int m, int y)
        : entryDate{d, m, y}
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        originalPrice = p;
    }

    virtual float getPrice() override
    {
        return originalPrice * 0.002 * (currentDate() - entryDate);
    }

    virtual void display() override
    {
        std::cout << "Permanent: " << name << " | Rs. " << originalPrice << " -> Rs. " << getPrice() << " | ";
        entryDate.print();
        std::cout << "\n";
    }

    virtual ~Permanent() = default;
};

class BulkItem : public Permanent
{
private:
    char *description;
    bool isSet;

public:
    BulkItem(const char *n, float p, int d, int m, int y, const char *desc, bool s) : Permanent{n, p, d, m, y}, isSet{s}
    {
        description = new char[strlen(desc) + 1];
        strcpy(description, desc);
    }

    float getPrice() override
    {
        if (isSet)
            return originalPrice;

        return Permanent::getPrice();
    }

    void display() override
    {
        std::cout << "Bulk Item: " << (isSet ? "Set of " : "") << name << " | " << description << " | Rs. " << originalPrice << " -> Rs. " << getPrice() << " | ";
        entryDate.print();
        std::cout << "\n";
    }

    ~BulkItem()
    {
        if (description)
            delete[] description;
    }
};

class Pharmacy
{
private:
    Item **items;
    int cap;
    int count;

public:
    Pharmacy(int size) : cap{size}
    {
        items = nullptr;
        count = 0;
    }

    void AddItem(Item *ptr)
    {
        Item **temp = new Item *[count + 1];
        for (int i = 0; i < count; ++i)
            temp[i] = items[i];

        temp[count] = ptr;

        delete[] items;

        items = temp;
        count++;
    }

    void DisplayItems()
    {
        for (int i = 0; i < count; ++i)

            items[i]->display();
    }

    ~Pharmacy()
    {
        for (int i = 0; i < count; ++i)
            if (items[i])
                delete items[i];

        delete[] items;
    }
};

int main()
{
    int itemCount = 4;
    Pharmacy ph(itemCount);
    Item *iptr = new Permanent("Glucometer", 5000, 15, 11, 2025);

    ph.AddItem(iptr);
    iptr = new Perishable("Panadol", 20, 16, 11, 2018, 500);

    ph.AddItem(iptr);
    iptr = new BulkItem("Gloves", 500, 12, 10, 2016, "Glove box for doctors", true);

    ph.AddItem(iptr);
    iptr = new BulkItem("5CC Syringe", 90, 15, 7, 2017, "For Injections only", false);

    ph.AddItem(iptr);
    ph.DisplayItems();

    return 0;
}