auto ptr = head;

while (ptr)
{
    if (ptr->data == DLL1.head->data)
    {
        auto temp = ptr, inner = DLL1.head;
        bool found = true;
        while (inner && ptr)
        {
            if (ptr->data != inner->data)
            {
                ptr = temp->next;
                found = false;
                break;
            }

            inner = inner->next;
            ptr = ptr->next;
        }

        found = found && (inner == nullptr);
        if (found)
        {
            if (temp == head)
            {
                while (head != ptr)
                {
                    auto temp2 = head;
                    head = head->next;
                    head->prev = nullptr;
                    delete temp2;
                }
                if (head)
                    head->prev = nullptr;
                else
                    tail = nullptr;
                return true;
            }

            auto prev = head;
            while (prev->next != temp)
                prev = prev->next;

            while (temp != ptr)
            {
                auto temp2 = temp;
                temp = temp->next;
                prev->next = temp;
                if (temp)
                    temp->prev = prev;

                if (temp2 == tail)
                {
                    tail = temp2->prev;
                    tail->next = nullptr;
                }
                delete temp2;
            }

            return true;
        }
    }
    else
    {
        ptr = ptr->next;
    }
}
