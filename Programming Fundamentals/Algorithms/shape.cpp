
#include <iostream>
#include <math.h>

using namespace std;

int main() {
    int n = 15;
    for(int i = -n; i <= n; i++) {
        for(int j = -n; j <= n; j++) {
            if(pow((j*j + i*i - n), 3) <= (j*j*i*i*i))
                cout << "*";
            else
                cout << "-";
        }
        cout << endl;
    }
    
    return 0;
}