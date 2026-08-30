#pragma once

#include <iostream>
#include "mergeSort.hpp"

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

    CircularLinkedList<T> &insertOne(const T &d)
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

    CircularLinkedList<T> &insertMany(const T *dArr, int size)
    {
        if (size <= 0)
        {
            return *this;
        }

        T *sortedInput = new T[size];
        int sortedCtr = 0;
        for (int i = 0; i < size; ++i)
        {
            sortedInput[i] = dArr[i];
        }

        mergeSort(sortedInput, 0, size - 1);

        if (!head)
        {
            head = new Node<T>(sortedInput[sortedCtr]);
            head->next = head;
            sortedCtr++;
        }

        Node<T> *lastEl = head;
        while (lastEl->next != head)
        {
            lastEl = lastEl->next;
        }

        while (sortedCtr < size && head->data >= sortedInput[sortedCtr])
        {
            Node<T> *newNode = new Node<T>(sortedInput[sortedCtr]);

            newNode->next = head;
            head = newNode;
            lastEl->next = head;
            sortedCtr++;
        }

        Node<T> *ptr = head;
        while (sortedCtr < size && ptr->next != head)
        {
            if (ptr->next->data >= sortedInput[sortedCtr])
            {
                Node<T> *newNode = new Node<T>(sortedInput[sortedCtr]);
                newNode->next = ptr->next;
                ptr->next = newNode;
                sortedCtr++;
            }

            ptr = ptr->next;
        }

        while (sortedCtr < size && ptr->data <= sortedInput[sortedCtr])
        {
            Node<T> *newNode = new Node<T>(sortedInput[sortedCtr]);
            newNode->next = head;
            ptr->next = newNode;
            sortedCtr++;

            ptr = ptr->next;
        }

        delete[] sortedInput;

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

// int main()
// {
//     int arr[] = {5, 4, 3, 2, 1};
//     int size = sizeof(arr) / sizeof(arr[0]);

//     int low = 0, high = size - 1;
//     mergeSort<int>(arr, low, high);

//     for (int i = 0; i < size; ++i)
//     {
//         cout << arr[i] << " ";
//     }

//     cout << "\n";

//     return 0;
// }