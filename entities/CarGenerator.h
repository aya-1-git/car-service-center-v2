#pragma once
#include "Car.h"

// Generates random cars one by one. Car IDs are 1, 2, 3, ... and VT never decreases,
// so inserting them into idleList in generation order keeps it sorted by VT.
class CarGenerator
{
private:
    int nextCID;
    int lastVT;
    int randInt(int lo, int hi) const;

public:
    CarGenerator();
    Car* next();     // creates ONE new car with new (the caller puts the pointer in a list)
};
