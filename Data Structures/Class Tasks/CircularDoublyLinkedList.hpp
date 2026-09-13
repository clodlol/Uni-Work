#pragma once
#include <iostream>
#include <mergeSort.hpp>

using namespace std;

template <typename T>
class Node
{
private:
    Node<T> *prev;
    Node<T> *next;
    T data;

public:
    Node(const T &d) : prev{nullptr}, next{nullptr}, data{d} {}
};

template <typename T>
class CircularDoublyLinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;

public:
    CircularDoublyLinkedList() : head{nullptr}, tail{nullptr} {}

    void display() const
    {
        if (!head)
            return;

        Node<T> *ptr = head;
        while (ptr != head)
        {
            cout << ptr->data << "->";
            ptr = ptr->next;
        }

        cout << "END\n";
    }

    CircularDoublyLinkedList &deleteMany(const T &d)
    {
        if (!head)
        {
            return *this;
        }

        while (head->data == d)
        {
            if (head->next == head)
            {
                delete head;
                head = nullptr;
                tail = nullptr;
                return *this;
            }

            Node<T> *temp = head;
            tail->next = head->next;
            head->next->prev = tail;
            head = head->next;
            delete temp;
        }

        Node<T> *ptr = head;
        while (ptr->next != head)
        {
            if (ptr->next->data == d)
            {
                Node<T> *temp = ptr->next;
                ptr->next = temp->next;
                temp->next->prev = ptr;

                if (temp == tail)
                {
                    tail = tail->prev;
                }

                delete temp;

                continue;
            }

            ptr = ptr->next;
        }

        return *this;
    }

    CircularDoublyLinkedList &deleteOne(const T &d)
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
                tail = nullptr;

                return *this;
            }

            Node<T> *temp = head;
            tail->next = head->next;
            head->next->prev = tail;
            head = head->next;
            delete temp;

            return *this;
        }

        Node<T> *ptr = head;
        while (ptr->next != head)
        {
            if (ptr->next->data == d)
            {
                Node<T> *temp = ptr->next;

                if (temp == tail)
                {
                    tail = temp->prev;
                }

                ptr->next->next->prev = ptr;
                ptr->next = ptr->next->next;

                delete temp;

                return *this;
            }

            ptr = ptr->next;
        }

        return *this;
    }

    CircularDoublyLinkedList &insertMany(const T *arr, int size)
    {
        if (size <= 0)
        {
            return *this;
        }

        int sortedCtr = 0;
        T *sortedData = new T[size];
        for (int i = 0; i < size; ++i)
        {
            sortedData[i] = arr[i];
        }

        mergeSort(sortedData, 0, size - 1);

        if (!head)
        {
            head = new Node<T>(sortedData[sortedCtr]);
            tail = head;
            head->prev = tail;
            head->next = tail;
            tail->next = head;
            tail->prev = head;
            sortedCtr++;
        }

        while (sortedCtr < size && sortedData[sortedCtr] <= head->data)
        {
            Node<T> *temp = new Node<T>(sortedData[sortedCtr]);
            temp->prev = head->prev;
            temp->next = head;
            head->prev->next = temp;
            head->prev = temp;
            head = temp;
            sortedCtr++;
        }

        Node<T> *ptr = head;
        while (sortedCtr < size)
        {
            if (ptr->next->data <= sortedData[sortedCtr] && ptr->next != head)
            {
                ptr = ptr->next;
                continue;
            }

            Node<T> *temp = new Node<T>(sortedData[sortedCtr]);
            temp->prev = ptr;
            temp->next = ptr->next;
            ptr->next->prev = temp;
            ptr->next = temp;
            sortedCtr++;

            if (ptr == tail)
            {
                tail = temp;
            }

            ptr = ptr->next;
        }

        delete[] sortedData;

        return *this;
    }

    CircularDoublyLinkedList &insert(const T &d)
    {
        if (!head)
        {
            head = new Node<T>(d);
            tail = head;
            head->prev = tail;
            head->next = tail;
            tail->next = head;
            tail->prev = head;
            return *this;
        }

        if (d <= head->data)
        {
            Node<T> *newNode = new Node<T>(d);
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            head = newNode;
            tail->next = head;
            return *this;
        }

        Node<T> *ptr = head;
        while (ptr->next != head)
        {
            if (ptr->next->data >= d)
            {
                Node<T> *newNode = new Node<T>(d);
                newNode->prev = ptr;
                newNode->next = ptr->next;
                ptr->next->prev = newNode;
                ptr->next = newNode;
                return *this;
            }

            ptr = ptr->next;
        }

        Node<T> *newNode = new Node<T>(d);
        newNode->next = head;
        newNode->prev = ptr;
        ptr->next = newNode;
        head->prev = newNode;
        tail = newNode;

        return *this;
    }
};