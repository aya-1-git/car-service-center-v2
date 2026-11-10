#pragma once
#include <iostream>
#include "Car.h"     // for UnitType

class Bay
{
private:
    int id;                  // bay number inside its unit (D4, M14, E5, W3 -> 4, 14, 5, 3)
    UnitType unitType;       // DU / MU / EU / WU
    int capacity;            // 1 (DU/MU/EU) or WB_Cap (wash)
    int remainingCapacity;   // free slots

public:
    Bay(int id, UnitType type, int capacity = 1);

    int getID() const;
    UnitType getUnitType() const;
    int getCapacity() const;
    int getRemainingCapacity() const;

    bool isFull() const;     // no free slot
    bool isEmpty() const;    // no car inside (all slots free)
    bool addCar();           // takes one slot, false if full
    bool removeCar();        // frees one slot, false if already empty

    void printID(std::ostream& os = std::cout) const;   // D4, M14, E5, W3
    void print(std::ostream& os = std::cout) const;     // same, but wash bays also show remaining capacity: W3(2)
};

std::ostream& operator<<(std::ostream& os, Bay* b);

// Used by DS print() for lists of Bay*
void printItem(std::ostream& os, Bay* b, int mode);
