#include "Center.h"

// 2.6 / 2.7  Pick ALL cars that have spent 3 timesteps in DIAG.
//            With probability 20% a car goes to CNCL, otherwise it gets its random services
//            and moves randomly to one of the WAIT lists.
//            The DIAG bay of each of these cars becomes available again.
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

            // move the car RANDOMLY to one of the WAIT lists (MB / EB / WB)
            UnitType listType = static_cast<UnitType>(randInt(MU, WU));
            c->setStatus(WAIT);
            getWaitList(listType).enqueue(c);    // WaitingQueue adds the car's next-service time to its total
        }
    }
}