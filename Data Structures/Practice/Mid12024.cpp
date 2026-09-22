#include <climits>

void removeLongestSequence(Node *head)
{

    Node *longest = nullptr;
    int largest = INT_MIN;
    int count = 0;
    auto ptr = head;
    while (ptr)
    {
        if (ptr->data == ch)
        {
            auto temp = ptr;
            while (ptr && ptr->data == ch)
            {
                count++;
                if (count > largest)
                {
                    largest = count;
                    longest = temp;
                }
                ptr = ptr->next;
            }
            count = 0;
        }
        else
        {
            count = 0;
        }
    }

    while (longest == head && longest->data == ch)
    {
        auto temp = longest;
        longest = longest->next;
        head = longest;
        delete temp;
    }

    if (!longest || longest->data != ch)
        return;

    auto prev = head;
    while (prev->next != longest)
        prev = prev->next;
    ptr = longest;
    while (ptr->data == ch)
    {
        auto temp = ptr;
        ptr = ptr->next;
        prev->next = ptr;
        delete temp;
    }
}