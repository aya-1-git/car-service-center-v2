#include "Center.h"
#include <climits>

// Shared helpers used by the simulation steps (2.7, 2.10).

WaitingQueue& Center::getWaitList(UnitType type)
{
    if (type == EU) return waitEB;
    if (type == WU) return waitWB;
    return waitMB;                       // MU (DU never has a waiting list)
}

// Diagnosis result: 1 to 3 random services (MU / EU / WU) + random SS/FS.
void Center::assignRandomServices(Car* c)
{
    int n = randInt(1, 3);
    for (int i = 0; i < n; i++)
    {
        Service* s = new Service;
        s->type = static_cast<UnitType>(randInt(MU, WU));
        s->duration = randInt(1, 5);
        c->getServiceList().enqueue(s);
    }
    c->setSeqType(chance(50) ? SS : FS);
}

// Puts the car in the WAIT list of its NEXT service (used by 2.10: "waiting for the next service").
// Convention: the FRONT of serviceList is the next service.
//  - SS: front service as is.
//  - FS: pick the service whose waiting list has the minimum total service time, bring it to the front.
void Center::moveToWaitList(Car* c)
{
    CountQueue<Service*>& sl = c->getServiceList();
    int n = sl.GetCount();
    if (n == 0)
        return;                          // nothing left (caller should send the car to FNSH)

    if (c->getSeqType() == FS && n > 1)
    {
        Service* s;
        int bestIdx = 0, bestTotal = INT_MAX;

        // pass 1: find the best service (queue order is unchanged after n dequeue/enqueue)
        for (int i = 0; i < n; i++)
        {
            sl.dequeue(s);
            int total = getWaitList(s->type).GetTotalServiceTime();
            if (total < bestTotal) { bestTotal = total; bestIdx = i; }
            sl.enqueue(s);
        }

        // pass 2: take the best one out, put it at the back, then rotate it to the front
        Service* chosen = nullptr;
        for (int i = 0; i < n; i++)
        {
            sl.dequeue(s);
            if (i == bestIdx) chosen = s;
            else sl.enqueue(s);
        }
        sl.enqueue(chosen);
        for (int i = 0; i < n - 1; i++)
        {
            sl.dequeue(s);
            sl.enqueue(s);
        }
    }

    Service* next;
    sl.peek(next);
    c->setStatus(WAIT);
    getWaitList(next->type).enqueue(c);  // WaitingQueue adds next->duration to its running total
}