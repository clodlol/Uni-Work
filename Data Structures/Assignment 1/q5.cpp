#include <iostream>
using namespace std;

struct ScheduleNode
{
    int startTime;
    int duration;
    int targetTemp;
    bool isLocked;
    ScheduleNode *prev;
    ScheduleNode *next;

    ScheduleNode(int _startTime, int _duration, int _targetTemp, bool _isLocked) : startTime{_startTime}, duration{_duration}, targetTemp{_targetTemp}, isLocked{_isLocked}, prev{nullptr}, next{nullptr} {}
};

class ScheduleList
{
private:
    ScheduleNode *head;
    ScheduleNode *cursor;
    int threshold;

public:
    ScheduleList() : head{nullptr}, cursor{nullptr}, threshold{10} {}

    void next()
    {
        if (cursor && cursor->next)
            cursor = cursor->next;
    }

    void prev()
    {
        if (cursor && cursor->prev)
            cursor = cursor->prev;
    }

    void insertSchedule(int sTime, int d, int tTemp, bool iLocked = false)
    {
        ScheduleNode *inserted = nullptr;

        if (!head)
        {
            head = new ScheduleNode(sTime, d, tTemp, iLocked);
            inserted = head;
            head->prev = nullptr;
            head->next = nullptr;
        }

        if (sTime <= head->startTime && !inserted)
        {
            ScheduleNode *newNode = new ScheduleNode(sTime, d, tTemp, iLocked);
            inserted = newNode;
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }

        ScheduleNode *ptr = head;

        while (ptr && !inserted)
        {
            if (!ptr->next)
            {
                ScheduleNode *newNode = new ScheduleNode(sTime, d, tTemp, iLocked);
                inserted = newNode;
                newNode->prev = ptr;
                newNode->next = nullptr;
                ptr->next = newNode;
                break;
            }

            if (ptr->next->startTime >= sTime)
            {
                ScheduleNode *newNode = new ScheduleNode(sTime, d, tTemp, iLocked);
                newNode->prev = ptr;
                newNode->next = ptr->next;
                newNode->next->prev = newNode;
                ptr->next = newNode;
                break;
            }

            ptr = ptr->next;
        }

        if (!inserted)
            return;

        ScheduleNode *prev = inserted->prev;
        ptr = inserted;
        ScheduleNode *next = inserted->next;

        while (ptr)
        {
            bool ptrMoved = false;

            if (!prev && !next)
            {
                break;
            }

            if (prev)
            {
                int prevEndtime = prev->startTime + prev->duration;
                if (prevEndtime - (ptr->startTime) > threshold)
                {
                    ScheduleNode *temp = prev;
                    int newStart = min(prev->startTime, ptr->startTime);
                    int newEnd = max(prev->startTime + prev->duration, ptr->startTime + ptr->duration);
                    ptr->startTime = newStart;
                    ptr->duration = newEnd - newStart;
                    ptr->targetTemp = floor((ptr->targetTemp + prev->targetTemp) / 2);
                    ptr->isLocked = prev->isLocked || ptr->isLocked;

                    if (prev == head)
                    {
                        head = ptr;
                        ptr->prev = nullptr;
                    }

                    if (prev->prev)
                    {
                        prev->prev->next = ptr;
                        ptr->prev = prev->prev;
                    }

                    prev = prev->prev;
                    ptrMoved = true;

                    delete temp;
                }
            }

            if (next && ptr)
            {
                int ptrEndTime = ptr->startTime + ptr->duration;
                if (ptrEndTime - next->startTime > threshold)
                {
                    ScheduleNode *temp = ptr;
                    int newStart = min(next->startTime, ptr->startTime);
                    int newEnd = max(next->startTime + next->duration, ptr->startTime + ptr->duration);
                    next->startTime = newStart;
                    next->duration = newEnd - newStart;
                    next->targetTemp = floor((ptr->targetTemp + next->targetTemp) / 2);
                    next->isLocked = next->isLocked || ptr->isLocked;

                    if (ptr == head)
                    {
                        head = next;
                        next->prev = nullptr;
                    }

                    if (ptr->prev)
                    {
                        ptr->prev->next = next;
                        next->prev = ptr->prev;
                    }

                    ptr = next;
                    next = next->next;
                    ptrMoved = true;

                    delete temp;
                }
            }

            if (!ptrMoved)
            {
                break;
            }
        }
    }

    void undoLast(int n)
    {
        if (!cursor)
            return;

        int count = 0;
        int skipped = 0;

        ScheduleNode *ptr = cursor->prev;

        while (ptr && count < n)
        {
            if (!ptr->isLocked)
            {
                ScheduleNode *temp = ptr;

                if (ptr->next)
                    ptr->next->prev = ptr->prev;

                if (ptr->prev)
                    ptr->prev->next = ptr->next;

                if (temp == head)
                {
                    if (temp->next)
                        head = temp->next;
                    else
                        head = nullptr;
                }

                ptr = ptr->prev;
                delete temp;
                count++;

                continue;
            }

            skipped++;
            ptr = ptr->prev;
        }

        cout << count << " / " << n << " nodes were deleted, " << skipped << " nodes were skipped.\n";
    }
};