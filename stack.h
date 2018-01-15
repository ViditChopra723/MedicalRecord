#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cassert>
#include "Node.h"

using namespace std;

template< class ItemType >
class Stack {
public:
	Stack();      // constructor
	~Stack();     // destructor
	bool push(const ItemType &);
	bool pop();
	bool top(ItemType &);
	bool isEmpty() const;
	bool isFull() const;


private:
	Node< ItemType > *stackPtr;  // pointer to first node

};

// Default constructor
template< class ItemType >
Stack< ItemType >::Stack()
{
	stackPtr = nullptr;
}

// Destructor
template< class ItemType >
Stack< ItemType >::~Stack()
{
	Node< ItemType > *currentPtr;

	while (stackPtr != nullptr)
	{
		currentPtr = stackPtr;
		stackPtr = stackPtr->nextPtr;
		delete currentPtr;
	}

}

// Insert a node at the front of the Stack
template< class ItemType >
bool Stack< ItemType >::push(const ItemType &value)
{
	Node< ItemType > *newPtr = new Node< ItemType>(value);

	if (newPtr == NULL)		//failure to allocate new node
		return false;
	else
	{
		newPtr->nextPtr = stackPtr;
		stackPtr = newPtr;
		return true;		// push is successful
	}
}

// Delete a node from the front of the list
template< class ItemType >
bool Stack< ItemType >::pop()
{
	if (isEmpty())             // List is empty
		return false;             // delete unsuccessful
	else {
		Node< ItemType > *tempPtr = stackPtr;

		stackPtr = stackPtr->nextPtr;

		delete tempPtr;
		return true;            // delete is successful
	}
}

template< class ItemType >
bool Stack< ItemType >::top(ItemType & value)
{
	if (isEmpty())             // List is empty
		return false;             // top is unsuccessful
	else {

		value = stackPtr->info;  // value is set to be data at top 
		return true;            // top is successful
	}
}

// Is the Stack empty?
template< class ItemType >
bool Stack< ItemType >::isEmpty() const
{
	return (stackPtr == nullptr);
}

// Is the Stack full?
template< class ItemType >
bool Stack< ItemType >::isFull() const
{
	Node< ItemType > *newPtr = new Node< ItemType >;

	if (newPtr == nullptr)		//failure to allocate new node
		return true;

	else {
		delete newPtr;
		return false;
	}
}


#endif
