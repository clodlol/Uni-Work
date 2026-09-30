Node *prev = NULL;
auto ptr = head;
auto l = NULL;
auto e = NULL;
while (ptr != NULL)
{
    if (ptr->data > x)
    {
        prev = ptr;
        ptr = ptr->next;
        continue;
    }

    if (ptr->data < x)
    {
        prev->next = ptr->next;
        ptr->next = l->next;
        l->next = ptr;
        l = l->next;

        ptr = prev->next;
        continue;
    }

    prev->next = ptr->next;
    ptr->next = e->next;
    e->next = ptr;
    e = e->next;

    ptr = prev->next;
}