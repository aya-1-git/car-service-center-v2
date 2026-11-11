#include "Center.h"

// Random simulation (the driver):
//   1. initialisation: bays + at least 1000 random IDLE cars
//   2. at every timestep run steps 2.1 to 2.11 in order
//   3. end the simulation when ALL cars are in the FNSH or CNCL lists
void Center::runRandomSimulation()
{
    const int MAX_STEPS = 5000;   // safety guard against an endless loop

    // 1. initialisation
    setupBays(3, 5, 4, 3, 3);     // nDU, nMU, nEU, nWU, wash-bay capacity (change freely)
    loadRandomCars(1000);
    totalCars = 1000;
    currentTimestep = 1;

    // 2. one iteration = one timestep
    while (!allCarsDone() && currentTimestep <= MAX_STEPS)
    {
        int t = currentTimestep;

        moveIdleToLists(t);       // 2.1   Center_Sim_M1.cpp
        moveEarlyToReady(t);      // 2.2   Center_Sim_M1.cpp
        cancelRandomLate(t);      // 2.3   Center_Sim_M2.cpp
        moveLateToReady(t);       // 2.4   Center_Sim_M2.cpp
        assignReadyToDiag(t);     // 2.5   Center_Sim_M5.cpp
        finishDiagnosis(t);       // 2.6, 2.7   Center_Sim_M6.cpp
        assignWaitToBays(t);      // 2.8   Center_Sim_M7.cpp
        finishServices(t);        // 2.9, 2.10  Center_Sim_M8.cpp
        printState(t);            // 2.11  Center_Sim_M9.cpp

        ui.waitForKey();          // comment this line out for a fast run without pressing Enter
        currentTimestep++;
    }

    // 3. finished
    if (!allCarsDone())
        std::cout << "Stopped: reached " << MAX_STEPS << " timesteps and not all cars are done." << std::endl;
}