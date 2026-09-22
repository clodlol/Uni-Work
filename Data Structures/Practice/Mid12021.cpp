void InsertAfter(Node *ptr, char key)
{
    auto newNode = new Node(key);
    newNode->next = ptr->next;
    ptr->next = newNode;
}

void DeleteAfter(Node *ptr)
{
    auto temp = ptr->next;
    ptr->next = ptr->next->next;
    delete temp;
}

void EqualizeOccurrences(char key, int maxCount)
{
    if (!head)
        return;

    auto ptr = head;
    while (ptr)
    {
        if (ptr->data == key)
        {
            auto temp = ptr;
            int count = 0;
            while (ptr && ptr->data == key)
            {
                count++;
                ptr = ptr->next;
            }

            if (count > maxCount)
            {
                while (count > maxCount)
                {
                    DeleteAfter(temp);
                    count--;
                }
            }
            else if (count < maxCount)
            {
                while (count < maxCount)
                {
                    InsertAfter(temp, key);
                    count++;
                }
            }
        }
        else
        {
            ptr = ptr->next;
        }
    }
}