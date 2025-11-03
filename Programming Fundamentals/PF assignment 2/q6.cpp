#include <iostream>
using namespace std;

int main() {
    int n = 0;
    cout << "Enter number of students: ";
    cin >> n;
    int classAverageTotal = 0;
    int highestAverage = 0;
    int topperIndex = 0;
    for(int i = 1; i <= n; i++) {
        cout << "----------------------------------" << endl;
        cout << "STUDENT " << i << ":" << endl;
        const int subjects = 5;
        int totalMarks = 0;
        cout << "Marks: " << endl;
        for(int j = 1; j <= subjects; j++) {
            int currentMarks = 0;
            cin >> currentMarks;
            totalMarks += currentMarks;
        }
        int average = totalMarks/subjects;
        classAverageTotal += average;
        cout << "Total: " << totalMarks << endl;
        cout << "Average: " << average << endl;
        if(average > highestAverage) {
            highestAverage = average;
            topperIndex = i;
        }
    }
    cout << "----------------------------------" << endl;
    classAverageTotal = classAverageTotal/n;
    cout << "Class Average: " << classAverageTotal << endl;
    cout << "Highest Average: " << highestAverage << endl;
    cout << "Topper: Student " << topperIndex << endl;
}