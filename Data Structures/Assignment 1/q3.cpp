#include <iostream>
using namespace std;

const int COURSE_LIMIT = 18;
const int COURSE_CRS = 3;

class StudentWaitlist;

class StudentNode
{
private:
    int id;
    float cgpa;
    int requestTime;
    int creditHoursEnrolled;
    int skipCount;
    StudentNode *next;

public:
    friend class StudentWaitlist;

    StudentNode(int _id, float _cgpa, int _requestTime, int _creditHoursEnrolled) : id{_id}, cgpa{_cgpa}, requestTime{_requestTime}, creditHoursEnrolled{_creditHoursEnrolled}, skipCount{0}, next{nullptr} {}

    bool eligible() const
    {
        return (creditHoursEnrolled + COURSE_CRS <= COURSE_LIMIT);
    }

    bool operator>(const StudentNode &other) const
    {
        return (cgpa == other.cgpa ? (requestTime < other.requestTime) : cgpa > other.cgpa);
    }

    bool operator<(const StudentNode &other) const
    {
        return !(*this > other) && !(*this == other);
    }

    bool operator==(const StudentNode &other) const
    {
        return (cgpa == other.cgpa && requestTime == other.requestTime);
    }
};

class StudentWaitlist
{
private:
    StudentNode *head;

    void clear()
    {
        if (!head)
            return;

        StudentNode *prev = nullptr;
        StudentNode *ptr = head;
        while (ptr)
        {
            if (prev)
                delete prev;

            prev = ptr;
            ptr = ptr->next;
        }

        delete prev;

        head = nullptr;
    }

public:
    StudentWaitlist() : head{nullptr} {}
    ~StudentWaitlist()
    {
        clear();
    }

    void display() const
    {
        StudentNode *ptr = head;
        while (ptr)
        {
            cout << ptr->id << "->";
            ptr = ptr->next;
        }
        cout << "END\n";
    }

    void insert(int studentId, float studentCgpa, int studentReqTime, int studentCrsEnrolled)
    {
        if (!head)
        {
            head = new StudentNode(studentId, studentCgpa, studentReqTime, studentCrsEnrolled);
            head->next = nullptr;
            return;
        }

        StudentNode *newNode = new StudentNode(studentId, studentCgpa, studentReqTime, studentCrsEnrolled);

        if (*head < *newNode)
        {
            newNode->next = head;
            head = newNode;

            return;
        }

        StudentNode *ptr = head;
        while (ptr->next)
        {
            if (*ptr->next < *newNode)
            {
                newNode->next = ptr->next;
                ptr->next = newNode;
                return;
            }

            ptr = ptr->next;
        }

        newNode->next = ptr->next;
        ptr->next = newNode;
    }

    void allocateSeat()
    {
        if (!head)
        {
            return;
        }

        StudentNode *prev = nullptr;
        StudentNode *ptr = head;

        bool eligibleFound = false;

        while (ptr)
        {
            if (!ptr->eligible())
            {
                ptr->skipCount++;

                if (ptr->skipCount < 3)
                {
                    prev = ptr;
                    ptr = ptr->next;
                    continue;
                }

                StudentNode *temp = ptr;
                if (temp == head)
                {
                    head = head->next;
                }

                if (prev)
                    prev->next = ptr->next;
                ptr = ptr->next;
                cout << "[AUTO DROP NOTIFICATION]: Student " << temp->id << " auto dropped from waitlist.\n";
                delete temp;

                continue;
            }

            eligibleFound = true;

            StudentNode *temp = ptr;
            if (temp == head)
            {
                head = head->next;
            }

            if (prev)
                prev->next = ptr->next;
            ptr = ptr->next;

            cout << "[ALLOCATION NOTIFICATION]: Student " << temp->id << " was allocated a seat.\n";
            delete temp;

            break;
        }

        if (!eligibleFound)
        {
            cout << "[UNALLOCATED NOTIFICATION]: No seat was successfully allocated in the waitlist.\n";
        }
    }

    void mergeWaitlists(StudentNode *otherHead)
    {
        if (!otherHead)
        {
            return;
        }

        if (!head)
        {
            head = otherHead;
            return;
        }

        while (otherHead && *head < *otherHead)
        {
            StudentNode *temp = otherHead;
            otherHead = otherHead->next;
            temp->next = head;
            head = temp;
        }

        StudentNode *ptr = head;
        StudentNode *otherPtr = otherHead;

        while (ptr->next && otherPtr)
        {
            if (*ptr->next < *otherPtr)
            {
                StudentNode *temp = otherPtr->next;

                otherPtr->next = ptr->next;
                ptr->next = otherPtr;

                otherPtr = temp;
                ptr = ptr->next;
                continue;
            }

            ptr = ptr->next;
        }

        if (otherPtr)
        {
            ptr->next = otherPtr;
        }
    }
};