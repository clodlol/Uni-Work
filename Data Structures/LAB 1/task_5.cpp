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

template <typename T>
class ArrayStatistics
{
private:
    DynamicArray<T> arr;

public:
    ArrayStatistics(const T *input, int size) : arr(size)
    {
        for (int i = 0; i < size; ++i)
        {
            arr.insert(input[i]);
        }
    }

    T minimum() const // O(n)
    {
        T min = arr.get(0);
        int size = arr.size();
        for (int i = 1; i < size; ++i)
        {
            if (arr.get(i) < min)
                min = arr.get(i);
        }

        return min;
    }
    T maximum() const // O(n)
    {
        T max = arr.get(0);
        int size = arr.size();
        for (int i = 1; i < size; ++i)
        {
            if (arr.get(i) > max)
                max = arr.get(i);
        }

        return max;
    }
    double average() const // O(n)
    {
        T sum = arr.get(0);
        int size = arr.size();
        for (int i = 1; i < size; ++i)
        {
            sum += arr.get(i);
        }

        return sum / (float)size;
    }

    int count(T value) const // O(n)
    {
        int cnt = 0;
        int size = arr.size();
        for (int i = 0; i < size; ++i)
        {
            if (arr.get(i) == value)
                cnt++;
        }

        return cnt;
    }

    void display() const // O(n)
    {
        int size = arr.size();
        for (int i = 0; i < size; ++i)
        {
            cout << arr.get(i) << " ";
        }

        cout << "\n";
    }
};

int main()
{
    int input[] = {12, 7, 9, 21, 7, 15};
    int size = sizeof(input) / sizeof(input[0]);

    ArrayStatistics<int> stats(input, size);

    cout << "Array contents: ";
    stats.display();

    cout << "Minimum: " << stats.minimum() << endl;
    cout << "Maximum: " << stats.maximum() << endl;
    cout << "Average: " << stats.average() << endl;

    int valueToCount = 7;
    cout << "Count of " << valueToCount << ": " << stats.count(valueToCount) << endl;

    return 0;
}
