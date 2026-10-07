#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node* next;
    Node(int data): val{data}, next{NULL} {};
};

Node* reverse(Node* head, Node* prev = NULL)
{
    if(!head)
        return prev;
    
    auto temp = head->next;
    head->next = prev;
    return reverse(temp, head);
}

int main()
{

}