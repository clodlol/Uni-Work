#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T val;
    Node<T> *next;
    Node(const T &p_val) : val{p_val}, next{NULL} {}
    Node(const T &p_val, Node<T> *p_next) : val{p_val}, next{p_next} {}
};

template <typename T>
class Stack
{
    int count;
    Node<T> *sp;

    void reverseStack()
    {
        Node<T> *prev = NULL;
        auto ptr = sp;
        while (sp != NULL)
        {
            auto temp = sp->next;
            sp->next = prev;
            prev = sp;
            sp = temp;
        }
        sp = prev;
    }

public:
    Stack() : count{0}, sp{NULL} {}
    ~Stack()
    {
        clear();
    }

    Stack(const Stack &other) : count{0}, sp{NULL}
    {
        auto otherSp = other.sp;
        while (otherSp != NULL)
        {
            this->push(otherSp->val);
            otherSp = otherSp->next;
        }
        reverseStack();
        count = other.count;
    }

    Stack &operator=(const Stack &other)
    {
        if (this == &other)
            return *this;

        Stack temp = other;
        swap(count, temp.count);
        swap(sp, temp.sp);
        return *this;
    }

    bool isEmpty() const { return count == 0; }

    T pop()
    {
        if (isEmpty())
            return T{};
        auto data = sp->val;
        auto temp = sp;
        sp = sp->next;
        count--;
        delete temp;
        return data;
    }

    void push(const T &data)
    {
        auto newNode = new Node<T>(data);
        newNode->next = sp;
        sp = newNode;
        count++;
    }

    T top() const
    {
        if (isEmpty())
            return T{};
        return sp->val;
    }

    void clear()
    {
        while (sp != NULL)
        {
            auto temp = sp;
            sp = sp->next;
            delete temp;
        }
        count = 0;
    }
};

class HistogramAnalyzer
{
public:
    int largestRectangleArea(int heights[], int size)
    {
        Stack<int> stack;
        int ans = 0;

        int *right = new int[size];
        int *left = new int[size];
        for (int i = size - 1; i >= 0; --i)
        {
            while (!stack.isEmpty() && heights[stack.top()] >= heights[i])
            {
                stack.pop();
            }
            right[i] = stack.isEmpty() ? size : stack.top();
            stack.push(i);
        }
        stack.clear();
        for (int i = 0; i < size; ++i)
        {
            while (!stack.isEmpty() && heights[stack.top()] >= heights[i])
            {
                stack.pop();
            }
            left[i] = stack.isEmpty() ? -1 : stack.top();
            stack.push(i);
        }

        for (int i = 0; i < size; ++i)
        {
            ans = max(ans, heights[i] * (right[i] - left[i] - 1));
        }

        delete[] right;
        delete[] left;
        return ans;
    }
};