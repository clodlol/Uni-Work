#include <iostream>
using namespace std;

class MaxHeap
{
private:
    int *data;
    int capacity;
    int currentSize;

    void resize(int newCapacity)
    {
        int *temp = new int[newCapacity];
        for (int i = 0; i < currentSize; ++i)
            temp[i] = data[i];
        delete[] data;
        data = temp;
        capacity = newCapacity;
    }
    void siftUp(int index)
    {
        int child = index;
        int parent = (child - 1) / 2;
        while (child > parent)
        {
            if (data[child] > data[parent])
                swap(data[child], data[parent]);
            else
                break;

            child = parent;
            parent = (parent - 1) / 2;
        }
    }
    void siftDown(int index)
    {
        int parent = index;
        while (parent < currentSize)
        {
            int leftChild = parent * 2 + 1;
            int rightChild = parent * 2 + 2;

            if (leftChild >= currentSize)
                break;

            if (rightChild >= currentSize)
            {
                if (data[leftChild] > data[parent])
                    swap(data[leftChild], data[parent]);

                break;
            }

            int maxChild = max(data[leftChild], data[rightChild]) == data[leftChild] ? leftChild : rightChild;
            if (data[maxChild] > data[parent])
                swap(data[maxChild], data[parent]);
            else
                break;

            parent = maxChild;
        }
    }

public:
    MaxHeap(int initialCapacity = 10) : data(new int[initialCapacity <= 0 ? 1 : initialCapacity]), capacity(initialCapacity <= 0 ? 1 : initialCapacity), currentSize(0) {}
    MaxHeap(const int *arr, int size) : data(new int[size <= 0 ? 1 : size]), capacity(size <= 0 ? 1 : size), currentSize(0)
    {
        for (int i = 0; i < size; ++i)
            data[i] = arr[i];
        currentSize = size < 0 ? 0 : size;
        for (int i = (currentSize - 1) / 2; i >= 0; --i)
            siftDown(i);
    }
    ~MaxHeap()
    {
        delete[] data;
    }
    MaxHeap(const MaxHeap &other) = delete;
    MaxHeap &operator=(const MaxHeap &other) = delete;

    void push(int val)
    {
        if (currentSize + 1 > capacity)
        {
            resize(capacity * 2);
        }

        data[currentSize] = val;
        siftUp(currentSize);
        currentSize++;
    }
    void pop()
    {
        if (currentSize <= 0)
            return;
        data[0] = data[currentSize - 1];
        currentSize--;
        siftDown(0);
    }
    int top() const
    {
        return data[0];
    }
    bool empty() const
    {
        return currentSize == 0;
    }
    int size() const
    {
        return currentSize;
    }
    void printHeap() const
    {
        for (int i = 0; i < currentSize; ++i)
        {
            cout << data[i] << " ";
        }
        cout << "\n";
    }
};
class MinHeap
{
private:
    int *data;
    int capacity;
    int currentSize;

    void resize(int newCapacity)
    {
        int *temp = new int[newCapacity];
        for (int i = 0; i < currentSize; ++i)
            temp[i] = data[i];
        delete[] data;
        data = temp;
        capacity = newCapacity;
    }
    void siftUp(int index)
    {
        int child = index;
        int parent = (child - 1) / 2;
        while (child > parent)
        {
            if (data[child] < data[parent])
                swap(data[child], data[parent]);
            else
                break;

            child = parent;
            parent = (parent - 1) / 2;
        }
    }
    void siftDown(int index)
    {
        int parent = index;
        while (parent < currentSize)
        {
            int leftChild = parent * 2 + 1;
            int rightChild = parent * 2 + 2;

            if (leftChild >= currentSize)
                break;

            if (rightChild >= currentSize)
            {
                if (data[leftChild] < data[parent])
                    swap(data[leftChild], data[parent]);

                break;
            }

            int minChild = min(data[leftChild], data[rightChild]) == data[leftChild] ? leftChild : rightChild;
            if (data[minChild] < data[parent])
                swap(data[minChild], data[parent]);
            else
                break;

            parent = minChild;
        }
    }

public:
    MinHeap(int initialCapacity = 10) : data(new int[initialCapacity <= 0 ? 1 : initialCapacity]), capacity(initialCapacity <= 0 ? 1 : initialCapacity), currentSize(0) {}
    MinHeap(const int *arr, int size) : data(new int[size <= 0 ? 1 : size]), capacity(size <= 0 ? 1 : size), currentSize(0)
    {
        for (int i = 0; i < size; ++i)
            data[i] = arr[i];
        currentSize = size < 0 ? 0 : size;
        for (int i = (currentSize - 1) / 2; i >= 0; --i)
            siftDown(i);
    }
    ~MinHeap()
    {
        delete[] data;
    }
    MinHeap(const MinHeap &other) = delete;
    MinHeap &operator=(const MinHeap &other) = delete;

    void push(int val)
    {
        if (currentSize + 1 > capacity)
        {
            resize(capacity * 2);
        }

        data[currentSize] = val;
        siftUp(currentSize);
        currentSize++;
    }
    void pop()
    {
        if (currentSize <= 0)
            return;
        data[0] = data[currentSize - 1];
        currentSize--;
        siftDown(0);
    }
    int top() const
    {
        return data[0];
    }
    bool empty() const
    {
        return currentSize == 0;
    }
    int size() const
    {
        return currentSize;
    }
    void printHeap() const
    {
        for (int i = 0; i < currentSize; ++i)
        {
            cout << data[i] << " ";
        }
        cout << "\n";
    }
};

class MedianFinder
{
private:
    MaxHeap maxHeap;
    MinHeap minHeap;
    int elements;

public:
    MedianFinder() : elements(0) {}
    void addNum(int num)
    {
        elements++;

        if (maxHeap.empty() && minHeap.empty())
        {
            maxHeap.push(num);
            return;
        }

        if (!maxHeap.empty() && num <= maxHeap.top())
        {
            maxHeap.push(num);
        }
        else
        {
            minHeap.push(num);
        }

        while (maxHeap.size() - minHeap.size() > 1)
        {
            int el = maxHeap.top();
            maxHeap.pop();
            minHeap.push(el);
        }

        while (minHeap.size() - maxHeap.size() > 1)
        {
            int el = minHeap.top();
            minHeap.pop();
            maxHeap.push(el);
        }
    }
    double findMedian()
    {
        if (elements % 2 == 0)
        {
            return double((maxHeap.top() + minHeap.top()) / 2.0);
        }
        else
        {
            if (maxHeap.size() > minHeap.size())
            {
                return double(maxHeap.top() / 1.0);
            }
            else
            {
                return double(minHeap.top() / 1.0);
            }
        }
    }
};