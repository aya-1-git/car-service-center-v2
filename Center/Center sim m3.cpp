#include "Center.h"
#include <climits>

// ---------- shared helpers ----------

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

// Puts the car in the WAIT list of its NEXT service.
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

// ---------- 2.5  each free diagnosis bay takes one car from REDY ----------
void Center::assignReadyToDiag(int t)
{
    const int DIAG_TIME = 3;             // steps in DIAG (Phase 1.2 simple simulator)
    Car* c;
    Bay* b;
    while (!freeDiagBays.isEmpty() && !readyList.isEmpty())
    {
        freeDiagBays.dequeue(b);
        readyList.dequeue(c);

        b->addCar();
        c->setCurrentBay(b);
        c->setStatus(DIAG);
        c->setDiagStart(t);
        c->setDiagEnd(t + DIAG_TIME);
        diagList.enqueue(c, -c->getDiagEnd());
    }
}

// ---------- 2.6 / 2.7  diagnosis finished ----------
void Center::finishDiagnosis(int t)
{
    const int CANCEL_PERCENT = 20;
    Car* c;
    int p;
    while (diagList.peek(c, p) && c->getDiagEnd() <= t)
    {
        diagList.dequeue(c, p);

        // free the diagnosis bay
        Bay* b = c->getCurrentBay();
        if (b)
        {
            b->removeCar();
            freeDiagBays.enqueue(b);
        }
        c->setCurrentBay(nullptr);

        if (chance(CANCEL_PERCENT))
        {
            c->setStatus(CNCL);
            c->setFT(t);                 // finish time = cancel time
            cnclList.push(c);
        }
        else
        {
            assignRandomServices(c);
            moveToWaitList(c);
        }
    }
}

// ---------- 2.11  print everything (UI only calls each list's print()) ----------
void Center::printState(int t)
{
    // The parameter list must match Member 4's UI::printScreen declaration.
    ui.printScreen(t, idleList, earlyList, lateList, readyList,
        freeDiagBays, diagList,
        waitMB, waitEB, waitWB,
        freeMB, freeEB, freeWB,
        servList, cnclList, fnshList);
}
