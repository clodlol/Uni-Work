#include <iostream>
#include <string>
using namespace std;

struct Coach
{
    string coachId;
    int weightTons;
    int slot;
    int loops;

    Coach() : coachId{""}, weightTons{0}, slot{0}, loops{0} {}
    Coach(const string &p_coachId, int p_weightTons, int p_slot) : coachId{p_coachId}, weightTons{p_weightTons}, slot{p_slot}, loops{0} {}
};
struct CoachNode
{
    Coach data;
    CoachNode *next;

    CoachNode() : data{}, next{nullptr} {}
    CoachNode(const Coach &p_coach) : data{p_coach}, next{nullptr} {}
};

class CoachQueue
{
private:
    CoachNode *front;
    CoachNode *rear;

    void clear()
    {
        auto ptr = front;
        while (ptr != nullptr)
        {
            auto temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
        front = rear = nullptr;
    }

public:
    CoachQueue() : front{nullptr}, rear{nullptr} {}
    ~CoachQueue()
    {
        clear();
    }

    CoachQueue &operator=(const CoachQueue &other)
    {
        if (this == &other)
            return *this;

        auto ptr = other.front;
        clear();
        while (ptr != nullptr)
        {
            if (!front)
            {
                front = rear = new CoachNode(ptr->data);
                ptr = ptr->next;
                continue;
            }
            rear->next = new CoachNode(ptr->data);
            rear = rear->next;
            ptr = ptr->next;
        }

        return *this;
    }

    CoachQueue(const CoachQueue &other) : front{nullptr}, rear{nullptr}
    {
        *this = other;
    }

    void enqueue(const Coach &coach)
    {
        rear = (front == nullptr) ? (front = new CoachNode(coach)) : (rear->next = new CoachNode(coach));
    }

    Coach dequeue()
    {
        if (!front)
            return Coach{};
        auto temp = front;
        auto retVal = front->data;
        front = front->next;
        delete temp;
        return retVal;
    }

    const Coach &peek() const
    {
        return front->data;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }
};

class CoachStack
{
private:
    CoachNode *sp;
    int capacity;
    int count;

    void clear()
    {
        auto ptr = sp;
        while (ptr != nullptr)
        {
            auto temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
        sp = nullptr;
        count = 0;
    }

public:
    CoachStack() : sp{nullptr}, capacity{0}, count{0} {}
    CoachStack(int p_capacity) : sp{nullptr}, capacity{p_capacity}, count{0} {}
    ~CoachStack()
    {
        clear();
    }

    CoachStack &operator=(const CoachStack &other)
    {
        if (this == &other)
            return *this;

        auto ptr = other.sp;
        clear();
        CoachNode *tail = nullptr;
        while (ptr != nullptr)
        {
            auto newNode = new CoachNode(ptr->data);
            if (!sp)
                sp = tail = newNode;
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
            ptr = ptr->next;
        }

        count = other.count;
        capacity = other.capacity;
        return *this;
    }

    CoachStack(const CoachStack &other) : sp{nullptr}
    {
        *this = other;
    }

    bool push(const Coach &coach, bool verbose = true)
    {
        if (count == capacity)
        {
            if (verbose)
                cout << "ERROR [SidingFull]: Siding is full, coach " << coach.coachId << " refused.\n";
            return false;
        }

        if (sp && sp->data.weightTons < coach.weightTons)
        {
            if (verbose)
                cout << "ERROR [TooHeavy]: Coach " << coach.coachId << " (" << coach.weightTons << "t) is heavier than siding top " << sp->data.coachId << " (" << sp->data.weightTons << "t).\n";
            return false;
        }

        if (!sp)
        {
            sp = new CoachNode(coach);
            count++;
            return true;
        }

        auto newNode = new CoachNode(coach);
        newNode->next = sp;
        sp = newNode;
        count++;

        return true;
    }

    void forcePush(const Coach &coach)
    {
        auto n = new CoachNode(coach);
        n->next = sp;
        sp = n;
        count++;
    }

    Coach pop()
    {
        if (!sp)
            return Coach{};
        auto temp = sp;
        auto retVal = sp->data;
        sp = sp->next;
        delete temp;
        count--;
        return retVal;
    }

    const Coach &top() const
    {
        return sp->data;
    }

    bool isEmpty() const
    {
        return sp == nullptr;
    }
};

class RailwayManager
{
private:
    CoachQueue entryLine;
    CoachStack siding;
    CoachQueue platform;
    CoachQueue Track2;

    int platformExpectedSlot;

public:
    RailwayManager() : siding{3}, platformExpectedSlot{1} {}

    bool arriveCoach(const string &coachId, int weightTons, int slot)
    {
        if (coachId.size() <= 0 || weightTons <= 0 || slot <= 0)
        {
            cout << "ERROR [Invalid Coach]: Invalid coach id, weight or slot.\n";
            return false;
        }

        CoachQueue temp;
        bool valid = true;
        while (!entryLine.isEmpty())
        {
            if (entryLine.peek().slot == slot || entryLine.peek().coachId == coachId)
                valid = false;
            temp.enqueue(entryLine.dequeue());
        }

        entryLine = temp;
        if (!valid)
        {
            cout << "ERROR [Invalid Coach]: Slot or coach id already taken.\n";
            return false;
        }

        entryLine.enqueue(Coach{coachId, weightTons, slot});
        return true;
    }

    bool joinPlatform(const Coach &coach)
    {
        if (coach.slot != platformExpectedSlot)
        {
            cout << "ERROR [Out of Order]: Coach attempted to board platform out of order.\n";
            return false;
        }

        platform.enqueue(coach);
        platformExpectedSlot++;
        return true;
    }

    bool shunt()
    {
        int goArounds = 0;
        while (!entryLine.isEmpty())
        {
            if (entryLine.peek().slot != platformExpectedSlot)
            {
                auto front = entryLine.dequeue();
                bool pushed = siding.push(front, false);
                if (!pushed && front.loops == 0)
                {
                    front.loops = 1;
                    goArounds++;
                    entryLine.enqueue(front);
                }
                else if (!pushed && front.loops == 1)
                {
                    cout << "ERROR [Yard Jam]: Yard jammed due to coach " << front.coachId << ".\n";
                    showStatus();
                    return false;
                }

                continue;
            }

            if (!joinPlatform(entryLine.dequeue()))
                return false;

            while (!siding.isEmpty() && siding.top().slot == platformExpectedSlot)
                if (!joinPlatform(siding.pop()))
                    return false;
        }

        if (!siding.isEmpty())
        {
            cout << "ERROR [Deadlock]: Siding non empty due to top coach " << siding.top().coachId << ".\n";
            showStatus();
            return false;
        }

        cout << "Train formed. Go-arounds: " << goArounds << "\n";
        showStatus();
        return true;
    }

    void turnAround()
    {
        if (platform.isEmpty())
            return;

        auto temp = platform.dequeue();
        turnAround();
        platform.enqueue(temp);
    }

    void splitAfter(const string &coachId)
    {
        CoachQueue temp;
        while (!platform.isEmpty() && platform.peek().coachId != coachId)
            temp.enqueue(platform.dequeue());

        if (!platform.isEmpty() && platform.peek().coachId == coachId)
        {
            temp.enqueue(platform.dequeue());
            Track2 = platform;
            platform = temp;
        }
        else
        {
            platform = temp;
            cout << "ERROR [Split error]: Cannot find " << coachId << " in platform queue.\n";
        }
    }

    void showStatus()
    {
        CoachQueue temp;

        cout << "Entry Line: <- ";
        while (!entryLine.isEmpty())
        {
            cout << "(" << entryLine.peek().coachId << ", " << entryLine.peek().weightTons << "t, " << entryLine.peek().slot << ") ";
            temp.enqueue(entryLine.dequeue());
        }
        cout << " <- \n";
        entryLine = temp;

        temp = CoachQueue{};

        cout << "Platform: <- ";
        while (!platform.isEmpty())
        {
            cout << "(" << platform.peek().coachId << ", " << platform.peek().weightTons << "t, " << platform.peek().slot << ") ";
            temp.enqueue(platform.dequeue());
        }
        cout << " <- \n";
        platform = temp;

        auto temp2 = CoachStack{3};

        cout << "Siding: ^ ";
        while (!siding.isEmpty())
        {
            cout << "(" << siding.top().coachId << ", " << siding.top().weightTons << "t, " << siding.top().slot << ") ";
            temp2.forcePush(siding.pop());
        }
        cout << "\n";
        while (!temp2.isEmpty())
            siding.forcePush(temp2.pop());

        temp = CoachQueue{};

        cout << "Track 2: <- ";
        while (!Track2.isEmpty())
        {
            cout << "(" << Track2.peek().coachId << ", " << Track2.peek().weightTons << "t, " << Track2.peek().slot << ") ";
            temp.enqueue(Track2.dequeue());
        }
        cout << " <- \n";
        Track2 = temp;
    }
};

int main()
{
    cout << "===== Part A: arrival validation =====\n";
    {
        RailwayManager m;
        m.arriveCoach("A", 30, 2);
        m.arriveCoach("B", 0, 3);
        m.arriveCoach("C", 20, 2);
        m.arriveCoach("A", 10, 5);
        m.arriveCoach("", 10, 6);
        m.arriveCoach("D", 10, 0);
        m.showStatus();
    }

    cout << "\n===== Part A: siding rules (standalone) =====\n";
    {
        CoachStack s{3};
        s.push(Coach{"A", 30, 1});
        s.push(Coach{"B", 50, 2});
        s.push(Coach{"C", 30, 3});
        s.push(Coach{"D", 20, 4});
        s.push(Coach{"E", 10, 5});
        cout << "top: " << s.top().coachId << "\n";
    }

    cout << "\n===== Part A: platform rule =====\n";
    {
        RailwayManager m;
        m.joinPlatform(Coach{"X", 10, 2});
        m.joinPlatform(Coach{"X", 10, 1});
        m.joinPlatform(Coach{"Y", 10, 2});
        m.showStatus();
    }

    cout << "\n===== Example 1 (no conflicts) =====\n";
    {
        RailwayManager m;
        m.arriveCoach("A", 50, 3);
        m.arriveCoach("B", 40, 1);
        m.arriveCoach("C", 30, 2);
        m.arriveCoach("D", 20, 5);
        m.arriveCoach("E", 10, 4);
        m.shunt();
    }

    cout << "\n===== Example 2 (one go-around) + Part C =====\n";
    {
        RailwayManager m;
        m.arriveCoach("A", 30, 2);
        m.arriveCoach("B", 50, 3);
        m.arriveCoach("C", 40, 1);
        m.shunt();

        cout << "-- turnAround --\n";
        m.turnAround();
        m.showStatus();

        cout << "-- splitAfter(A) --\n";
        m.splitAfter("A");
        m.showStatus();

        cout << "-- splitAfter(Z) --\n";
        m.splitAfter("Z");
        m.showStatus();
    }

    cout << "\n===== Example 3 (yard jam) =====\n";
    {
        RailwayManager m;
        m.arriveCoach("A", 30, 3);
        m.arriveCoach("B", 50, 4);
        m.arriveCoach("C", 40, 2);
        m.arriveCoach("D", 10, 1);
        m.shunt();
    }

    cout << "\n===== Example 4 (deadlock) =====\n";
    {
        RailwayManager m;
        m.arriveCoach("A", 30, 3);
        m.arriveCoach("B", 50, 2);
        m.arriveCoach("C", 20, 4);
        m.arriveCoach("D", 10, 1);
        m.shunt();
    }

    cout << "\n===== Repeat shunt after more arrivals =====\n";
    {
        RailwayManager m;
        m.arriveCoach("A", 10, 1);
        m.arriveCoach("B", 10, 2);
        m.shunt();
        m.arriveCoach("C", 10, 3);
        m.shunt();
    }

    cout << "\n===== Empty yard =====\n";
    {
        RailwayManager m;
        m.shunt();
        m.turnAround();
        m.splitAfter("A");
        m.showStatus();
    }

    return 0;
}