/*
* Name: Simon Yip
* Reader Member Function Definitions
* Course : CSI218(Fall 2018)
* Date: 12/2/18 (Started) @v1 12/17/18, 12/17/18 (Due)
* Description : Reader member function definitions.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>	// for shuffle
#include "reader.h"

using namespace std;

// Constructors
Reader::Reader()  // default constructor (no parameters)
	:Reader("Reader", 1)
{
	// do something for bookList?
	// do something for bookStack?
}

Reader::Reader(string newName)
	:Reader(newName, 1)
{
}

Reader::Reader(string newName, int newPriority)
{
	name = newName;
	priority = newPriority;
	//returnBooks = false;
}



Reader::Reader(string newName, vector<Book> newBookList, stack<Book> newBookStack, int newPriority)
{
	name = newName;
	bookList = newBookList;
	bookStack = newBookStack;
	priority = newPriority;
	//returnBooks = false;
}

// Accessors
// returns name of reader
string Reader::getName() const
{
	return name;
}

// returns booklist
vector<Book> Reader::getBookList() const
{
	return bookList;
}

// returns book stack
stack<Book> Reader::getBookStack() const
{
	return bookStack;
}

// return reader's priority
int Reader::getPriority() const
{
	return priority;
}

// returns whether the booklist is empty
bool Reader::isBookListEmpty() const
{
	return(bookList.empty());
}

// prints reader info
void Reader::showReaderInfo()
{
	// prints out some info
	cout << endl
		 << "*Reader: " << name << endl
		 << "**Book List: " << endl;
	// goes thru every book and prints book info out
	for (int i = 0; i < (int) bookList.size(); i++)
		bookList[i].showBookInfo();

	// print out books in stack, primary reason why it cannot be const
	stack<Book>bookStackCopy = bookStack;

	// show all info in the book stack
	cout << endl
		<< "***Books in stack: " << endl;
	// print out book stack info
	while (!bookStackCopy.empty())
		// do not suppress messages of book data from stack
		removeBookFromStack(bookStackCopy, true);
}

// Mutators
// sets name of reader
void Reader::setName(string newName)
{
	name = newName;
}

// sets priority of reader
void Reader::setPriority(int newPriority)
{
	priority = newPriority;
}

// sets booklist of reader
void Reader::updateBookList(vector <Book> newBookList)
{
	bookList = newBookList;
}

// adds to book to stack
void Reader::addBookToStack(Book newBook)
{
	bookStack.push(newBook);
}

// empties book stack
void Reader::emptyBookStack()
{
	// suppress book info while removing books from stack.
	while (!bookStack.empty())
		removeBookFromStack(bookStack, false);

	// turn bit to return books to off
	// to simulate having just returned the books
	//returnBooks = false;
}

// simulates user reading through books
void Reader::readThruBooks()
{
	// create vector used for shuffling
	vector<Book> bookShuffle;
	// empty stack by copying the top and put each element into a vector
	while (!bookStack.empty())
	{
		bookShuffle.push_back(bookStack.top());
		bookStack.pop();
	}
	// use shuffle from algorithm
	random_shuffle(bookShuffle.begin(), bookShuffle.end());
	// put all the shuffled books back into stack
	for (int i = 0; i < (int) bookShuffle.size() ; i++)
		bookStack.push(bookShuffle[i]);

	// set bit to return books if and only if the bookList is empty
	//if (bookList.empty())
	//	returnBooks = true;
}

// helper function
// removes one book from stack
// asserts bookstack not empty
void Reader::removeBookFromStack(stack<Book> &aBookStack, bool displayInfo)
{
	// only display info when enabled
	if (displayInfo)
		aBookStack.top().showBookInfo();
	// pop book from stack
	aBookStack.pop();
}
