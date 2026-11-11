#include "Center.h"

// 2.5  For each available DIAG bay, assign one car from the REDY list.
//      (2.6: diagnosis takes 3 timesteps, so diagEnd = t + 3.)
void Center::assignReadyToDiag(int t)
{
    const int DIAG_TIME = 3;             // 2.6: diagnosis takes 3 timesteps
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