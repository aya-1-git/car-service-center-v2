#include "Center.h"

// 2.9 / 2.10  Pick ALL cars that have spent 4 timesteps in SERV.
//             Their bay becomes available again and the finished service is removed from the car's list.
//             Then: FNSH with probability 40% (or when no service is left),
//             otherwise back to a WAIT list (the list of its next service).
void Center::finishServices(int t)
{
    const int FINISH_PERCENT = 40;
    Car* c = nullptr;
    int p;

    while (servList.peek(c, p) && c->getServEnd() <= t)
    {
        servList.dequeue(c, p);

        // free the bay
        Bay* b = c->getCurrentBay();
        if (b)
        {
            bool wasFull = b->isFull();
            b->removeCar();
            if (b->getUnitType() == MU)      freeMB.enqueue(b);
            else if (b->getUnitType() == EU) freeEB.enqueue(b);
            else if (b->getUnitType() == WU && wasFull)
                freeWB.enqueue(b);       // it was out of the list while full; if it was not full it is still there
        }
        c->setCurrentBay(nullptr);
        c->setTS(c->getTS() + (c->getServEnd() - c->getServStart()));

        // the service that just ended is the front of the car's list
        Service* done = nullptr;
        if (c->getServiceList().dequeue(done))
            delete done;

        if (c->getServiceList().isEmpty() || chance(FINISH_PERCENT))
        {
            c->setStatus(FNSH);
            c->setFT(t);                 // finish time
            fnshList.push(c);
        }
        else
        {
            moveToWaitList(c);           // back to the WAIT list of its next service
        }
    }
}