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
};

struct Unit
{
    int unitID;
    int freeAt;
    int heapIndex;

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
};

template <typename T>
struct MaxHeap
{
    int capacity;
    int count;
    T *arr;

    MaxHeap(int cap) : capacity(cap), count(0), arr(new T[cap]) {}
    ~MaxHeap() { delete[] arr; }
    MaxHeap(const MaxHeap &other) = delete;
    MaxHeap &operator=(const MaxHeap &other) = delete;

    void insert(const T &d)
    {
        if (count + 1 > capacity)
            return;

        arr[count] = d;
        count++;

        int child = count - 1;
        int parent = (child - 1) / 2;
        while (child > parent)
        {
            if (arr[child] > arr[parent])
                swap(arr[child], arr[parent]);
            else
                break;

            child = parent;
            parent = (parent - 1) / 2;
        }
    }

    void remove()
    {
        if (count == 0)
            return;
        count--;
        arr[0] = arr[count];

        int e = 0;
        while (e < count)
        {
            int lc = e * 2 + 1;
            int rc = e * 2 + 2;

            if (lc >= count)
                break;

            if (rc >= count)
            {
                if (arr[e] < arr[lc])
                {
                    swap(arr[e], arr[lc]);
                    e = lc;
                    break;
                }
                else
                    break;
            }

            int maxc = max(arr[lc], arr[rc]) == arr[lc] ? lc : rc;

            if (arr[e] < arr[lc] || arr[e] < arr[rc])
                swap(arr[e], arr[maxc]);
            else
                break;

            e = maxc;
        }
    }
};

class ControlRoom
{
    MaxHeap<Incident> dispatchHeap;
    MaxHeap<Unit> unitHeap;

public:
    ControlRoom(int maxIncidents, int maxUnits) : dispatchHeap(maxIncidents), unitHeap(maxUnits) {}

    void reportIncident(int id, int sev, int arr, int due, int trv)
    {

        dispatchHeap.insert(Incident(id, sev, arr, due, trv));
    }
};