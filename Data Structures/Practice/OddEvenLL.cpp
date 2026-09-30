// handle 0 1 2 edgecases later
auto ptr = head;
auto next = head->next;
auto secHead = next;
auto nextFirst = next->next;
auto nextSec = (nextFirst ? nextFirst->next : nullptr);
while (nextFirst)
{
    ptr->next = nextFirst;
    next->next = nextSec;
    ptr = nextFirst;
    next = nextSec;
    if (nextFirst->next)
        nextFirst = nextFirst->next->next;
    else
        nextFirst = nullptr;

    nextSec = (nextFirst ? nextFirst->next : nullptr);
}

ptr->next = nextFirst;
if (next)
    next->next = nextSec;

ptr = head;
while (ptr->next)
    ptr = ptr->next;
ptr->next = secHead;