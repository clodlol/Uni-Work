#include < iostream >
using namespace std;
class ArrayQueue
{
private:
    int *arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    ArrayQueue(int cap = 5)
    {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }
    ~ArrayQueue()
    {
        delete[] arr;
    }

    bool isFull()
    {
        return count == capacity;
    }
    bool isEmpty()
    {
        return count == 0;
    }
    void enqueue(int value)
    {
        if (isFull())
            return;

        rear = (rear + 1) % capacity;
        arr[rear] = value;
        count++;
    }
    int dequeue()
    {
        if (isEmpty())
            return -1;

        int val = arr[front];
        front = (front + 1) % capacity;
        count--;
        return val;
    }
    int peek()
    {
        if (isEmpty())
            return -1;
        return arr[front];
    }
    void display()
    {
        if (isEmpty())
            return;

        for (int i = front; i != rear; (i = (i + 1) % capacity))
        {
            cout << arr[i] << "->";
        }
        cout << arr[rear] << "->";
    }
};
int main()
{
    ArrayQueue q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << " Dequeued : " << q.dequeue() << endl;
    q.enqueue(4);
    q.display();
    return 0;
}