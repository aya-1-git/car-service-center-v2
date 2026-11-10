#include "CarGenerator.h"
#include <cstdlib>

CarGenerator::CarGenerator()
{
    nextCID = 1;
    lastVT = 1;
}

int CarGenerator::randInt(int lo, int hi) const
{
    return lo + rand() % (hi - lo + 1);
}

Car* CarGenerator::next()
{
    int vt = lastVT + randInt(0, 2);       // arrival time, never decreasing
    int pt = vt + randInt(-10, 10);        // appointment: early, on time or late
    if (pt < 1) pt = 1;
    int dd = randInt(1, 5);                // diagnosis duration

    lastVT = vt;
    return new Car(nextCID++, pt, vt, dd);
}
