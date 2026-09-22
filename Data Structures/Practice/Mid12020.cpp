auto ptr = head;
Node *prev = NULL;

void searchAndPromote(int key)
{

    while (ptr)
    {
        if (ptr->key == key)
        {
            if (ptr == head)
            {
                prev = ptr;
                ptr = ptr->next;
                continue;
            }

            auto temp = ptr->next;
            if (head->key == key)
            {
                auto insertAfter = head;
                while (insertAfter->next->key == key)
                    insertAfter = insertAfter->next;
                if (prev)
                    prev->next = ptr->next;
                ptr->next = insertAfter->next;
                insertAfter->next = ptr;
            }
            else
            {
                if (prev)
                    prev->next = ptr->next;
                ptr->next = head;
                head = ptr;
            }

            ptr = temp;
        }
        else
        {
            prev = ptr;
            ptr = ptr->next;
        }
    }
}
