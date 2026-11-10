#include "UI.h"
using namespace std;

void UI::waitForKey()
{
    cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl;
    cin.get();
}

void UI::printScreen(int t,
    priQueue<Car*>& idle, EarlyPQ& early, LateQueue& late, CountQueue<Car*>& ready,
    CountQueue<Bay*>& freeDiag, priQueue<Car*>& diag,
    WaitingQueue& waitMB, WaitingQueue& waitEB, WaitingQueue& waitWB,
    CountQueue<Bay*>& freeMB, CountQueue<Bay*>& freeEB, CountQueue<Bay*>& freeWB,
    priQueue<Car*>& serv, ArrayStack<Car*>& cncl, ArrayStack<Car*>& fnsh)
{
    cout << "Current Timestep:" << t << endl;

    cout << "=============== IDLE Cars [CarID, VT, PT] ================" << endl;
    cout << idle.GetCount() << " cars: ";
    idle.print(0, 15);
    if (idle.GetCount() > 15) cout << " ..... and so on";
    cout << endl << endl;

    cout << "=============== ERLY & LATE & REDY Cars [CarID, VT, PT] ============" << endl;
    cout << early.GetCount() << " ERLY: ";  early.print(0);  cout << endl;
    cout << late.GetCount() << " LATE: ";  late.print(0);   cout << endl;
    cout << ready.GetCount() << " REDY: ";  ready.print(0);  cout << endl << endl;

    cout << "--------------- Free Diagnosis Bays IDs ------------------------" << endl;
    cout << freeDiag.GetCount() << " Diag Bays: ";
    freeDiag.print(0, -1, ", ");
    cout << endl << endl;

    cout << "=============== DIAG Cars [CarID, Diag Bay ID] ==================" << endl;
    cout << diag.GetCount() << " Cars in Diag: ";
    diag.print(1);
    cout << endl << endl;

    cout << "=============== Cars waiting for Service [CarID, next Serv Time] ========" << endl;
    cout << waitMB.GetCount() << " MB cars waiting: ";  waitMB.print(2);  cout << endl;
    cout << waitEB.GetCount() << " EB cars waiting: ";  waitEB.print(2);  cout << endl;
    cout << waitWB.GetCount() << " WB cars waiting: ";  waitWB.print(2);  cout << endl << endl;

    cout << "--------------- Free Bays IDs -----------------------------------" << endl;
    cout << freeMB.GetCount() << " MB free: ";  freeMB.print(0, -1, ", ");  cout << endl;
    cout << freeEB.GetCount() << " EB free: ";  freeEB.print(0, -1, ", ");  cout << endl;
    cout << freeWB.GetCount() << " WB free (ID, remaining capacity): ";  freeWB.print(0, -1, ", ");  cout << endl << endl;

    cout << "=============== In-Service Cars [CarID, Bay ID] ==================" << endl;
    cout << serv.GetCount() << " Cars in Serv: ";
    serv.print(1);
    cout << endl << endl;

    cout << "=============== CNCL Cars [CarID, CancelTime] ==================" << endl;
    cout << cncl.GetCount() << " cancelled: ";
    cncl.print(3);
    cout << endl << endl;

    cout << "=============== FNSH Cars [CarID, FinishTime] ==================" << endl;
    cout << fnsh.GetCount() << " DONE: ";
    fnsh.print(3);
    cout << endl;
}
