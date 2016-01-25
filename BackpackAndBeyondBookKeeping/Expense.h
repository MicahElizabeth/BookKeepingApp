#ifndef EXPENSE_H
#define EXPENSE_H
#include "Transaction.h"

class Expense: public Transaction
{
private:
	string mStore;
	int mNumItems;
	//the amount will be negative
public:
#pragma region Big5
	//constructor
	Expense(int cycle = 0, string category = "", string store = "", int numItems = 0, string name = "", int month = 0, int day = 0, int year = 0, double amount = 0.00) 
		:Transaction(cycle, category, name, month, day, year, amount)
	{
		mStore = store;
		mNumItems = numItems;
	}

	//destructor
	~Expense()
	{

	}

	//copy constructor
	Expense(const Expense &other) :Transaction(other)
	{
		if (this != &other)
		{
			mStore = other.mStore;
			mNumItems = other.mNumItems;
		}
	}
	//copy operator
	Expense & operator= (const Expense &rhs)
	{
		if (this != &rhs)
		{
			mStore = rhs.mStore;
			mNumItems = rhs.mNumItems;
			//Transaction stuff
			mName = rhs.mName;
			mDate = rhs.mDate;
			mAmount = rhs.mAmount;
		}

		return *this;
	}
	//move constructor
	Expense(Expense &&other) :Transaction(other)
	{
		mStore = other.mStore;
		mNumItems = other.mNumItems;
	}
	//move operator
	Expense & operator=(Expense &&rhs)
	{
		mStore = rhs.mStore;
		mNumItems = rhs.mNumItems;
		//Transaction stuff
		mName = rhs.mName;
		mDate = rhs.mDate;
		mAmount = rhs.mAmount;
	}
#pragma endregion
#pragma region Setters Getters
	void setStore(string store)
	{
		mStore = store;
	}
	void setNumItems(int numItems)
	{
		mNumItems = numItems;
	}
	string getStore()
	{
		return mStore;
	}
	int getNumItems()
	{
		return mNumItems;
	}
#pragma endregion

};
#endif