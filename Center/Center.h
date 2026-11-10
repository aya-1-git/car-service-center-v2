#pragma once
#include "../entities/Car.h"
#include "../entities/Bay.h"
#include "../ui/UI.h"
#include "../ds/CountQueue.h"
#include "../ds/priQueue.h"
#include "../ds/ArrayStack.h"
#include "../ds/EarlyPQ.h"
#include "../ds/LateQueue.h"
#include "../ds/WaitingQueue.h"

// priQueue: HIGHEST priority comes out first, so for "min X" order pass -X.
class Center
{
private:
    int totalCars;
    int currentTimestep;
    UI  ui;

    // ---- Car lists (pointers only: share, move, don't copy) ----
    priQueue<Car*>    idleList;      // priority = -VT
    EarlyPQ           earlyList;     // min PT
    LateQueue         lateList;      // arrival order
    CountQueue<Car*>  readyList;     // FCFS
    priQueue<Car*>    diagList;      // priority = -diagEnd
    WaitingQueue      waitMB;        // FCFS + running total service time
    WaitingQueue      waitEB;
    WaitingQueue      waitWB;
    priQueue<Car*>    servList;      // priority = -servEnd
    ArrayStack<Car*>  cnclList;      // top = latest cancel time
    ArrayStack<Car*>  fnshList;      // top = latest finish time

    // ---- Bay lists (pointers only) ----
    CountQueue<Bay*>  freeDiagBays;  // FCFS
    CountQueue<Bay*>  freeMB;        // FCFS
    CountQueue<Bay*>  freeEB;        // FCFS
    CountQueue<Bay*>  freeWB;        // wash bays that still have room

public:
    // ---------- Member 3: Center.cpp ----------
    Center();
    ~Center();
    bool allCarsDone() const;
    void runRandomSimulation();       // calls 2.1 to 2.11 in order, every timestep

    // ---------- Member 1: Center_Setup.cpp + Center_Sim_M1.cpp ----------
    void setupBays(int nDU, int nMU, int nEU, int nWU, int wbCap);
    void loadRandomCars(int count);
    void moveIdleToLists(int t);      // 2.1
    void moveEarlyToReady(int t);     // 2.2

    // ---------- Member 2: Center_Sim_M2.cpp ----------
    void cancelRandomLate(int t);     // 2.3
    void moveLateToReady(int t);      // 2.4

    // ---------- Member 3: Center_Sim_M3.cpp ----------
    void assignReadyToDiag(int t);    // 2.5
    void finishDiagnosis(int t);      // 2.6, 2.7
    void printState(int t);           // 2.11 (forwards to ui.printScreen)

    // ---------- Member 4: Center_Sim_M4.cpp ----------
    void assignWaitToBays(int t);     // 2.8
    void finishServices(int t);       // 2.9, 2.10

    // ---------- Shared helpers (Member 3 defines them, everyone uses them) ----------
    bool chance(int percent);                  // true with probability percent/100   (Center.cpp)
    int  randInt(int lo, int hi);              // random int in [lo, hi]              (Center.cpp)
    void assignRandomServices(Car* c);         // fills serviceList + seqType         (Center_Sim_M3.cpp)
    void moveToWaitList(Car* c);               // puts car in the WAIT list of its next service (2.6/2.7 and 2.9/2.10)
    WaitingQueue& getWaitList(UnitType type);  // MU->waitMB, EU->waitEB, WU->waitWB
};
