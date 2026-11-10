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

class StoneSimulator
{
public:
    int lastStoneWeight(const int *stones, int n)
    {
        MaxHeap heap(stones, n);
        while (heap.size() > 1)
        {
            int y = heap.top();
            heap.pop();
            int x = heap.top();
            heap.pop();
            int difference = y - x;
            if (y - x == 0)
                continue;

            heap.push(difference);
        }

        return heap.empty() ? 0 : heap.top();
    }
};