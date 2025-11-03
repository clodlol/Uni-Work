#include <iostream>
using namespace std;

int main() {
    int scholars = 0, regulars = 0, weak = 0, students = 0;
    do {
        cout << "Enter the number of students: ";
        cin >> students;
    } while (students < 1);
    
    for(int i = 1; i <= students; i++) {
        int attendance = 0; 
        int marks = 0;
        cout << "-------------------------------------" << endl;
        cout << "Student " << i << endl;
        
        cout << "Attendance: ";
        cin >> attendance;
        
        cout << "Marks: ";
        cin >> marks;
        
        if(attendance >= 27 && marks >= 80) {
            scholars++;
        } else if(attendance >= 20 && (marks <= 79 && marks >= 60)) {
            regulars++;
        } else {
            weak++;
        }
    }
    
    cout << "-------------------------------------" << endl;
    cout << "Scholars: " << scholars << endl;
    cout << "Regulars: " << regulars << endl;
    cout << "Weaks: " << weak << endl; 
}