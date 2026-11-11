#include "../Center/Center.h"

// 2.3  With probability 10%, pick one random car (NOT the top one) from LATE and move it to CNCL
void Center::cancelRandomLate(int t)
{
    const int CANCEL_PERCENT = 10;

    if (!chance(CANCEL_PERCENT))
        return;

    int n = lateList.GetCount();
    if (n < 2)                         // LATE is empty or has only the top car: skip
        return;

    int target = randInt(1, n - 1);    // index 0 is the top car, never picked

    Car* chosen = nullptr;
    lateList.removeAt(target, chosen);

    chosen->setStatus(CNCL);
    chosen->setFT(t);                  // finish time = cancel time
    cnclList.push(chosen);
}

// 2.4  Top 6 cars of LATE go to REDY
void Center::moveLateToReady(int t)
{
    Car* c = nullptr;
    for (int i = 0; i < 6; i++)
    {
        if (!lateList.dequeue(c))
            break;                    // LATE is empty: skip

        c->setStatus(REDY);
        readyList.enqueue(c);
    }
}