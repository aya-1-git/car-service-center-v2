#include "Car.h"
#include "Bay.h"

Car::Car(int cid, int pt, int vt, int dd)
{
    this->cid = cid;
    this->pt = pt;
    this->vt = vt;
    this->dd = dd;
    status = IDLE;
    seqType = SS;
    diagStart = diagEnd = 0;
    servStart = servEnd = 0;
    currentBay = nullptr;
    tw = ts = 0;
    ft = 0;
}

Car::~Car()
{
    Service* s;
    while (serviceList.dequeue(s))
        delete s;
}

int Car::getCID() const { return cid; }
int Car::getPT() const { return pt; }
int Car::getVT() const { return vt; }
int Car::getDD() const { return dd; }
CarStatus Car::getStatus() const { return status; }
SeqType Car::getSeqType() const { return seqType; }
CountQueue<Service*>& Car::getServiceList() { return serviceList; }
int Car::getDiagStart() const { return diagStart; }
int Car::getDiagEnd() const { return diagEnd; }
int Car::getServStart() const { return servStart; }
int Car::getServEnd() const { return servEnd; }
Bay* Car::getCurrentBay() const { return currentBay; }
int Car::getTW() const { return tw; }
int Car::getTS() const { return ts; }
int Car::getFT() const { return ft; }

void Car::setStatus(CarStatus s) { status = s; }
void Car::setSeqType(SeqType s) { seqType = s; }
void Car::setDiagStart(int t) { diagStart = t; }
void Car::setDiagEnd(int t) { diagEnd = t; }
void Car::setServStart(int t) { servStart = t; }
void Car::setServEnd(int t) { servEnd = t; }
void Car::setCurrentBay(Bay* b) { currentBay = b; }
void Car::setTW(int t) { tw = t; }
void Car::setTS(int t) { ts = t; }
void Car::setFT(int t) { ft = t; }

void Car::print(std::ostream& os) const
{
    os << "[C" << cid << ", " << vt << ", " << pt << "]";
}

void Car::printWithBay(std::ostream& os) const
{
    os << "[C" << cid << ", ";
    if (currentBay) currentBay->printID(os);
    else os << "-";
    os << "]";
}

void Car::printWithNextService(std::ostream& os)
{
    Service* s = nullptr;
    int d = 0;
    if (serviceList.peek(s) && s)
        d = s->duration;
    os << "[C" << cid << ", " << d << "]";
}

void Car::printWithFinishTime(std::ostream& os) const
{
    os << "[C" << cid << ", " << ft << "]";
}

std::ostream& operator<<(std::ostream& os, Car* c)
{
    if (c) c->print(os);
    return os;
}

void printItem(std::ostream& os, Car* c, int mode)
{
    if (!c) return;
    if (mode == 1) c->printWithBay(os);
    else if (mode == 2) c->printWithNextService(os);
    else if (mode == 3) c->printWithFinishTime(os);
    else c->print(os);
}
