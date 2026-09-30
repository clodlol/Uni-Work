#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T val;
    Node<T> *next;

    Node() : val{}, next{NULL} {}
    Node(T p_val) : val{p_val}, next{NULL} {}
    Node(T p_val, Node<T> *p_next) : val{p_val}, next{p_next} {}
};

template <typename T>
struct Stack
{
    Node<T> *sp;

    Stack() : sp{NULL} {}
    void push(const T &data)
    {
        Node<T> *temp = sp;
        sp = new Node<T>(data);
        sp->next = temp;
    }

    void pop()
    {
        if (isEmpty())
            return;
        auto temp = sp->next;
        delete sp;
        sp = temp;
    }

    bool isEmpty() const
    {
        return sp == NULL;
    }
};
