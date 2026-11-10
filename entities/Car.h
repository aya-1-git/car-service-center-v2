#pragma once
#include <iostream>
#include "../ds/CountQueue.h"

class Bay;   // forward declaration (Bay.h includes this file for UnitType)

enum CarStatus { IDLE, ERLY, LATE, REDY, DIAG, WAIT, SERV, CNCL, FNSH };
enum SeqType { SS, FS };
enum UnitType { DU, MU, EU, WU };
struct Service { UnitType type; int duration; };

class Car
{
private:
    int cid;                 // car ID (printed as C<cid>)
    int pt;                  // appointment time
    int vt;                  // arrival time
    int dd;                  // diagnosis duration
    CarStatus status;
    SeqType seqType;
    CountQueue<Service*> serviceList;   // required services; FRONT = current/next service
    int diagStart, diagEnd;
    int servStart, servEnd;
    Bay* currentBay;         // bay the car is in (nullptr if none)
    int tw, ts;              // total waiting / service time
    int ft;                  // finish time or cancel time

public:
    Car(int cid, int pt, int vt, int dd);
    ~Car();                  // deletes any services still in serviceList

    // ---- getters ----
    int getCID() const;
    int getPT() const;
    int getVT() const;
    int getDD() const;
    CarStatus getStatus() const;
    SeqType getSeqType() const;
    CountQueue<Service*>& getServiceList();
    int getDiagStart() const;
    int getDiagEnd() const;
    int getServStart() const;
    int getServEnd() const;
    Bay* getCurrentBay() const;
    int getTW() const;
    int getTS() const;
    int getFT() const;

    // ---- setters ----
    void setStatus(CarStatus s);
    void setSeqType(SeqType s);
    void setDiagStart(int t);
    void setDiagEnd(int t);
    void setServStart(int t);
    void setServEnd(int t);
    void setCurrentBay(Bay* b);
    void setTW(int t);
    void setTS(int t);
    void setFT(int t);

    // ---- print helpers (none of them removes anything) ----
    void print(std::ostream& os = std::cout) const;                  // [C43, 90, 82]  = [CarID, VT, PT]
    void printWithBay(std::ostream& os = std::cout) const;           // [C1, D9]       = [CarID, Bay ID]
    void printWithNextService(std::ostream& os = std::cout);         // [C74, 9]       = [CarID, next service time]
    void printWithFinishTime(std::ostream& os = std::cout) const;    // [C99, 68]      = [CarID, finish/cancel time]
};

// the ONLY allowed friend-like operator (it only uses public getters, so no friendship is needed)
std::ostream& operator<<(std::ostream& os, Car* c);

// Used by every DS print(): mode 0 = [C, VT, PT], 1 = [C, bay], 2 = [C, next service time], 3 = [C, finish/cancel time]
void printItem(std::ostream& os, Car* c, int mode);
