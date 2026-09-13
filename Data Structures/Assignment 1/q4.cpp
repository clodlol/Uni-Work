#include <iostream>
using namespace std;

class BotList;

struct BotNode
{
    int botId;
    int activeLoad;
    int maxLoad;
    bool isResting;
    int chatsHandledSinceRest;
    int lapsPassedWhileResting;
    BotNode *next;

    BotNode(int _botId, int _maxLoad) : botId{_botId}, activeLoad{0}, maxLoad{_maxLoad}, isResting{false}, chatsHandledSinceRest{0}, lapsPassedWhileResting{0} {}
};

class BotList
{
private:
    int threshold;
    BotNode *current;

public:
    BotList() : threshold{5}, current{nullptr} {}

    void overrideCurrent(BotNode *newCurrent)
    {
        current = newCurrent;
    }

    void display() const
    {
        if (!current)
        {
            return;
        }

        BotNode *ptr = current;
        do
        {
            cout << ptr->botId << " | " << ptr->activeLoad << " chats\n";
            ptr = ptr->next;
        } while (ptr != current);

        cout << "END\n";
    }

    void addBot(int bId, int mLoad)
    {
        if (!current)
        {
            current = new BotNode(bId, mLoad);
            current->next = current;
            return;
        }

        BotNode *newNode = new BotNode(bId, mLoad);
        newNode->next = current->next;
        current->next = newNode;
    }

    void assignQuery()
    {
        if (!current)
        {
            return;
        }

        BotNode *start = current;
        bool assigned = false;

        do
        {
            if (current->isResting || current->activeLoad == current->maxLoad)
            {
                current = current->next;
                continue;
            }

            current->activeLoad++;
            current->chatsHandledSinceRest++;
            assigned = true;
            break;

        } while (current != start);

        if (!assigned)
        {
            cout << "[SYSTEM OVERLOAD] - Query queued.\n";
        }
        else
        {
            current = current->next;
        }
    }

    void rotateCycle()
    {
        if (!current)
        {
            return;
        }

        BotNode *ptr = current;

        do
        {
            if (ptr->chatsHandledSinceRest >= threshold)
            {
                ptr->isResting = true;
            }

            if (ptr->isResting)
            {
                ptr->lapsPassedWhileResting++;
            }

            if (ptr->lapsPassedWhileResting == 2)
            {
                ptr->isResting = false;
                ptr->chatsHandledSinceRest = 0;
                ptr->lapsPassedWhileResting = 0;
            }

            ptr = ptr->next;

        } while (ptr != current);
    }

    void crashBot(int bId)
    {
        if (!current)
        {
            return;
        }

        BotNode *toCrash = nullptr;
        BotNode *ptr = current;

        do
        {
            if (ptr->botId == bId)
            {
                toCrash = ptr;
                break;
            }

            ptr = ptr->next;
        } while (ptr != current);

        if (!toCrash)
        {
            return;
        }

        int chatsToForward = toCrash->activeLoad;
        ptr = toCrash->next;

        while (chatsToForward >= 0)
        {
            if (ptr == toCrash)
            {
                cout << chatsToForward << " chats unassigned.\n";
                break;
            }

            int capacity = ptr->maxLoad - ptr->activeLoad;
            ptr->activeLoad += min(capacity, chatsToForward);
            chatsToForward -= capacity;
            ptr = ptr->next;
        }

        while (ptr->next != toCrash)
            ptr = ptr->next;

        if (current == toCrash)
        {
            if (toCrash != toCrash->next)
            {
                current = toCrash->next;
            }
            else
            {
                current = nullptr;
            }
        }

        ptr->next = toCrash->next;
        delete toCrash;
    }
};

int main()
{
    BotList ring1;
    ring1.addBot(1, 5);
    ring1.addBot(2, 4);
    ring1.addBot(3, 3);

    ring1.display();

    BotList ring2;

    return 0;
}
