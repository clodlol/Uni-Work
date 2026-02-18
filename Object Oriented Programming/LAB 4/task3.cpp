#include <iostream>
#include <conio.h>
using namespace std;

class TollBooth
{
    int carCount;
    double totalMoney;

public:
    TollBooth(int carCount = 0, double totalMoney = 0.00)
    {
        this->carCount = carCount;
        this->totalMoney = totalMoney;
    }

    void payingCar()
    {
        carCount++;
        totalMoney += 0.50;
    }

    void nonPayingCar()
    {
        carCount++;
    }

    void display()
    {
        cout << endl;
        cout << "Cars passed: " << carCount << " | Money collected: $" << totalMoney << endl;
    }
};

int main()
{
    TollBooth tollBooth;
    while (true)
    {
        cout << "Press W to count a paying car || Press S to count a non-paying car || Press ESC to quit: ";
        int keyPressed = getch();
        if (keyPressed == 'W' || keyPressed == 'w')
        {
            tollBooth.payingCar();
            tollBooth.display();
        }
        else if (keyPressed == 'S' || keyPressed == 's')
        {
            tollBooth.nonPayingCar();
            tollBooth.display();
        }
        else if (keyPressed == 27)
        {
            break;
        }
    }
    return 0;
}
