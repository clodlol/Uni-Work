#include <iostream>

using namespace std;

void inputArray(int* arr, int size);
void displayArray(int* arr, int size);
int findMinimum(int* arr, int size);
int findMaximum(int* arr, int size);
int calculateSum(int* arr, int size);
int countEven(int* arr, int size);
void reverseArray(int* arr, int size);

int main()
{
   int size = 0;
   cout << "Enter the array size: ";
   cin >> size;

   int* arr = nullptr;
   
   arr = new int[size];

   inputArray(arr, size);
   displayArray(arr, size);
   int min = findMinimum(arr, size);
   cout << "Minimum: " << min << "\n";
   int max = findMaximum(arr, size);
   cout << "Maximum: " << max << "\n";
   int sum = calculateSum(arr, size);
   cout << "Sum: " << sum << "\n";
   float avg = sum / (float)size;
   cout << "Average: " << avg << "\n";
   int numEven = countEven(arr, size);
   cout << "Evens: " << numEven << "\n";
   reverseArray(arr, size);
   cout << "Reversed ";
   displayArray(arr, size);

   delete[] arr;

   return 0;
}


void inputArray(int* arr, int size)
{

   for (int i = 0; i < size; ++i)
   {
       cout << "Enter element " << i << ": ";
       cin >> *(arr + i);
   }
}

void displayArray(int* arr, int size)
{
   cout << "Array: ";
   for (int i = 0; i < size; ++i)
       cout << *(arr + i)  << " ";
   cout << "\n";
}

int findMinimum(int* arr, int size)
{
   int min = *(arr);
   for (int i = 1; i < size; ++i)
   {
       if (*(arr + i) < min)
           min = *(arr + i);
   }

   return min;
}

int findMaximum(int* arr, int size)
{
   int max = *(arr);
   for (int i = 1; i < size; ++i)
   {
       if (*(arr + i) > max)
           max = *(arr + i);
   }

   return max;
}

int calculateSum(int* arr, int size)
{
   int sum = 0;
   for (int i = 0; i < size; ++i)
   {
       sum += *(arr + i);
   }

   return sum;
}

int countEven(int* arr, int size)
{
   int evens = 0;
   for (int i = 0; i < size; ++i)
   {
       if (*(arr + i) % 2 == 0)
           evens++;
   }

   return evens;
}

void reverseArray(int* arr, int size)
{
   for (int i = 0; i < size/2; ++i)
   {
       swap(*(arr + i), *(arr + (size - 1 - i)));
   }
}