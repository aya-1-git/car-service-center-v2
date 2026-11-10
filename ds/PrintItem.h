#pragma once
#include <iostream>

// Generic fallback used by every DS print() (ints, etc.).
// Car* and Bay* have their own overloads (declared in Car.h / Bay.h), and the overload wins.
template<typename T>
void printItem(std::ostream& os, const T& item, int mode)
{
    os << item;
}
