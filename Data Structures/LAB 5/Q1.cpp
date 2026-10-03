#include < iostream >
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};
class LinkedListQueue
{
private:
    Node *front;
    Node *rear;
    int count;

public:
    LinkedListQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }
    ~LinkedListQueue()
    {
        auto ptr = front;
        while (ptr)
        {
            auto temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }
    bool isEmpty()
    {
        return front == nullptr;
    }
    void enqueue(int value)
    {
        auto newNode = new Node(value);
        if (!rear)
        {
            rear = newNode;
            front = newNode;
            count++;
            return;
        }
        rear->next = newNode;
        rear = rear->next;
        count++;
    }
    int dequeue()
    {
        if (isEmpty())
            return -1;
        auto temp = front;
        int num = temp->data;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        delete temp;
        return num;
    }
    int peek()
    {
        if (!front)
            return -1;
        return front->data;
    }
    void display()
    {
        if (isEmpty())
        {
            cout << " Queue is Empty " << endl;
            return;
        }
        Node *curr = front;
        cout << " Queue elements : ";
        while (curr != nullptr)
        {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << " nullptr " << endl;
    }
};
int main()
{
    LinkedListQueue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();
    cout << " Dequeued : " << q.dequeue() << endl;
    q.display();
    return 0;
}