/*
 * Name: Simon Yip
 * Reader Class Definition
 * Course: CSI218 (Fall 2018)
 * Date: 12/2/18 (Started) @v1 12/17/18, 12/17/18 (Due)
 * Description: Reader class definition declaring
 *				data members and member functions.
 *				Reader contains name, list of books,
 *				stack of books to read/return, # of days before books are returned.
 */

#ifndef READER_H
#define READER_H

#include <string>
#include <stack>
#include <vector>
#include "book.h"

using namespace std;

class Reader
{
public:
	// Constructors
	Reader();  // default constructor (no parameters)
	Reader(string newName);
	Reader(string newName, int newPriority);
	Reader(string newName, vector<Book> newBookList, stack<Book> newBookStack, int newPriority);

	// Accessors
	string getName() const;
	vector<Book> getBookList() const;
	stack<Book> getBookStack() const;
	int getPriority() const;

	bool isBookListEmpty() const;

	// prints reader info
	void showReaderInfo();

	// Mutators
	void setName(string newName);
	void setPriority(int newPriority);
	void updateBookList(vector <Book> newBookList);
	void addBookToStack(Book newBook);
	void emptyBookStack();

	// simulates user reading through books
	void readThruBooks();
	
private:
	string name;
	vector<Book> bookList;
	stack<Book> bookStack;
	//bool returnBooks;
	/* The above variable was meant to prevent returning of books,
		it was disabled due to it causing potential issues with queue contention.
	*/
	int priority;
	// helper function
	void removeBookFromStack(stack<Book> &aBookStack, bool displayInfo);
};

#endif
