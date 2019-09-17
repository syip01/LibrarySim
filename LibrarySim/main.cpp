/*
 * Name: Simon Yip
 * Final Project - Library Simulator
 * Course: CSI218 (Fall 2018)
 * Date: 12/2/18 (Started) @v1 12/17/18, 12/17/18 (Due)
 * Description: This program simulates a library.
 * A Reader attempts to borrow multiple Books from the library,
 * looks thru them, and then returns those books back to the library.
 */

#include <iostream>
#include <string>
#include "book.h"	// book class
#include "reader.h"		// reader class
#include "pqueue.cpp"	// template priority queue
#include "qhash.cpp"	// quadratic hash table
#include <cstdlib>	// for generating random #s
#include <time.h>	// using time to seed random #s
#include <set>	// for removing duplicate values
#include <stack>	// for storing stacks
#include <vector>	// for storing vectors
#include <Windows.h>	// for holding screen @ end

#define BOOKS_TO_GET 4
#define BOOKSHELF_SIZE 11
#define QUIT_APP 0
#define NEXT_DAY 1
#define SHOW_READERS 2
#define SHOW_QUEUE 3
#define READER_LIST 4
#define BOOK_LIST 5
#define SHOW_TABLE 6

using namespace std;

void generateBooks(vector<Book> &library);
void addBook(vector<Book> &library, const string &name, const string &author, const int &number);
void generateReaders(vector<Reader> &readers);
void addReader(vector<Reader> &readers, const string &name, const int &priority);
void generateBooklistsForAReader(const vector<Book> &bookList, Reader &aReader);
void addBooksToShelf(vector<Book> &bookList, Qhash<Book> &bookShelf);
void addReadersToQueue(vector<Reader> &readers, Pqueue<Reader> &bookQueue);
void processQueue(vector<Reader> &readers, Pqueue<Reader> &bookQueue, Qhash<Book> &bookShelf, const vector<Book> &bookList);
void showReaders(vector<Reader> &readers);
void showReaderList(vector<Reader> &listReaders);
void showBookList(Qhash<Book> &bookShelf);
void showTable(Qhash<Book> &bookShelf);
void returnReaderBooks(Reader &aReader, Qhash<Book> &bookShelf);

int main()
{
	// initialize seed for randomization
	srand((int)time(NULL));

	// create list of books that exist
	vector<Book> bookList;
	generateBooks(bookList);

	// create readers that use the library
	vector<Reader> readers;
	generateReaders(readers);

	// create copies of these list for info purposes
	vector<Reader> listReaders = readers;

	// create booklist for each reader
	for (int i = 0; i < (int)readers.size(); i++)
		generateBooklistsForAReader(bookList, readers[i]);

	// create bookshelf that stores all the books
	Qhash<Book> bookShelf(BOOKSHELF_SIZE);
	addBooksToShelf(bookList, bookShelf);
	
	// add every reader to the priority queue
	Pqueue <Reader> pqueue;
	//addReadersToQueue(readers, pqueue);

	// store selected menu index
	int menuIndex = NEXT_DAY;

	// print title of app
	cout << "Library Simulator" << endl;

	// ADD MENU HERE
	do
	{
		cout << endl;
		// show readers and queue info upon after a new day has occurred
		if (menuIndex == NEXT_DAY)
		{
			cout << endl;
			cout << endl << "Reader Info: " << endl;
			showReaders(readers);
			cout << endl << "Queue Info:" << endl;
			pqueue.showQueueStats();
			cout << endl;
		}

		cout << endl;

		cout << NEXT_DAY << ") Simulate Next Day" << endl;
		cout << SHOW_READERS << ") Show Status of Readers" << endl;
		cout << SHOW_QUEUE << ") Show Queue Info" << endl;
		cout << READER_LIST << ") Show List of Readers" << endl;
		cout << BOOK_LIST << ") Show List of Books" << endl;
		cout << SHOW_TABLE << ") Show Book Locations" << endl;
		// get input
		cout << "Enter Option (" << QUIT_APP << " to quit): ";
		cin >> menuIndex;

		//process input
		switch (menuIndex)
		{
		case NEXT_DAY:
			// simulates processing the queue for a day
			processQueue(readers, pqueue, bookShelf, bookList);
			break;
		case SHOW_READERS:
			// show reader info
			showReaders(readers);
			break;
		case SHOW_QUEUE:
			// show queue info
			pqueue.showQueueStats();
			break;
		case READER_LIST:
			// show reader list
			showReaderList(listReaders);
			break;
		case BOOK_LIST:
			// show book list
			//showBookList(bookList);
			showBookList(bookShelf);
			break;
		case SHOW_TABLE:
			// show hash table
			showTable(bookShelf);
			break;
		case QUIT_APP:
			// quit message
			cout << "Thank you for using this simulator." << endl;
			break;
		default:
			// shows error message
			cout << "Invalid menu option." << endl;
		}

	} while (menuIndex != QUIT_APP);	// loop until selected option is 0

	// pause screen before exiting
	system("pause");

	return 0;
}

// generates books to be added to booklist
void generateBooks(vector<Book> &library)
{
	addBook(library, "C# 6 for Programmers", "Deitel", 2);
	addBook(library, "Data Structures Using C++", "Malik", 1);
	addBook(library, "Starting out with Java 7th Ed", "Gaddis", 2);
	addBook(library, "Starting out with Java 6th Ed", "Gaddis", 4);
	addBook(library, "CompTIA Network+ Guide to Networks", "West, Dean, Andrews", 2);
	addBook(library, "Cisco CCENT/CCNA", "Odom", 5);
	addBook(library, "Guide to UNIX Using Linux", "Palmer", 3);
	addBook(library, "Programming with Microsoft Visual Basic 2015", "Zak", 1);
}

// adds book to booklist
void addBook(vector<Book> &library, const string &name, const string &author, const int &number)
{
	Book aBook (name, author, number);
	library.push_back(aBook);
}

// generates readers to be added to reader list
void generateReaders(vector<Reader> &readers)
{
	addReader(readers, "Simon Yip", 1);
	addReader(readers, "Robert Pitts", 3);
	addReader(readers, "Sean Riley", 1);
	addReader(readers, "Jane Gray", 1);
	addReader(readers, "Xhefri Toro", 1);
	addReader(readers, "Ruiting Chen", 1);
}

// adds readers to reader list
void addReader(vector<Reader> &readers, const string &name, const int &priority)
{
	Reader aReader (name, priority);
	readers.push_back(aReader);
}

// adds a book list to one reader
void generateBooklistsForAReader(const vector<Book> &bookList, Reader &aReader)
{
	vector<int> bookIndexes;
	// generates 1 to 4 (BOOKS TO GET) books
	for (int i = rand() % BOOKS_TO_GET + 1; i > 0; i--)
		// of those books, we want to generate an index to select from the # of books there are
		bookIndexes.push_back(rand() % bookList.size());

	// code to sort + remove duplicates from vector
	// https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
	set<int> bookSet(bookIndexes.begin(), bookIndexes.end());
	bookIndexes.assign(bookSet.begin(), bookSet.end());

	vector <Book> newBookList;
	// add books to a list, based on the resulting list set
	for (int i = 0; i < (int) bookSet.size(); i++)
		newBookList.push_back(bookList[bookIndexes[i]]);

	// updates reader's book list
	aReader.updateBookList(newBookList);
}

// adds book to a bookshelf, which is in the form of a hash
void addBooksToShelf(vector <Book> &bookList, Qhash<Book> &bookShelf)
{
	for (int i = 0; i < (int) bookList.size(); i++)
		bookShelf.add(bookList[i], bookList[i].hash());
}

// adds readers to the priority queue
void addReadersToQueue(vector<Reader> &readers, Pqueue<Reader> &bookQueue)
{
	for (int i = (int)readers.size() - 1; i >= 0; i--)
	{
		bookQueue.add(readers[i], readers[i].getPriority());
		readers.pop_back();
	}
}

// processes readers in the queue
// those that successfully get all their books will end up back in the reader vector
// to spend a day to "read over the books"
// and will be added to the queue on the next day
// those that do not successfully get all their books will reenter the queue
void processQueue(vector<Reader> &readers, Pqueue<Reader> &bookQueue, Qhash<Book> &bookShelf, const vector<Book> &bookList)
{
	// stores readers that will reenter queue
	Pqueue<Reader> newQueue;
	// stores readers that will not reenter queue immediately
	// to simulate one day passing before they return their books
	vector<Reader> processedReaders;

	// stores # in queue - need to do that since queue will shrink
	int numInQueue = bookQueue.getQueueSize();

	// first process the queue
	for (int i = 0; i < numInQueue; i++)
	{
		// get reader from front of the queue and their priority
		Reader aReader = bookQueue.getFront();
		int priority = bookQueue.getFrontPriority();

		// get that reader's book list
		vector<Book> aBookList = aReader.getBookList();

		// flag to signal requeuing
		bool requeue = false;

		// returns reader's books
		// not originally intended
		// but this is to reduce the effect of a limited book
		// being stuck in limbo
		returnReaderBooks(aReader, bookShelf);

		// process their booklist
		for (int j = (int) aBookList.size() - 1; j >= 0; j--)
		{

			// store book to be found
			Book aBook = aBookList[j];
			// search for book
			int index = bookShelf.getIndex(aBook, aBook.hash());
			// get its data pointer and try to take out the book
			Book *bookPtr = bookShelf.getData(index);
			// process when book is available
			if (bookPtr->bookAvail())
			{
				// take out the book
				bookPtr->takeOutBook();
				// add book to stack of books
				aReader.addBookToStack(aBook);
				// remove from bookList
				aBookList.erase(aBookList.begin() + j);
			}
			// set flag that person has to reenter queue
			else
			{
				requeue = true;
			}
		}

		// if the requeue flag is set
		// add reader to new queue
		if (requeue)
			newQueue.add(aReader, priority + 1);

		// when the reader does not have to requeue
		// add reader to processed readers
		else
			processedReaders.push_back(aReader);

		// remove reader from queue
		bookQueue.remove();
	}

	// now process simulating readers outside of the queue
	// to read/shuffle thru books
	// and then return books
	for (int i = (int) readers.size() - 1; i >= 0; i--)
	{
		// reader "reads thru the books"
		readers[i].readThruBooks();

		// reader returns books
		returnReaderBooks(readers[i], bookShelf);

		// grab new list of books
		generateBooklistsForAReader(bookList, readers[i]);

		// add reader to queue
		newQueue.add(readers[i], readers[i].getPriority());
		// remove reader from list
		readers.pop_back();
	}

	// move appropriate new queue and list over old queue+list
	readers = processedReaders;
	bookQueue = newQueue;
}

// show reader info
void showReaders(vector<Reader> &readers)
{
	// check if there are readers in the vector
	if (readers.size() != 0)
	{
		// loop thru all the readers and show their info
		for (int i = 0; i < (int)readers.size(); i++)
			readers[i].showReaderInfo();
	}

	// display information that all readers are in queue
	else
	{
		cout << "All readers are in queue." << endl;
	}
}

// show list of readers
void showReaderList(vector<Reader> &listReaders)
{
	cout << "Readers: " << endl;
	for (int i = 0; i < (int)listReaders.size(); i++)
		cout << listReaders[i].getName() << endl;
}

// show list of books possible
//void showBookList(vector<Book> &listBooks)
void showBookList(Qhash<Book> &bookShelf)
{
	cout << "Books: " << endl;
	for (int i = 0; i < (int)bookShelf.getQhashSize(); i++)
	{
		// get the book pointer from the data
		Book *aBook = bookShelf.getData(i);
		// check the book is not the default value
		if (!(*aBook == Book()))
			// get the book info
			aBook->showBookInfo(true);
	}
}

// shows hashtable information
void showTable(Qhash<Book> &bookShelf)
{
	bookShelf.showQhashInfo();
}

// helper function that returns a reader's book
void returnReaderBooks(Reader &aReader, Qhash<Book> &bookShelf)
{
	// reader "returns books"

	// get stack of books to process
	stack<Book> bookStack = aReader.getBookStack();

	// reader returns books
	while (!bookStack.empty())
	{
		// get the book at the top of the stack
		Book aBook = bookStack.top();
		// search for book
		int index = bookShelf.getIndex(aBook, aBook.hash());
		// get its data pointer and return the book;
		Book *bookPtr = bookShelf.getData(index);
		// return the book
		bookPtr->returnBook();
		// remove book from stack
		bookStack.pop();
	}

	// remove stack of books from reader
	aReader.emptyBookStack();

}
