#include <iostream>
using namespace std;

template <typename T>
class DynamicArray
{
private:
    T *data;
    int capacity;
    int currentSize;

public:
    DynamicArray(int cap) : data{new T[cap]}, currentSize{0}, capacity{cap} {}
    DynamicArray(const DynamicArray &other)
    {
        delete[] data;

        capacity = other.capacity;
        currentSize = other.currentSize;

        data = new T[capacity];

        for (int i = 0; i < currentSize; ++i)
        {
            data[i] = other.data[i];
        }
    }
    ~DynamicArray()
    {
        delete[] data;
    }

    T get(int index) const
    {
        return data[index];
    }

    void insert(T value)
    {
        if (currentSize >= capacity)
        {
            capacity *= 2;
            T *temp = new T[capacity];
            for (int i = 0; i < currentSize; ++i)
            {
                temp[i] = data[i];
            }

            delete[] data;
            data = temp;
        }

        data[currentSize] = value;
        currentSize++;
    }

    void set(int index, T value)
    {
        // index check?
        data[index] = value;
    }

    int size() const
    {
        return currentSize;
    }

    bool isEmpty() const
    {
        return currentSize == 0;
    }

    void display() const
    {
        for (int i = 0; i < currentSize; ++i)
        {
            cout << data[i] << " ";
        }
    }

    void removeAt(int index)
    {
        // index check?
        T *temp = new T[currentSize - 1];
        int tempCtr = 0;
        for (int i = 0; i < currentSize; ++i)
        {
            if (i == index)
                continue;

            temp[tempCtr++] = data[i];
        }

        currentSize--;
        delete[] data;
        data = temp;
    }
};

int main()
{
    DynamicArray<int> arr(5);

    cout << "Inserting elements..." << endl;
    arr.insert(10);
    arr.insert(20);
    arr.insert(30);
    arr.insert(40);
    arr.insert(50);
    arr.insert(60); // triggers resize

    cout << "Array contents: ";
    arr.display();
    cout << endl;

    cout << "Size: " << arr.size() << endl;
    cout << "Is empty? " << (arr.isEmpty() ? "Yes" : "No") << endl;

    cout << "Setting index 2 to 99..." << endl;
    arr.set(2, 99);

    cout << "Array contents after set: ";
    arr.display();
    cout << endl;

    cout << "Removing element at index 3..." << endl;
    arr.removeAt(3);

    cout << "Array contents after removal: ";
    arr.display();
    cout << endl;

    cout << "Final size: " << arr.size() << endl;

    return 0;
}