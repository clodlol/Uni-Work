#include <iostream>
using namespace std;

class Date
{
    int day;
    int month;
    int year;

public:
    Date()
    {
        day = 1;
        month = 1;
        year = 1926;

        cout << "Default constructor called." << endl;
    }

    Date(int day, int month, int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    void print()
    {
        cout << day << "/" << month << "/" << year << endl;
    }

    void input()
    {
        do
        {
            cout << "Enter the day: ";
            cin >> day;
        } while (day < 1 || day > 30);

        do
        {
            cout << "Enter the month: ";
            cin >> month;
        } while (month < 1 || month > 12);

        do
        {
            cout << "Enter the year: ";
            cin >> year;
        } while (year < 1);
    }

    void setDay(int day)
    {
        this->day = day;
    }

    void setMonth(int month)
    {
        this->month = month;
    }

    void setYear(int year)
    {
        this->year = year;
    }

    int getDay()
    {
        return day;
    }

    int getMonth()
    {
        return month;
    }

    int getYear()
    {
        return year;
    }
};

int main()
{
    Date date1, xmasDay;

    xmasDay.print();

    xmasDay.setDay(25);
    xmasDay.setMonth(12);
    xmasDay.setYear(2020);

    cout << "XMAS Day: " << xmasDay.getDay() << " | XMAS Month: " << xmasDay.getMonth() << " | XMAS Year: " << xmasDay.getYear() << endl;

    return 0;
}