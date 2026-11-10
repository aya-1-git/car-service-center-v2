#pragma once
#include "CountQueue.h"
#include "../entities/Car.h"

// Late cars: plain FCFS queue (arrival order) + removeAt for cancellation of a random late car.
class LateQueue : public CountQueue<Car*>
{
public:
    // Removes the car at `position` (0 = front). Order of the rest is unchanged. False if out of range.
    bool removeAt(int position, Car*& removed)
    {
        if (position < 0 || position >= count)
            return false;

        int n = count;
        Car* c;
        for (int i = 0; i < n; i++)
        {
            LinkedQueue<Car*>::dequeue(c);
            if (i == position) removed = c;
            else LinkedQueue<Car*>::enqueue(c);
        }
        count--;
        return true;
    }
};