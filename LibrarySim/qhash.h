/*
 * Name: Simon Yip
 * Hashtable with Quadratic Probing Template Class Definition
 * Course: CSI218 (Fall 2018)
 * Date: 12/2/18 (Started) @v1 12/17/18, 12/17/18 (Due)
 * Description: Hashtable class definition declaring data members
 *				and member functions.  Represents a hashtable that stores
 *				various Books and allows for searching.
 */

#ifndef QHASH_H
#define QHASH_H

template<class T>
class Qhash
{
public:
	// Constructors
	Qhash(int size);  // default constructor (no parameters)	

	// Accessors
	int getIndex(const T &item, int hashValue);
	T *getData(int index) const;

	int getQhashSize() const;
	int getQhashNumItems() const;

	bool isQhashEmpty() const;

	// prints hash info
	void showQhashInfo();

	// Mutators
	void add(const T &newItem, int hashValue);
	void emptyQhash();

	// Copy constructor
	Qhash(const Qhash<T> &otherHistory);

	// Assignment operator
	Qhash<T> &operator =(
		const Qhash<T> &otherQhash);

	// Destructor
	~Qhash();

private:
	T *table;
	int length;
	int numItems;

	// helper functions
	int calcHashIndex(const T &item, int hashValue);
	int probe(const T &item, int hashValue);
	int locate(const T &item, int hashValue);
};

#endif
