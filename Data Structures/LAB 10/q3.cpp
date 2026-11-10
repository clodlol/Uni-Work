#include <iostream>
using namespace std;

struct ElementFreq
{
    int element;
    int frequency;
};

class MinHeapFreq
{
private:
    ElementFreq *data;
    int capacity;
    int currentSize;

    void siftUp(int index)
    {
        int child = index;
        int parent = (child - 1) / 2;
        while (child > parent)
        {
            if (data[child].frequency < data[parent].frequency)
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
                if (data[leftChild].frequency < data[parent].frequency)
                    swap(data[leftChild], data[parent]);

                break;
            }

            int minChild = min(data[leftChild].frequency, data[rightChild].frequency) == data[leftChild].frequency ? leftChild : rightChild;
            if (data[minChild].frequency < data[parent].frequency)
                swap(data[minChild], data[parent]);
            else
                break;

            parent = minChild;
        }
    }

public:
    MinHeapFreq(int cap) : capacity(cap), currentSize(0), data(new ElementFreq[cap]) {}
    MinHeapFreq(const ElementFreq *arr, int size) : data(new ElementFreq[size]), capacity(size), currentSize(0)
    {
        for (int i = 0; i < size; ++i)
            data[i] = arr[i];
        currentSize = size < 0 ? 0 : size;
        for (int i = (currentSize - 1) / 2; i >= 0; --i)
            siftDown(i);
    }
    ~MinHeapFreq()
    {
        delete[] data;
    }

    void push(ElementFreq ef)
    {
        if (currentSize + 1 > capacity)
            return;

        data[currentSize] = ef;
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
    ElementFreq top() const
    {
        return data[0];
    }
    int size() const
    {
        return currentSize;
    }
    bool empty() const
    {
        return currentSize == 0;
    }
    bool full() const
    {
        return currentSize == capacity;
    }
};

class TopKAnalyzer
{
public:
    void getTopKFrequent(const int *nums, int n, int k, int *&result)
    {
        const int SIGNED_MAX = 10000;

        int counts[2 * SIGNED_MAX + 1] = {0};
        for (int i = 0; i < n; ++i)
        {
            counts[nums[i] + SIGNED_MAX]++;
        }

        MinHeapFreq heap(k);
        for (int i = 0; i < 2 * SIGNED_MAX + 1; ++i)
        {
            if (counts[i] == 0)
                continue;

            if (!heap.full())
            {
                heap.push(ElementFreq{i - SIGNED_MAX, counts[i]});
                continue;
            }

            if (!heap.empty() && counts[i] > heap.top().frequency)
            {
                heap.pop();
                heap.push(ElementFreq{i - SIGNED_MAX, counts[i]});
            }
        }

        delete[] result;
        result = new int[k];
        for (int i = 0; i < k; ++i)
        {
            result[i] = heap.top().element;
            heap.pop();
        }
    }
};