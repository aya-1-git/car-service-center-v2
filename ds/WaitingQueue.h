#pragma once
#include "CountQueue.h"
#include "../entities/Car.h"

// Waiting list of one unit (MB / EB / WB): FCFS + running total of the NEXT-service durations of the cars inside.
// Convention: a car's next service is the FRONT of its serviceList.
class WaitingQueue : public CountQueue<Car*>
{
private:
    int totalServiceTime;

    static int nextDuration(Car* c)
    {
        Service* s = nullptr;
        if (c->getServiceList().peek(s) && s)
            return s->duration;
        return 0;
    }

public:
    WaitingQueue() : totalServiceTime(0) {}

    bool enqueue(Car* const& c)
    {
        totalServiceTime += nextDuration(c);
        return CountQueue<Car*>::enqueue(c);
    }

    bool dequeue(Car*& c)
    {
        if (!CountQueue<Car*>::dequeue(c))
            return false;
        totalServiceTime -= nextDuration(c);   // the service must still be at the front of the car's list here
        return true;
    }

    int GetTotalServiceTime() const { return totalServiceTime; }
};
