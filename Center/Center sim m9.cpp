#include "Center.h"

// 2.11  Print the info of all lists as described in the "Program Interface".
//       (The UI only calls each list's print() function.)
void Center::printState(int t)
{
    ui.printScreen(t, idleList, earlyList, lateList, readyList,
        freeDiagBays, diagList,
        waitMB, waitEB, waitWB,
        freeMB, freeEB, freeWB,
        servList, cnclList, fnshList);
}