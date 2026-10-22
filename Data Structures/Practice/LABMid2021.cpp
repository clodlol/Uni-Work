#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node *next;
    Node(int p_val) : val{p_val}, next{NULL} {}
};

Node *getPartitionedList(Node *&head, int x)
{
    if (!head)
        return NULL;

    Node *lh = NULL, *lt = NULL, *eh = NULL, *et = NULL, *gh = NULL, *gt = NULL;
    auto ptr = head;
    while (ptr != NULL)
    {
        auto temp = ptr->next;
        if (ptr->val > x)
        {
            if (gh == NULL)
            {
                gh = gt = ptr;
            }
            else
            {
                ptr->next = gt->next;
                gt->next = ptr;
                gt = ptr;
            }

            ptr = temp;
        }
        else if (ptr->val < x)
        {
            if (lh == NULL)
            {
                lh = lt = ptr;
            }
            else
            {
                ptr->next = lt->next;
                lt->next = ptr;
                lt = ptr;
            }

            ptr = temp;
        }
        else
        {
            if (eh == NULL)
            {
                eh = et = ptr;
            }
            else
            {
                ptr->next = et->next;
                et->next = ptr;
                et = ptr;
            }

            ptr = temp;
        }
    }

    return head;
}