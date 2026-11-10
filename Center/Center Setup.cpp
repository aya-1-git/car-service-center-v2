#include "Center.h"
#include "../entities/CarGenerator.h"

// Creates every bay ONCE with new and puts its pointer in the matching free list.
void Center::setupBays(int nDU, int nMU, int nEU, int nWU, int wbCap)
{
    for (int i = 1; i <= nDU; i++)
        freeDiagBays.enqueue(new Bay(i, DU, 1));

    for (int i = 1; i <= nMU; i++)
        freeMB.enqueue(new Bay(i, MU, 1));

    for (int i = 1; i <= nEU; i++)
        freeEB.enqueue(new Bay(i, EU, 1));

    for (int i = 1; i <= nWU; i++)
        freeWB.enqueue(new Bay(i, WU, wbCap));
}

// Creates `count` random cars, all start in idleList (priority = -VT, so smallest VT comes out first).
void Center::loadRandomCars(int count)
{
    CarGenerator gen;
    for (int i = 0; i < count; i++)
    {
        Car* c = gen.next();
        idleList.enqueue(c, -c->getVT());
    }
    totalCars = count;
}
