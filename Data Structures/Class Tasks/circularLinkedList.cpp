#include <iostream>
using namespace std;

template <typename T>
class CircularLinkedList;

template <typename T>
class Node
{
private:
    T data;
    Node *next;

public:
    Node(const T &d) : data{d}, next{nullptr} {}

    friend class CircularLinkedList<T>;
};

template <typename T>
class CircularLinkedList
{
private:
    Node<T> *head;

    void clear()
    {
        if (!head)
        {
            return;
        }

        Node<T> *tempHead = head;
        Node<T> *ptr = head;

        do
        {
            Node<T> *temp = ptr;
            ptr = ptr->next;

            delete temp;
        } while (ptr != tempHead);

        head = nullptr;
    }

public:
    CircularLinkedList() : head{nullptr} {}
    CircularLinkedList(const CircularLinkedList<T> &other) : head{nullptr}
    {
        *this = other;
    }
    ~CircularLinkedList()
    {
        clear();
    }

    CircularLinkedList<T> &operator=(const CircularLinkedList<T> &other)
    {
        if (&other == this)
        {
            return *this;
        }

        if (!other.head)
        {
            clear();
            head = nullptr;
            return *this;
        }

        clear();

        Node<T> *ptr = head;
        Node<T> *otherPtr = other.head;
        do
        {
            Node<T> *temp = new Node<T>(otherPtr->data);

            if (!head)
            {
                ptr = temp;
                head = ptr;
                otherPtr = otherPtr->next;
                continue;
            }

            ptr->next = temp;
            ptr = ptr->next;
            otherPtr = otherPtr->next;
        } while (otherPtr != other.head);

        ptr->next = head;

        return *this;
    }

    void display() const
    {
        if (!head)
            return;

        cout << head->data << "->";

        Node<T> *ptr = head->next;

        while (ptr != head)
        {
            cout << ptr->data << "->";
            ptr = ptr->next;
        }

        cout << "END\n";
    }

    CircularLinkedList<T> &insert(const T &d)
    {
        if (!head)
        {
            head = new Node<T>(d);
            head->next = head;
            return *this;
        }

        if (head->data > d)
        {
            Node<T> *temp = new Node<T>(d);
            temp->next = head;

            Node<T> *ptr = head;
            while (ptr->next != head)
            {
                ptr = ptr->next;
            }

            ptr->next = temp;
            head = temp;

            return *this;
        }

        Node<T> *ptr = head;
        while (ptr->next != head && ptr->next->data < d)
        {
            ptr = ptr->next;
        }

        Node<T> *temp = new Node<T>(d);
        temp->next = ptr->next;
        ptr->next = temp;

        return *this;
    }

    CircularLinkedList<T> &deleteOne(const T &d)
    {
        if (!head)
        {
            return *this;
        }

        if (head->data == d)
        {
            if (head->next == head)
            {
                delete head;
                head = nullptr;
                return *this;
            }

            Node<T> *elToDelete = head;
            Node<T> *ptr = head;

            while (ptr->next != head)
            {
                ptr = ptr->next;
            }

            ptr->next = elToDelete->next;
            head = ptr->next;
            delete elToDelete;
            return *this;
        }

        Node<T> *ptr = head;

        while (ptr->next != head && ptr->next->data != d)
        {
            ptr = ptr->next;
        }

        if (ptr->next == head && ptr->data != d)
        {
            return *this;
        }

        Node<T> *elToDelete = ptr->next;
        ptr->next = elToDelete->next;
        delete elToDelete;

        return *this;
    }

    CircularLinkedList<T> &deleteMany(const T &d)
    {
        if (!head)
        {
            return *this;
        }

        Node<T> *lastEl = head;
        while (lastEl->next != head)
        {
            lastEl = lastEl->next;
        }

        while (head->data == d)
        {
            Node<T> *elToDelete = head;

            if (elToDelete->next == elToDelete)
            {
                delete elToDelete;
                head = nullptr;
                return *this;
            }

            head = head->next;
            lastEl->next = head;

            delete elToDelete;
        }

        Node<T> *ptr = head;
        while (ptr->next != head)
        {
            if (ptr->next->data == d)
            {
                Node<T> *elToDelete = ptr->next;
                ptr->next = elToDelete->next;

                delete elToDelete;

                continue;
            }

            ptr = ptr->next;
        }

        return *this;
    }
};

int main()
{
    CircularLinkedList<int> list;
    list.insert(0).insert(1).insert(0).insert(3).insert(2).display();
    list.deleteMany(0).display();

    return 0;
}