#ifndef QUEUE_ADT_
#define QUEUE_ADT_

// Standard lab queue interface (LinkedQueue derives from it).
// If your lab folder already has its own QueueADT.h, keep yours and delete this one.
template <typename T>
class QueueADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool enqueue(const T& newEntry) = 0;
	virtual bool dequeue(T& frntEntry) = 0;
	virtual bool peek(T& frntEntry) const = 0;
	virtual ~QueueADT() {}
};

#endif
