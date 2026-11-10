#pragma once
#include <iostream>
#include "LinkedQueue.h"
#include "PrintItem.h"

// Lab LinkedQueue + a counter + print().  (Derived class with the extra functions the project allows.)
// Use it everywhere you would use LinkedQueue<T>.
template<typename T>
class CountQueue : public LinkedQueue<T>
{
protected:
    int count;

public:
    CountQueue() : count(0) {}

    bool enqueue(const T& item)
    {
        LinkedQueue<T>::enqueue(item);
        count++;
        return true;
    }

    bool dequeue(T& item)
    {
        if (!LinkedQueue<T>::dequeue(item))
            return false;
        count--;
        return true;
    }

    int GetCount() const { return count; }

    // Prints the elements front to back WITHOUT removing anything (dequeue + enqueue every element once).
    // mode: how each element is printed (see printItem overloads)   limit: print only the first N (-1 = all)
    void print(int mode = 0, int limit = -1, const char* sep = " ")
    {
        int n = count;
        T item;
        for (int i = 0; i < n; i++)
        {
            LinkedQueue<T>::dequeue(item);
            if (limit < 0 || i < limit)
            {
                if (i > 0) std::cout << sep;
                printItem(std::cout, item, mode);
            }
            LinkedQueue<T>::enqueue(item);
        }
    }
};