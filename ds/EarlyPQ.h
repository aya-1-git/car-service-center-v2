#pragma once
#include "priQueue.h"
#include "../entities/Car.h"

// Early cars: priority queue ordered by PT (enqueue with priority = -PT).
class EarlyPQ : public priQueue<Car*>
{
public:
    // Removes the car at `position` (0 = top). Order of the rest is unchanged. False if out of range.
    bool removeAt(int position, Car*& removed)
    {
        if (position < 0 || position >= count)
            return false;

        priNode<Car*>* node;
        int pri;
        if (position == 0)
        {
            node = head;
            head = head->getNext();
        }
        else
        {
            priNode<Car*>* prev = head;
            for (int i = 1; i < position; i++)
                prev = prev->getNext();
            node = prev->getNext();
            prev->setNext(node->getNext());
        }
        removed = node->getItem(pri);
        delete node;
        count--;
        return true;
    }
};
