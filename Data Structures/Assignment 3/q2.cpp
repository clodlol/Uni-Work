#include <iostream>
using namespace std;

struct Incident
{
    int incidentID;
    int severity;
    int arrivalTime;
    int dueTime;
    int travel;
    int escalations;
    int heapIndex;
    int shedIndex;

    Incident()
        : incidentID(-1), severity(-1), arrivalTime(-1), dueTime(-1),
          travel(-1), escalations(-1), heapIndex(-1), shedIndex(-1) {}
    Incident(int id, int sev, int arr, int due, int trv)
        : incidentID(id), severity(sev), arrivalTime(arr), dueTime(due),
          travel(trv), escalations(0), heapIndex(-1), shedIndex(-1) {}

    int effectiveSeverity() const
    {
        int s = severity + escalations;
        return s > 5 ? 5 : s;
    }

    bool operator>(const Incident &other) const
    {
        // Is *this more urgent than other?

        if (effectiveSeverity() > other.effectiveSeverity())
            return true;
        else if (effectiveSeverity() < other.effectiveSeverity())
            return false;

        if (dueTime < other.dueTime)
            return true;
        else if (dueTime > other.dueTime)
            return false;

        if (arrivalTime < other.arrivalTime)
            return true;
        else if (arrivalTime > other.arrivalTime)
            return false;

        return incidentID < other.incidentID;
    }

    bool operator<(const Incident &other) const
    {
        // Is *this less urgent than other?

        return other > *this;
    }

    bool operator==(const Incident &other) const
    {
        return effectiveSeverity() == other.effectiveSeverity() &&
               dueTime == other.dueTime &&
               arrivalTime == other.arrivalTime &&
               incidentID == other.incidentID;
    }

    bool operator!=(const Incident &other) const
    {
        return !(*this == other);
    }

    void print() const
    {
        cout << incidentID << "(S" << severity << ") ";
    }
};

struct Unit
{
    int unitID;
    int freeAt;
    int heapIndex;

    Unit() : unitID(-1), freeAt(-1), heapIndex(-1) {}
    Unit(int id, int free)
        : unitID(id), freeAt(free), heapIndex(-1) {}

    bool operator>(const Unit &other) const
    {
        if (freeAt < other.freeAt)
            return true;
        else if (freeAt > other.freeAt)
            return false;

        return unitID < other.unitID;
    }

    bool operator<(const Unit &other) const
    {
        return other > *this;
    }

    bool operator==(const Unit &other) const
    {
        return freeAt == other.freeAt &&
               unitID == other.unitID;
    }

    bool operator!=(const Unit &other) const
    {
        return !(*this == other);
    }
};

template <typename T>
struct MaxHeap
{
    int capacity;
    int count;
    T *arr;

    MaxHeap(int cap) : capacity(cap), count(0), arr(new T[cap]) {}
    virtual ~MaxHeap() { delete[] arr; }
    MaxHeap(const MaxHeap &other) : capacity(other.capacity), count(other.count), arr(new T[other.capacity])
    {
        *this = other;
    }
    MaxHeap &operator=(const MaxHeap &other)
    {
        if (this == &other)
            return *this;

        delete[] arr;
        count = other.count;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < other.count; ++i)
            arr[i] = other.arr[i];

        return *this;
    }

    virtual void placed(int i) {} // Methods to update heap and shed indices in Incident and Unit classes
    virtual void removed(T &x) {}

    void siftUp(int idx)
    {
        int child = idx;
        int parent = (child - 1) / 2;

        while (child > parent)
        {
            if (arr[child] > arr[parent])
            {
                swap(arr[child], arr[parent]);
                placed(child);
                placed(parent);
            }
            else
                break;

            child = parent;
            parent = (parent - 1) / 2;
        }
    }

    void siftDown(int idx)
    {
        int parent = idx;
        while (parent < count)
        {
            int leftChild = parent * 2 + 1;
            int rightChild = parent * 2 + 2;

            if (leftChild >= count)
                break;

            if (rightChild >= count)
            {
                if (arr[parent] < arr[leftChild])
                {
                    swap(arr[parent], arr[leftChild]);
                    placed(parent);
                    placed(leftChild);
                    parent = leftChild;
                    break;
                }
                else

                    break;
            }

            int maxChild = max(arr[leftChild], arr[rightChild]) == arr[leftChild] ? leftChild : rightChild;
            if (arr[parent] < arr[leftChild] || arr[parent] < arr[rightChild])
            {
                swap(arr[parent], arr[maxChild]);
                placed(parent);
                placed(maxChild);
            }
            else
                break;

            parent = maxChild;
        }
    }

    void insert(const T &d)
    {
        if (count + 1 > capacity)
            return;

        arr[count] = d;
        placed(count);
        count++;

        siftUp(count - 1);
    }

    void remove()
    {
        if (count == 0)
            return;
        count--;
        arr[0] = arr[count];
        placed(0);

        siftDown(0);
    }

    virtual bool exists(const T &obj) const
    {
        for (int i = 0; i < count; ++i)
            if (arr[i] == obj)
                return true;

        return false;
    }

    bool full() const { return count == capacity; }

    const T &top() const { return arr[0]; }

    bool empty() const { return count == 0; }
};

struct IncidentHeap : MaxHeap<Incident>
{
    int slot[1000];

    IncidentHeap(int cap) : MaxHeap<Incident>(cap), slot{-1} {}
    void placed(int i) override
    {
        arr[i].heapIndex = i;
        slot[arr[i].incidentID] = arr[i].heapIndex;
    }
    void removed(Incident &x) override
    {
        x.heapIndex = -1;
        slot[x.incidentID] = -1;
    }

    bool exists(const Incident &obj) const override
    {
        return slot[obj.incidentID] != -1;
    }
};

struct UnitHeap : MaxHeap<Unit>
{
    UnitHeap(int cap) : MaxHeap<Unit>(cap) {}
    void placed(int i) override { arr[i].heapIndex = i; }
    void removed(Unit &x) override { x.heapIndex = -1; }

    bool exists(const Unit &obj) const override
    {
        for (int i = 0; i < count; ++i)
            if (arr[i].unitID == obj.unitID)
                return true;

        return false;
    }
};

class ControlRoom
{
    IncidentHeap dispatchHeap;
    UnitHeap unitHeap;

    void printHeapArray() const
    {
        cout << "Heap array: ";
        for (int i = 0; i < dispatchHeap.count; ++i)
            dispatchHeap.arr[i].print();
        cout << "\n";
    }

    void printHeapLevels() const
    {
        printHeapArray();
        int left = 0, level = 0;
        for (int size = 1; left < dispatchHeap.count; size *= 2)
        {
            cout << "Level " << level++ << ": ";
            int currentBound = min(left + size, dispatchHeap.count);
            while (left < currentBound)
            {
                dispatchHeap.arr[left].print();
                left++;
            }
            cout << "\n";
        }
    }

public:
    ControlRoom(int maxIncidents, int maxUnits) : dispatchHeap(maxIncidents), unitHeap(maxUnits) {}

    void reportIncident(int incidentID, int severity, int arrivalTime, int dueTime, int travel)
    {
        Incident inc = Incident(incidentID, severity, arrivalTime, dueTime, travel);

        if (incidentID < 1 || incidentID > 999)
        {
            cout << "ERROR [InvalidIncident]: ID " << incidentID
                 << " is out of range (must be 1 to 999)." << endl;
            return;
        }
        if (dispatchHeap.exists(inc))
        {
            cout << "ERROR [InvalidIncident]: ID " << incidentID
                 << " is already used." << endl;
            return;
        }
        if (severity < 1 || severity > 5)
        {
            cout << "ERROR [InvalidIncident]: Incident " << incidentID
                 << " has severity " << severity << " (must be 1 to 5)." << endl;
            return;
        }
        if (arrivalTime < 0)
        {
            cout << "ERROR [InvalidIncident]: Incident " << incidentID
                 << " has negative arrival time " << arrivalTime << "." << endl;
            return;
        }
        if (dueTime <= arrivalTime)
        {
            cout << "ERROR [InvalidIncident]: Incident " << incidentID
                 << " has due time " << dueTime << ", which is not after arrival time "
                 << arrivalTime << "." << endl;
            return;
        }
        if (travel <= 0)
        {
            cout << "ERROR [InvalidIncident]: Incident " << incidentID
                 << " has travel time " << travel << " (must be greater than 0)." << endl;
            return;
        }

        dispatchHeap.insert(inc);
    }

    void printHeap() const
    {
        printHeapArray();
        printHeapLevels();
    }

    void addUnit(int unitID, int freeAt)
    {
        Unit unit = Unit(unitID, freeAt);

        if (unitID <= 0)
        {
            cout << "ERROR [InvalidUnit]: Unit ID " << unitID
                 << " is not positive." << endl;
            return;
        }
        if (unitHeap.exists(unit))
        {
            cout << "ERROR [InvalidUnit]: Unit " << unitID
                 << " already exists." << endl;
            return;
        }
        if (freeAt < 0)
        {
            cout << "ERROR [InvalidUnit]: Unit " << unitID
                 << " has negative free time " << freeAt << "." << endl;
            return;
        }
        if (unitHeap.full())
        {
            cout << "ERROR [PoolFull]: Cannot add unit " << unitID
                 << ", the unit pool is full." << endl;
            return;
        }

        unitHeap.insert(unit);
    }

    void dispatch(int now)
    {
        Incident t = dispatchHeap.top();
        Unit u = unitHeap.top();
        int start = max(now, u.freeAt);
        int eta = start + t.travel;

        if (eta > t.dueTime)
        {
            dispatchHeap.remove();
            cout << "ERROR [DeadlineMissed]: Incident " << t.incidentID
                 << " cannot be reached by due time " << t.dueTime
                 << " (best ETA " << eta << " by Unit " << u.unitID << ")." << endl;
            return;
        }

        dispatchHeap.remove();
        unitHeap.remove();
        u.freeAt = start + 2 * t.travel;
        unitHeap.insert(u);
        cout << "Dispatched: Unit " << u.unitID << " -> Incident " << t.incidentID
             << " (ETA " << eta << ", due " << t.dueTime << ")." << endl;
    }

    void escalate(int incidentId)
    {
        if (incidentId < 1 || incidentId > 999 || dispatchHeap.slot[incidentId] == -1)
        {
            cout << "ERROR [IncidentNotFound]: No incident with ID "
                 << incidentId << " on the board." << endl;
            return;
        }

        Incident &inc = dispatchHeap.arr[dispatchHeap.slot[incidentId]];
        if (inc.effectiveSeverity() == 5)
        {
            cout << "ERROR [AlreadyCritical]: Incident " << incidentId
                 << " is already at severity 5." << endl;
            return;
        }

        inc.escalations++;
        int newSev = inc.effectiveSeverity();
        dispatchHeap.siftUp(inc.heapIndex);
        cout << "Incident " << incidentId << " escalated to severity " << newSev << "." << endl;
    }

    void cancel(int incidentId)
    {
        if (incidentId < 1 || incidentId > 999 || dispatchHeap.slot[incidentId] == -1)
        {
            cout << "ERROR [IncidentNotFound]: No incident with ID "
                 << incidentId << " on the board." << endl;
            return;
        }

        int incIdx = dispatchHeap.slot[incidentId];

        dispatchHeap.slot[incidentId] = -1; // Not in heap anymore
        cout << "Incident " << incidentId << " cancelled." << endl;

        if (incIdx == dispatchHeap.count - 1)
        {
            dispatchHeap.count--;
            return;
        }

        dispatchHeap.arr[incIdx] = dispatchHeap.arr[dispatchHeap.count - 1];
        dispatchHeap.placed(incIdx);
        dispatchHeap.count--;
        dispatchHeap.siftDown(incIdx);
        dispatchHeap.siftUp(incIdx);
    }

    void ageAll(int now)
    {
        for (int i = 0; i < dispatchHeap.count; ++i)
        {
            int target = min((now - dispatchHeap.arr[i].arrivalTime / 30), 5 - dispatchHeap.arr[i].severity);
            if (target > dispatchHeap.arr[i].escalations)
                dispatchHeap.arr[i].escalations = target;
        }
    }
};

int main()
{
    ControlRoom obj(10, 10);
    obj.reportIncident(1, 5, 101, 1001, 100);
    obj.reportIncident(2, 5, 101, 1001, 100);
    obj.reportIncident(3, 5, 101, 1001, 100);
    obj.reportIncident(4, 5, 101, 1001, 100);
    obj.reportIncident(5, 5, 101, 1001, 100);
    obj.reportIncident(6, 5, 101, 1001, 100);
    obj.printHeap();
    return 0;
}