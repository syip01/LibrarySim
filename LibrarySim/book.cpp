/*
* Name: Simon Yip
* Book Member Function Definitions
* Course : CSI218(Fall 2018)
* Date: 12/2/18 (Started) @v1 12/17/18, 12/17/18 (Due)
* Description : Book member function definitions.
*/

#include <iostream>
#include "book.h"

using namespace std;
// Book member function definitions.

// Constructors

Book::Book()  // default constructor
	:Book("NewBook", "New Author", 0)
{

}

Book::Book(string newTitle, string newAuthor, int newQuantity)
{
	// Call member function "set" to initialize
	// data members.  Has one disadvantage: if
	// "newQuantity" is negative, "set" will
	// set the value to 0.
	setValues(newTitle, newAuthor, newQuantity);
}

// Accessors

// returns book title
string Book::getTitle() const
{
	return title;
}

// returns book author
string Book::getAuthor() const
{
	return author;
}

// returns current quantity of book
int Book::getCurQuantity() const
{
	return curQuantity;
}

// returns max quantity of book
int Book::getMaxQuantity() const
{
	return curQuantity;
}

// returns whether the book is available
bool Book::bookAvail() const
{
	return curQuantity > 0;
}

// prints book info
void Book::showBookInfo() const
{
	// wrapper to actual function
	// do not show current quantity info
	showBookInfo(false);
}

// prints book info with current quantity
void Book::showBookInfo(bool showCur) const
{
	// displays info
	cout << "Book Title: " << title << endl
		 << "Author: " << author << endl;
	// if show current book info flag is true, show it
	if (showCur)
		cout << "Current Quantity: " << curQuantity << endl;
	cout << "Max Quantity: " << maxQuantity << endl;
}

// Mutators

// Precondition: newQuantity must be a non-negative number.
// sets values for each component of book
void Book::setValues(string newTitle, string newAuthor, int newQuantity)
{
	setTitle(newTitle);
	setAuthor(newAuthor);
	setMaxQuantity(newQuantity);  // Check price; set if valid
}

// sets book title
void Book::setTitle(string newTitle)
{
	title = newTitle;
}

// sets book author
void Book::setAuthor(string newAuthor)
{
	author = newAuthor;
}

// Precondition: newQuantity must be a non-negative number.
// sets max quantity of book
void Book::setMaxQuantity(int newQuantity)
{
	if (newQuantity < 0)
	{
		cerr << "Quantity must be non-negative." << endl;
		maxQuantity = 0;
		curQuantity = 0;
		return;
	}

	// sets quantity to appropriate values	
	maxQuantity = newQuantity;
	// setting cur quantity is problematic
	// when books are already handed out
	curQuantity = maxQuantity;
}

// function simulates user taking out book
void Book::takeOutBook()
{
	// check for book availability
	if (bookAvail())
		// reduce current quantity
		curQuantity--;
	// prints out error message
	else
		cout << "Cannot take out more books." << endl;
}

// function simulates user returning book
void Book::returnBook()
{
	// check if current quantity is less than max quantity
	if (curQuantity < maxQuantity)
		// increase current quantity
		curQuantity++;
	// prints out error message (this should not happen)
	else
		cerr << "Already have max quantity." << endl;
}

// generates hash value
int Book::hash()
{
	// instantitate hash value
	int someHashVal = 0;
	// crude way of getting getting hashvalue
	// for both author and title
	for (int i = 0; i < (int) author.length(); i++)
		someHashVal += author[i] * (i + 17);
	for (int i = 0; i < (int) title.length(); i++)
		someHashVal += title[i] * (i + 11);
	// returns computed hashvalue
	return someHashVal;
}

/*
bool Book::equals(const Book &otherBook)
{
	return this.getAuthor() == otherBook.getAuthor() &&
		this.getTitle() == otherBook.getTitle();
}
*/

// Equality operator for book (not ideal)
// asserts that titles are unqiue
bool operator ==(const Book &left,
	const Book &right)
{
	return left.getTitle() == right.getTitle();
}
