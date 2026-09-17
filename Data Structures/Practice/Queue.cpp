#include <iostream>
using namespace std;

class Queue
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node(int val) : data{val}, next{nullptr} {}
    };

    Node *front;
    Node *rear;

    void clear()
    {
        auto ptr = front;
        while (ptr)
        {
            auto temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }

public:
    Queue() : front{nullptr}, rear{nullptr} {}

    ~Queue()
    {
        clear();
    }

    void enqueue(int val)
    {

        if (!front)
        {
            front = new Node(val);
            rear = front;
            return;
        }

        rear->next = new Node(val);
        rear = rear->next;
    }

    Node *dequeue()
    {
        if (!front)
        {
            return nullptr;
        }

        auto temp = front;
        front = front->next;

        if (!front)
        {
            rear = nullptr;
        }

        return temp;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    int size() const
    {
        int count = 0;
        auto ptr = front;
        while (ptr)
        {
            count++;
            ptr = ptr->next;
        }

        return count;
    }
};