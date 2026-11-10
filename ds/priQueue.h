#pragma once
#include <iostream>
#include "priNode.h"
#include "PrintItem.h"


//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
protected:  //in case you need to inherit for the project
    priNode<T>* head;
    int count;                      // ADDED (allowed): number of items
public:
    priQueue() : head(nullptr), count(0) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        count++;                    // ADDED

        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        count--;                    // ADDED
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    // ADDED (allowed)
    int GetCount() const { return count; }

    // ADDED (allowed): prints front to back, removes nothing.
    // mode: how each element is printed   limit: only the first N (-1 = all)
    void print(int mode = 0, int limit = -1, const char* sep = " ") const {
        int i = 0;
        int p;
        for (priNode<T>* cur = head; cur && (limit < 0 || i < limit); cur = cur->getNext(), i++) {
            if (i > 0) std::cout << sep;
            printItem(std::cout, cur->getItem(p), mode);
        }
    }
};
