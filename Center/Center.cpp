#include "Center.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Center::Center()
{
    totalCars = 0;
    currentTimestep = 1;          // the simulation counter starts at 1
    srand((unsigned)time(0));     // seed once, here (no globals)
}

Center::~Center()
{
    // Every car/bay is created once with new, so delete each pointer exactly once.
    // At the end of a normal run all cars are in fnshList/cnclList and all bays are in the free lists.
    // Draining every list also covers a run that stopped early.
    Car* c;
    int p;
    while (idleList.dequeue(c, p))  delete c;
    while (earlyList.dequeue(c, p)) delete c;
    while (lateList.dequeue(c))     delete c;
    while (readyList.dequeue(c))    delete c;
    while (diagList.dequeue(c, p))  delete c;
    while (waitMB.dequeue(c))       delete c;
    while (waitEB.dequeue(c))       delete c;
    while (waitWB.dequeue(c))       delete c;
    while (servList.dequeue(c, p))  delete c;
    while (cnclList.pop(c))         delete c;
    while (fnshList.pop(c))         delete c;

    Bay* b;
    while (freeDiagBays.dequeue(b)) delete b;
    while (freeMB.dequeue(b))       delete b;
    while (freeEB.dequeue(b))       delete b;
    while (freeWB.dequeue(b))       delete b;
}

bool Center::allCarsDone() const
{
    return fnshList.GetCount() + cnclList.GetCount() == totalCars;
}

bool Center::chance(int percent)
{
    return (rand() % 100) < percent;
}

int Center::randInt(int lo, int hi)
{
    return lo + rand() % (hi - lo + 1);
}