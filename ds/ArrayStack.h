//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file ArrayStack.h */

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include <iostream>
#include "StackADT.h"
#include "PrintItem.h"

 //Unless spesificed by the stack user, the default size is 100
template<typename T>
class ArrayStack : public StackADT<T>
{
	enum { MAX_SIZE = 1000 };   // CHANGED from 100: the project has up to 1000 cars (ask your TA if this edit is OK)
protected:  //in case you need to inherit for the project
	T items[MAX_SIZE];		// Array of stack items
	int top;                   // Index to top of stack

public:

	ArrayStack()
	{
		top = -1;
	}  // end default constructor

	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if (top == MAX_SIZE - 1) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  // end peek

	// ADDED (allowed)
	int GetCount() const { return top + 1; }

	// ADDED (allowed): prints from the top (latest) down, removes nothing.
	void print(int mode = 0, int limit = -1, const char* sep = " ") const
	{
		int printed = 0;
		for (int i = top; i >= 0 && (limit < 0 || printed < limit); i--, printed++)
		{
			if (printed > 0) std::cout << sep;
			printItem(std::cout, items[i], mode);
		}
	}

}; // end ArrayStack

#endif
