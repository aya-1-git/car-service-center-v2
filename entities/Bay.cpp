#include "Bay.h"

Bay::Bay(int id, UnitType type, int capacity)
{
    this->id = id;
    unitType = type;
    this->capacity = capacity;
    remainingCapacity = capacity;
}

int Bay::getID() const { return id; }
UnitType Bay::getUnitType() const { return unitType; }
int Bay::getCapacity() const { return capacity; }
int Bay::getRemainingCapacity() const { return remainingCapacity; }

bool Bay::isFull() const { return remainingCapacity == 0; }
bool Bay::isEmpty() const { return remainingCapacity == capacity; }

bool Bay::addCar()
{
    if (isFull()) return false;
    remainingCapacity--;
    return true;
}

bool Bay::removeCar()
{
    if (isEmpty()) return false;
    remainingCapacity++;
    return true;
}

void Bay::printID(std::ostream& os) const
{
    char prefix = 'D';
    if (unitType == MU) prefix = 'M';
    else if (unitType == EU) prefix = 'E';
    else if (unitType == WU) prefix = 'W';
    os << prefix << id;
}

void Bay::print(std::ostream& os) const
{
    printID(os);
    if (unitType == WU)
        os << "(" << remainingCapacity << ")";
}

std::ostream& operator<<(std::ostream& os, Bay* b)
{
    if (b) b->print(os);
    return os;
}

void printItem(std::ostream& os, Bay* b, int mode)
{
    if (b) b->print(os);
}
