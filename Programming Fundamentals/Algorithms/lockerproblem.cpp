#include <iostream>
using namespace std;

int main()
{
    int lockers = 1000;
    int students = 1000;
    int open = 0;

    for(int i = 1; i <= lockers; i++)
    {
        int timesTouched = 0;
        for(int j = 1; j <= students; j++)
        {
            if(i%j == 0)
            {
                timesTouched++;
            }
        }
        if(timesTouched % 2 != 0) open++;
    }
}