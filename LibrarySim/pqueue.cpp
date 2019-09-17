/*
 * Name: Simon Yip
 * Priority Queue Template Class Member Function Definitions
 * Course: CSI218 (Fall 2018)
 * Date: 12/2/18 (Started) @v1 12/17/18, 12/17/18 (Due)
 * Description: Priority Queue member function definitions.
 */

#ifndef PQUEUE_CPP
#define PQUEUE_CPP

#include <iostream>
#include "pqueue.h"
using namespace std;


// Constructors

template <class T>
Pqueue<T>::Pqueue()  // default constructor (no parameters)	
{
	list = NULL;
	back = NULL;
	length = 0;
}

// Accessors

// returns data @ front of list
template <class T>
T Pqueue<T>::getFront() const
{
	// checks when list is set (not null)
	if(list != NULL)
		// returns data
		return list->data;
	// returns default value on fail
	// not sure if ideal
	return T();
}

// returns data @ back of list
// not normal/necessary
template <class T>
T Pqueue<T>::getBack() const
{
	// checks when back pointer is set (not null)
	if(back != NULL)
		// returns data
		return back->data;
	// returns default value on fail
	// not sure if ideal
	return T();
}

// returns value of the frontmost item
template <class T>
int Pqueue<T>::getFrontPriority() const
{
	// checks if list is not null
	if (list != NULL)
		// returns priority
		return list->priority;
	// returns 0 for nothing in list
	return 0;
}

// returnes queue length
template <class T>
int Pqueue<T>::getQueueSize() const
{
	return length;
}

// returns whether queue is empty
template <class T>
bool Pqueue<T>::isQueueEmpty() const
{
	return length == 0;
}

// prints queue info
template <class T>
void Pqueue<T>::showQueueStats() const
{
	// displays only if queue is empty
	if (length == 0)
	{
		cout << "There is nothing in the queue.";
		return;
	}

	// used to traverse list
	Node <T> *iter = list;

	// counts # of instances of a particular priority
	// initialized to 0 for the purposes of counting first item
	int count = 0;
	// stores current priority for the purposes of counting
	// initialized to the priority of the first item
	int curPriority = iter->priority;


	// goes through entire list
	for (int i = 0; i < length; i++)
	{
		// changes priority when it is different
		// also resets count
		// assumes list is sorted/in order by priority
		if (curPriority != iter->priority)
		{
			//displays info
			cout << "Priority: " << curPriority << endl
				 << "Count: " << count << endl;
			curPriority = iter->priority;
			// count is reset to 1, because it is a new item being counted
			count = 1;
		}

		// otherwise updates count
		else
		{
			count++;
		}
		// move to next node
		iter = iter->nextP;
	}

	// prints out last count once out of loop
	cout << "Priority: " << curPriority << endl
		 << "Count: " << count << endl;
}

// Mutators
// adds item to queue
template <class T>
void Pqueue<T>::add(const T &newItem, int priority)
{
	// increase length count
	length++;

	// create node with data
	Node<T> *newNode = new Node<T>;
	newNode->data = newItem;
	// sets priority to 1 if not greater than 1
	// 0 priority means error
	newNode->priority = (priority >= 1) ? priority : 1;
	newNode->nextP = NULL;

	// sets list pointer when it is initially empty
	if (list == NULL)
	{
		list = newNode;
		back = newNode;
		return;
	}

	// stores the last node pointer it was greater than
	// initial NULL value used for putting node to head
	Node <T> *lastP = NULL;

	for (Node<T> *traverseP = list; traverseP != NULL; traverseP = traverseP->nextP)
	{
		// if the current priority is less than the new node's priority
		// then add node to last pointer
		if (traverseP->priority < priority)
		{
			//check if the last node is not NULL/first
			// add in between nodes
			if (lastP != NULL)
			{
				// make the new node point to current node
				newNode->nextP = traverseP;
				// make the last/prev node recorded link to next
				lastP->nextP = newNode;
				return;
			}

			// add as the first node
			else
			{
				// make the new node point to first node
				newNode->nextP = list;
				// make the first node the new node
				list = newNode;
				return;
			}
		}

		// update last node that it the new node is >= current node
		else
		{
			lastP = traverseP;
		}
	}

	// if loop ends w/o returning, attach new node to the end
	lastP->nextP = newNode;
	// update back node to the new node
	back = newNode;
}

// removes item from queue
template <class T>
void Pqueue<T>::remove()
{
	// do not try to remove when length is 0/empty queue
	if (length == 0)
		return;

	// decrease length count
	length--;

	// store pointer to next node
	Node<T> *nextNode = list->nextP;

	// delete head/list pointer node
	delete list;

	// make head/list the next node that was previously stored
	list = nextNode;
}

// Copy constructor
template<class T>
Pqueue<T>::Pqueue(const Pqueue<T> &otherPqueue)
{
	// Copy non-dynamic members.
	length = otherPqueue.length;
	
	// copy elements from other queue to this queue
	copy(otherPqueue);
}

// Assignment operator
template<class T>
Pqueue<T> &Pqueue<T>::operator =(
	const Pqueue<T> &otherPqueue)
{
	// Avoid copying when assign object to self.
	if (this != &otherPqueue)
	{
		// Copy non-dynamic members.
		length = otherPqueue.length;

		// delete current queue

		// copy elements from other queue to this queue
		copy(otherPqueue);
	}

	// Return self.
	return *this;
}

// destructor
template <class T>
Pqueue<T>::~Pqueue()
{
	// sets length to 0
	length = 0;
	// clear all nodes
	clear();
	// prevent dangling pointers
	list = NULL;
	back = NULL;
}

// Add all items from other history
template<class T>
void Pqueue<T>::copy(const Pqueue<T> &otherPqueue)
{
	// traverse thru the list
	for (Node <T> *traverseP = otherPqueue.list; traverseP != NULL; traverseP = traverseP->nextP)
	{
		// creates new node
		Node <T> *newNode = new Node<T>;
		newNode->data = traverseP->data;
		newNode->priority = traverseP->priority;
		newNode->nextP = NULL;

		// check if head exists
		if (list == NULL)
			list = newNode;
		// otherwise append to end
		else
			back->nextP = newNode;

		// sets back node to the newnode
		back = newNode;
	}
}

// Remove all items
template<class T>
void Pqueue<T>::clear()
{
	// loops until the list is empty
	while (list != NULL)
	{
		// makes a pointer to the current list node
		Node <T> *deleteP = list;
		// move to next node
		list = list->nextP;
		// delete node that is being pointed to
		delete deleteP;
	}

	// ALSO SET RESET POINTER TO LAST NODE.
	back = NULL;
}

#endif
