/*
 * Name: Simon Yip
 * Book Class Definition
 * Course: CSI218 (Fall 2018)
 * Date: 12/2/18 (Started) @v1 12/17/18, 12/17/18 (Due)
 * Description: Book class definition declaring
 *				data members and member functions.
 *				Book contains title, author, and quantity.
 */

#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book
{
public:
	// Constructors
	Book();  // default constructor (no parameters)
	Book(string newTitle, string newAuthor, int newQuantity);

	// Accessors
	string getTitle() const;
	string getAuthor() const;
	int getCurQuantity() const;
	int getMaxQuantity() const;
	bool bookAvail() const;

	// prints book info
	void showBookInfo() const;
	void showBookInfo(bool showCur) const;

	// Mutators
	void setValues(string newTitle, string newAuthor, int newQuantity);
	// Precondition: newQuantity must be non-negative

	void setTitle(string newTitle);

	void setAuthor(string newAuthor);

	void setMaxQuantity(int newQuantity);
	// Precondition: newQuantity must be non-negative.

	void takeOutBook();
	
	void returnBook();

	// hash function
	// required for hashtable
	int hash();

private:
	string title;
	string author;
	int maxQuantity;
	int curQuantity;
};

// Equality operator
bool operator ==(const Book &left,
	const Book &right);

#endif
