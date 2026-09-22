void insertAfter(Node *ptr, int el)
{
    auto newNode = new Node(el);
    newNode->next = ptr->next;
    ptr->next = newNode;
}

Node *freqHead = NULL;
Node *freqCurrent = NULL;
auto ptr = head;
while (ptr)
{
    int el = ptr->data;
    int count = 0;
    while (ptr && ptr->data == el)
    {
        ptr = ptr->next;
        count++;
    }
    if (!freqHead)
    {
        freqHead = new Node(count);
        freqCurrent = freqHead;
    }
    else
    {
        insertAfter(freqCurrent, count);
        freqCurrent = freqCurrent->next;
    }
}

ptr = head;

while (ptr)
{
    auto temp = ptr;
    int el = ptr->data;
    while (ptr && ptr->data == el)
        ptr = ptr->next;
    if (temp->next == ptr)
        continue;
    auto del = temp->next;
    temp->next = ptr;
    while (del != ptr)
    {
        auto temp2 = del;
        del = del->next;
        delete temp2;
    }
}