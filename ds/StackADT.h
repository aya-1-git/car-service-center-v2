#ifndef STACK_ADT_
#define STACK_ADT_

// Standard lab stack interface (ArrayStack derives from it).
// If your lab folder already has its own StackADT.h, keep yours and delete this one.
template<typename T>
class StackADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool push(const T& newEntry) = 0;
	virtual bool pop(T& TopEntry) = 0;
	virtual bool peek(T& TopEntry) const = 0;
	virtual ~StackADT() {}
};

#endif
