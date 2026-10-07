#include <iostream>
using namespace std;

class Customer
{
private:
    int tokenNumber;
    string name;
    string serviceType;

public:
    Customer() : tokenNumber{}, name{}, serviceType{} {}
    Customer(int p_tokenNumber,
             const string &p_name,
             const string &p_serviceType) : tokenNumber{p_tokenNumber}, name{p_name}, serviceType{p_serviceType} {}

    int getTokenNumber() const { return tokenNumber; }
    const string &getName() const { return name; }
    const string &getServiceType() const { return serviceType; }
};

template <typename T>
struct Node
{
    T val;
    Node<T> *next;
    Node(const T &p_val) : val{p_val}, next{NULL} {}
    Node(const T &p_val, Node<T> *p_next) : val{p_val}, next{p_next} {}
};

template <typename T>
class Queue
{
private:
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    Queue() : head{NULL}, tail{NULL}, size{0} {}

    Queue &operator=(const Queue &other)
    {
        if (this == &other)
            return *this;

        while (!isEmpty())
            dequeue();

        auto ptr = other.head;
        while (ptr != NULL)
        {
            this->enqueue(ptr->val);
            ptr = ptr->next;
        }

        return *this;
    }

    void enqueue(T data)
    {
        auto newNode = new Node<T>(data);
        size++;
        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
            return;
        }

        tail->next = newNode;
        tail = newNode;
    }

    T dequeue()
    {
        if (isEmpty())
            return T{};

        auto temp = head;
        auto data = temp->data;

        if (temp == head)
            head = NULL;
        if (temp == tail)
            tail = NULL;

        head = head->next;

        delete temp;
        size--;
        return data;
    }

    T front() const { return (isEmpty() ? T{} : head->val); }

    bool isEmpty() const { return head == NULL; }
    int size() const { return size; }

    void display() const
    {
        auto ptr = head;
        cout << "<- ";
        while (ptr != NULL)
        {
            cout << ptr->val << " ";
            ptr = ptr->next;
        }
        cout << "<-\n";
    }
};

class CustomerServiceCenter
{
private:
    Queue<Customer> queues[4];
    int currentQueue;

public:
    CustomerServiceCenter() : currentQueue{0} {}

    void addCustomer(Customer customer)
    {
        int smallestQueueIndex = findSmallestQueue();

        if (customer.getName().size() > 0)
            queues[smallestQueueIndex].enqueue(customer);

        if (queues[currentQueue].isEmpty())
            currentQueue = smallestQueueIndex;
    }

    int findSmallestQueue() const
    {
        int smallestIndex = 0;
        for (int i = 1; i < 4; ++i)
        {
            if (queues[i].size() < queues[smallestIndex].size())
                smallestIndex = i;
        }

        return smallestIndex;
    }

    void serveCustomer(int queueNumber)
    {
        if (queueNumber >= 0 && queueNumber < 4)
            queues[queueNumber].dequeue();

        if (queues[currentQueue].isEmpty())
            currentQueue = currentQueue + 1 % 4;
    }

    void serveNextCustomer()
    {
        queues[currentQueue].dequeue();

        if (queues[currentQueue].isEmpty())
            currentQueue = currentQueue + 1 % 4;
    }

    void displayAllQueues() const
    {
        for (int i = 0; i < 4; ++i)
        {
            cout << "QUEUE [" << i + 1 << "]: ";
            queues[i].display();
        }
    }
    void displayQueue(int queueNumber) const
    {
        if (queueNumber >= 0 && queueNumber < 4)
            queues[queueNumber].display();
    }

    int getQueueSize(int queueNumber) const
    {
        if (queueNumber >= 0 && queueNumber < 4)
            return queues[queueNumber].size();

        return -1;
    }

    int getTotalWaitingCustomers() const
    {
        int sum = 0;
        for (int i = 0; i < 4; ++i)
            sum += queues[i].size();

        return sum;
    }

    bool isQueueEmpty(int queueNumber) const
    {
        if (queueNumber >= 0 && queueNumber < 4)
            return queues[queueNumber].isEmpty();

        return true;
    }

    void removeCustomer(int tokenNumber)
    {
        for (int i = 0; i < 4; ++i)
        {
            Queue<Customer> temp;
            while (!queues[i].isEmpty())
            {
                if (queues[i].front().getTokenNumber() == tokenNumber)
                {
                    queues[i].dequeue();
                }
                else
                {
                    temp.enqueue(queues[i].dequeue());
                }
            }

            queues[i] = temp;
        }
    }

    void searchCustomer(int tokenNumber)
    {
        for (int i = 0; i < 4; ++i)
        {
            Queue<Customer> temp;
            while (!queues[i].isEmpty())
            {
                if (queues[i].front().getTokenNumber() == tokenNumber)
                {
                    cout << "Customer with token number [" << tokenNumber << "] is in queue " << i + 1 << ".\n";
                }
                temp.enqueue(queues[i].dequeue());
            }

            queues[i] = temp;
        }
    }
};