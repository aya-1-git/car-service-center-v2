#pragma once
#include "../entities/Car.h"
#include "../entities/Bay.h"
#include "../ui/UI.h"
#include "../ds/LinkedQueue.h"
#include "../ds/priQueue.h"
#include "../ds/LinkedQueue Queues.h"
#include "../ds/ArrayStack.h"
#include "../ds/Queue.h"
#include "../ds/EarlyPQ.h"
#include "../ds/WaitingQueue.h"
#include "../ds/LateQueue.h"



class Center
{
private:
    int totalCars;
    int currentTimestep;
    /// <summary>
  /// the following lines should not be commented///////////////////////////////////////////////////////////////////////////////////
  /// </summary>
  /// <param name="c"></param>
    //UI  ui;
    //priQueue<Car*> idleList;      // priority = -VT
    //EarlyPQ        earlyList;     // min PT
    //LateQueue      lateList;      // arrival order
   // LinkedQueue<Car*> readyList;     // FCFS
    //priQueue<Car*> diagList;      // priority = -diagEnd
    //WaitingQueue   waitMB;        // FCFS + running total service time
    //WaitingQueue   waitEB;
    //WaitingQueue   waitWB;
    //priQueue<Car*> servList;      // priority = -servEnd
    //Stack<Car*>    cnclList;   // TODO: lab stack class name      // top = latest cancel time
    //Stack<Car*>    fnshList;      // top = latest finish time

    // ---- Bay lists (pointers only) ----
    //LinkedQueue<Bay*> freeDiagBays;  // FCFS
    //LinkedQueue<Bay*> freeMB;        // FCFS
    //LinkedQueue<Bay*> freeEB;        // FCFS
    //LinkedQueue<Bay*> freeWB;        // wash bays that still have room

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

    // ---------- Shared helpers (defined by Member 3 in Center.cpp, used by everyone) ----------
    bool chance(int percent);                  // true with probability percent/100
    int  randInt(int lo, int hi);              // random int in [lo, hi]



    /// <summary>
    /// the following lines should not be commented///////////////////////////////////////////////////////////////////////////////////
    /// </summary>
    /// <param name="c"></param>
    //void assignRandomServices(Car* c);         // fills serviceList + seqType (done at end of diagnosis)
    //void moveToWaitList(Car* c);               // puts car in the right WAIT list for its next service (used by 2.6/2.7 and 2.9/2.10)

};