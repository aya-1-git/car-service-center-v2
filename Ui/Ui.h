#pragma once
#include <iostream>
#include "../entities/Car.h"
#include "../entities/Bay.h"
#include "../ds/CountQueue.h"
#include "../ds/priQueue.h"
#include "../ds/ArrayStack.h"
#include "../ds/EarlyPQ.h"
#include "../ds/LateQueue.h"
#include "../ds/WaitingQueue.h"

// Console output only. It never reads/writes the input/output files and it only calls each list's print().
class UI
{
public:
    void printScreen(int t,
        priQueue<Car*>& idle, EarlyPQ& early, LateQueue& late, CountQueue<Car*>& ready,
        CountQueue<Bay*>& freeDiag, priQueue<Car*>& diag,
        WaitingQueue& waitMB, WaitingQueue& waitEB, WaitingQueue& waitWB,
        CountQueue<Bay*>& freeMB, CountQueue<Bay*>& freeEB, CountQueue<Bay*>& freeWB,
        priQueue<Car*>& serv, ArrayStack<Car*>& cncl, ArrayStack<Car*>& fnsh);

    void waitForKey();      // "PRESS ANY KEY TO MOVE TO NEXT STEP !"
};
