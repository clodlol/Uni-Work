#include <iostream>
using namespace std;

bool validateDirection(char direction)
{
    return (direction == 'E' || direction == 'e' || direction == 'W' || direction == 'w' || direction == 'S' || direction == 's' || direction == 'N' || direction == 'n');
}

class Angle
{
    int degrees;
    float minutes;
    char direction;

public:
    Angle(int degrees = 0, float minutes = 0.00f, char direction = 'E')
    {
        this->degrees = degrees;
        this->minutes = minutes;
        this->direction = direction;
    }

    void print()
    {
        cout << "Current coordinates: ";
        cout << degrees << "\xF8" << minutes << "'" << direction << endl;
    }

    void input()
    {
        do
        {
            cout << "Enter the degrees: ";
            cin >> degrees;
        } while (degrees < 0 || degrees > 180);

        do
        {
            cout << "Enter the minutes: ";
            cin >> minutes;
        } while (minutes < 0);

        do
        {
            cout << "Enter the direction: ";
            cin >> direction;
        } while (!validateDirection(direction));
    }
};

int main()
{
    Angle angle;
    angle.print();

    while (true)
    {
        cout << "Enter coordinates (Ctrl+C to quit): " << endl;

        angle.input();
        angle.print();
    }
    return 0;
}