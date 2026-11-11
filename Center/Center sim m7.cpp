#include "Center.h"

// 2.8  Pick up to 6 cars from the WAIT lists and give each one a RANDOM bay:
//      MB 60%, EB 30%, WB 10%.  If there is no available bay of the chosen type,
//      the car is NOT picked: it stays in its WAIT list.
//      (2.9: any service takes 4 timesteps, so servEnd = t + 4.)
void Center::assignWaitToBays(int t)
{
    const int SERV_TIME = 4;             // 2.9: any service takes 4 timesteps
    WaitingQueue* lists[3] = { &waitMB, &waitEB, &waitWB };

    for (int i = 0; i < 6; i++)
    {
        // a WAIT list that still has a car (random starting list)
        WaitingQueue* waitList = nullptr;
        int start = randInt(0, 2);
        for (int j = 0; j < 3 && waitList == nullptr; j++)
        {
            WaitingQueue* l = lists[(start + j) % 3];
            if (!l->isEmpty())
                waitList = l;
        }
        if (waitList == nullptr)
            break;                       // nobody is waiting anywhere: skip the rest

        // random bay type: MB 60%, EB 30%, WB 10%
        int r = randInt(1, 100);
        UnitType type = (r <= 60) ? MU : (r <= 90) ? EU : WU;
        CountQueue<Bay*>& freeList = (type == MU) ? freeMB : (type == EU) ? freeEB : freeWB;

        if (freeList.isEmpty())
            continue;                    // no available bay: don't pick the car

        // take the car FIRST (its service is still at the front, so WaitingQueue lowers its total correctly)
        Car* c = nullptr;
        waitList->dequeue(c);

        // take the bay
        Bay* b = nullptr;
        if (type == WU)
        {
            freeList.peek(b);            // a wash bay stays in the list while it still has room
            b->addCar();
            if (b->isFull())
                freeList.dequeue(b);     // now full: remove it from the "bays with room" list
        }
        else
        {
            freeList.dequeue(b);
            b->addCar();
        }

        // start the service
        c->setCurrentBay(b);
        c->setStatus(SERV);
        c->setServStart(t);
        c->setServEnd(t + SERV_TIME);
        servList.enqueue(c, -c->getServEnd());
    }
}