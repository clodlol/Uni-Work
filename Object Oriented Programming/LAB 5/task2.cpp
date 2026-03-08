#include <iostream>
#include <conio.h>
using namespace std;

class Task
{
    string title;
    string description;
    bool isComplete;

public:
    Task() {}
    Task(string t, string d, bool b) : title(t), description(d), isComplete(b) {}

    string getTitle() { return title; }
    string getDescription() { return description; }
    bool getIsComplete() { return isComplete; }

    void setTitle(const string &s) { title = s; }
    void setDescription(const string &s) { description = s; }
    void setIsComplete(const bool &b) { isComplete = b; }

    void complete()
    {
        setIsComplete(true);
    }

    void incomplete()
    {
        setIsComplete(false);
    }
};

int main()
{
    Task task;
    while (true)
    {
        char choice;
        cout << "Press y to complete a task, n to make the task incomplete, or any other key to quit: ";
        choice = getch();
        if (choice == 'y')
        {
            task.complete();
            cout << "Task status: " << task.getIsComplete() << "\n";
        }
        else if (choice == 'n')
        {
            task.incomplete();
            cout << "Task status: " << task.getIsComplete() << "\n";
        }
        else
        {
            break;
        }
    }
    return 0;
}