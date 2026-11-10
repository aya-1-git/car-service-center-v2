#include "Center.h"

// 2.1  Top 50 cars of IDLE go randomly to LATE / ERLY / REDY
void Center::moveIdleToLists(int t)
{
    Car* c;
    int p;
    for (int i = 0; i < 50; i++)
    {
        if (!idleList.dequeue(c, p))
            break;                                   // IDLE is empty: skip

        int r = randInt(0, 2);
        if (r == 0)
        {
            c->setStatus(ERLY);
            earlyList.enqueue(c, -c->getPT());       // min PT first
        }
        else if (r == 1)
        {
            c->setStatus(LATE);
            lateList.enqueue(c);                     // arrival order
        }
        else
        {
            c->setStatus(REDY);
            readyList.enqueue(c);
        }
    }
}

// 2.2  Top 6 cars of ERLY go to REDY
void Center::moveEarlyToReady(int t)
{
    Car* c;
    int p;
    for (int i = 0; i < 6; i++)
    {
        if (!earlyList.dequeue(c, p))
            break;                                   // ERLY is empty: skip

        c->setStatus(REDY);
        readyList.enqueue(c);
    }
}
