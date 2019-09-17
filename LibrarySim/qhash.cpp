/*
 * Name: Simon Yip
 * Hashtable with Quadratic Probing Template Class Member Function Definitions
 * Course: CSI218 (Fall 2018)
 * Date: 12/2/18 (Started) @v1.1 12/17/18, 12/17/18 (Due)
 * Description: Hashtable member function definitions.
 */

#ifndef QHASH_CPP
#define QHASH_CPP

#include <iostream>
#include "qhash.h"
using namespace std;

// Constructors

template <class T>
Qhash<T>::Qhash(int size)  // default constructor (no parameters)	
{
	// length is used to store the size, assumes # > 0
	length = size;
	// sets/initializes # of items
	numItems = 0;
	// create new table
	table = new T[length];
	// setting each table to default values
	for (int i = 0; i < length; i++)
		table[i] = T();
}

// Accessors
// provides index of item in hashtable
template <class T>
int Qhash<T>::getIndex(const T &item, int hashValue)
{
	return locate(item, hashValue);
}

// returns a pointer to the object in the table
template <class T>
T * Qhash<T>::getData(int index) const
{
	return &table[index];
}

// returns hashtable length/size
template <class T>
int Qhash<T>::getQhashSize() const
{
	return length;
}

// returns # of items in hashtable
template <class T>
int Qhash<T>::getQhashNumItems() const
{
	return numItems;
}

// returns whether or not hashtable is empty
template <class T>
bool Qhash<T>::isQhashEmpty() const
{
	return numItems == 0;
}

// prints queue info
template <class T>
void Qhash<T>::showQhashInfo()
{
	// displays only if hashtable is empty
	if (length == 0)
	{
		cout << "There is nothing in the queue.";
		return;
	}

	// go thru each element in array
	for (int i = 0; i < length; i++)
	{
		// check to see whether value is filled with element
		if (!(table[i] == T()))
			// print out hash info
			cout << "Item in index: " << i << " Calculated base hash index: " << table[i].hash() % length << endl;
	}

}

// Mutators
// attempts to add appropriate item to hastable
template <class T>
void Qhash<T>::add(const T &newItem, int hashValue)
{
	// prevents adding to table when full
	if (numItems == length)
	{
		// prints out error message
		cerr << "Error: Cannot add, hashtable full!" << endl;
		return;
	}

	// attempt to get hash index
	int hashIndex = probe(newItem, hashValue);
	// check if hashindex is not the invalidindex
	if (hashIndex != -1)
	{
		// set item to new index
		table[hashIndex] = newItem;
		// increase num item count
		numItems++;

	}
	// prints out error message
	else
		cerr << "Error: Could not find open spot.";
}

// removes values in hashtable
template <class T>
void Qhash<T>::emptyQhash()
{
	// do not do work if there are no items to delete
	if (numItems == 0)
		return;
	// set numItems to 0
	else
		numItems = 0;

	// reset every value to default
	for (int i = 0; i < length; i++)
		table[i] = T();
}

// Copy constructor
template<class T>
Qhash<T>::Qhash(const Qhash<T> &otherQhash)
{
	// Copy non-dynamic array members.
	numItems = otherQhash.numItems;
	length = otherQhash.length;

	// Allocate new array for copy of other hashtable.
	table = new T[length];

	// copy values from other hashtable to this one
	for (int i = 0; i < length; i++)
		table[i] = otherQhash.table[i];
}

// Assignment operator
template<class T>
Qhash<T> &Qhash<T>::operator =(
	const Qhash<T> &otherQhash)
{
	// Avoid copying when assign object to self.
	if (this != &otherQhash)
	{
		// Copy non-dynamic array members.
		numItems = otherQhash.numItems;
		length = otherQhash.length;

		// Deallocate old array.
		delete[] table;

		// Allocate new array for copy of other hashtable.
		table = new T[length];

		// copies values from other hashtable to this one
		for (int i = 0; i < length; i++)
			table[i] = otherQhash.table[i];
	}

	// Return self.
	return *this;
}

// destructor
template <class T>
Qhash<T>::~Qhash()
{
	// resets values to 0
	numItems = 0;
	length = 0;
	// deletes array
	delete[] table;
	// prevent dangling pointer
	table = NULL;
}

// this function requires hash() to be implemented in class
// this calculates hashvalue index
template <class T>
int Qhash<T>::calcHashIndex(const T &item, int hashValue)
{
	return hashValue % length;
}

// this function "probes" for an open spot
template <class T>
int Qhash<T>::probe(const T &item, int hashValue)
{
	// get default hash value
	int hashIndex = calcHashIndex(item, hashValue);

	// loop to keep trying, as long as the length
	for (int i = 0; i < length; i++)
	{
		// calculate new position, subtract i^2 when i is even, or add i^2 when i is odd
		int hashNewIndex = (i % 2 == 0) ? ((hashIndex - i * i) % length) : ((hashIndex + i * i) % length);
		// if spot is empty, return position
		if (table[hashNewIndex] == T())
			return hashNewIndex;
	}

	// failed to probe open position
	// this shouldn't happen when array/hashtable
	// length % 4 == 3 based on formula
	return -1;
}

// this function attempts to locate the value in the table
template <class T>
int Qhash<T>::locate(const T &item, int hashValue)
{
	// get default hash value
	int hashIndex = calcHashIndex(item, hashValue);

	// loop to keep trying, as long as the length
	for (int i = 0; i < length; i++)
	{
		// calculate new position, subtract i^2 when i is even, or add i^2 when i is odd
		int hashNewIndex = (i % 2 == 0) ? ((hashIndex - i * i) % length) : ((hashIndex + i * i) % length);
		// if spot is not empty and has matching hash (this is probably the wrong way to call hash function)
		if (!(table[hashNewIndex] == T()) && table[hashNewIndex].hash() == hashValue)
			return hashNewIndex;
	}

	// failed to locate value
	return -1;
}

#endif
