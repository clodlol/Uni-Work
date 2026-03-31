#include <iostream>
using namespace std;

char *paddedInput(int input, int inputLen)
{
    if (inputLen <= 0)
        return nullptr;
    input = input < 0 ? -input : input;

    char *fInput = new char[inputLen + 1];
    int fInputCounter = 0;

    if (input == 0)
    {
        fInput[inputLen - fInputCounter - 1] = ('0');
        fInputCounter++;
    }

    for (int i = input; i != 0 && fInputCounter < inputLen; i /= 10)
    {
        fInput[inputLen - fInputCounter - 1] = ('0' + (i % 10));
        fInputCounter++;
    }

    while (fInputCounter < inputLen)
    {
        fInput[inputLen - fInputCounter - 1] = '0';
        fInputCounter++;
    }

    fInput[inputLen] = '\0';

    return fInput;
}

class Time
{
    int m_hrs{};
    int m_mins{};

public:
    Time() {};
    Time(int hrs, int mins) : m_hrs{hrs}, m_mins{mins} {}

    void getTime(int &hrs, int &mins)
    {
        hrs = m_hrs;
        mins = m_mins;
    }
    void setTime(int hrs, int mins)
    {
        m_hrs = hrs;
        m_mins = mins;
    }
    void printTime()
    {
        char *fHrs = paddedInput(m_hrs, 2);
        char *fMins = paddedInput(m_mins, 2);

        cout << fHrs << ":" << fMins;

        delete[] fHrs;
        delete[] fMins;
    }
    void incrementHrs() { m_hrs++; }
    void incrementMins() { m_mins++; }
};

class Date
{
    int m_mon{};
    int m_day{};
    int m_yr{};

public:
    Date() {}
    Date(int mon, int day, int yr) : m_mon{mon}, m_day{day}, m_yr{yr} {}

    void getDate(int &mon, int &day, int &yr)
    {
        mon = m_mon;
        day = m_day;
        yr = m_yr;
    }
    void setDate(int mon, int day, int yr)
    {
        m_mon = mon;
        m_day = day;
        m_yr = yr;
    }
    void printDate()
    {
        char *fMon = paddedInput(m_mon, 2);
        char *fDay = paddedInput(m_day, 2);
        char *fYr = paddedInput(m_yr, 4);

        cout << fMon << "/" << fDay << "/" << fYr;

        delete[] fMon;
        delete[] fDay;
        delete[] fYr;
    }
};

class Event
{
    string eventName{};
    Time eventTime{};
    Date eventDate{};

public:
    Event(int hrs = 0, int mins = 0, int mon = 1, int day = 1, int yr = 1900, const string &name = "christmas")
        : eventName{name}, eventTime{Time{hrs, mins}}, eventDate{Date{mon, day, yr}} {}

    void setEventData(int hrs, int mins, int mon, int day, int yr, const string &name)
    {
        eventName = name;
        eventTime.setTime(hrs, mins);
        eventDate.setDate(mon, day, yr);
    }
    void printEventData()
    {
        cout << "The event " << eventName << " is scheduled for ";
        eventDate.printDate();
        cout << " at ";
        eventTime.printTime();
        cout << "\n";
    }
};

int main()
{
    Event ev1{16, 0, 12, 11125, 123140, "Christmas"};
    ev1.printEventData();

    Event ev2{};
    ev2.setEventData(1, 15, 7, 4, 2010, "Fourth of July");
    ev2.printEventData();

    return 0;
}