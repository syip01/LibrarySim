/*
 * Name: Simon Yip
 * Priority Queue Template Class Definition
 * Course: CSI218 (Fall 2018)
 * Date: 12/2/18 (Started) @v1 12/17/18, 12/17/18 (Due)
 * Description: Priority Queue class definition declaring data members
 *				and member functions.  Represents a queue that places
 *				Readers to the front of the line when all of the books on their list
 *				could not be collected. Readers get a chance to collect books on their list
 *				on a first-come first served basis (FIFO). Also, sorts data upon insertion.
 */

#ifndef PQUEUE_H
#define PQUEUE_H

template<class T>
class Pqueue
{
public:
	// Constructors
	Pqueue();  // default constructor (no parameters)	

	// Accessors
	T getFront() const;
	T getBack() const;

	int getFrontPriority() const;

	int getQueueSize() const;

	bool isQueueEmpty() const;

	// prints queue info
	void showQueueStats() const;

	// Mutators
	void add(const T &newObject, int priority);
	void remove();

	void clear();

	// Copy constructor
	Pqueue(const Pqueue<T> &otherPqueue);

	// Assignment operator
	Pqueue<T> &operator =(
		const Pqueue<T> &otherPqueue);

	// Destructor
	~Pqueue();

private:
	template <class T>
	struct Node
	{
	public:
		T data;
		int priority;
		Node *nextP;
	};

	Node<T> *list;
	Node<T> *back;
	int length;

	// assist in copying items from queue to queue
	void copy(const Pqueue<T> &otherPqueue);

};

#endif
