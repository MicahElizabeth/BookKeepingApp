#ifndef BOOK_H
#define BOOK_H

#include "Report.h"

class Book
{
private:
	//year needs to be a range somehow. use id where between date and date = id etc
	unordered_map<int, Report> mBook; // key:id value:detailed report for the year
	vector<int> mYears; //actually ids
public:
#pragma region Big5
	//constructor
	Book()
	{
		
	}
	//destructor
	~Book(){}
	//copy constructor
	Book(const Book &other)
	{
		if (this != &other)
		{
			mBook = other.mBook;
			mYears = other.mYears;
		}
	}
	//copy operator
	Book & operator= (const Book &rhs)
	{
		if (this != &rhs)
		{
			mBook = rhs.mBook;
			mYears = rhs.mYears;
		}
		return *this;
	}
	//move constructor
	Book(Book &&other)
	{
		mBook = other.mBook;
		mYears = other.mYears;
	}
	//move operator
	Book & operator= (Book &&rhs)
	{
		mBook = rhs.mBook;
		mYears = rhs.mYears;
	
		return *this;
	}
#pragma endregion
#pragma region Setters Getters
	void setBook(unordered_map<int, Report> book)
	{
		mBook = book;
	}
	void setYears(vector<int> years)
	{
		mYears = years;
	}
	unordered_map<int, Report> getBook()
	{
		return mBook;
	}
	vector<int> getYears()
	{
		return mYears;
	}
#pragma endregion
#pragma region Edits
	void addExpense(int cycle, string name, Date date, string category, double amount, string store, int numItems)
	{
		mBook[cycle].addExpense(cycle, name, date, category, amount, store, numItems);
		
	}
	void addDonation(int cycle, string name, Date date, string category, double amount)
	{
		
		mBook[cycle].addDonation(cycle, name, date, category, amount);
	}
#pragma endregion
};
#endif