#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include "Date.h"
using std::string;

class Transaction
{
protected:
	string mName;
	Date mDate;
	string mCategory;
	int mAmount; //the total price of the items
	int mCycle;
public:
#pragma region Big5
	//constructor
	Transaction(int cycle = 0, string category = "", string name = "", int month = 0, int day = 0, int year =  0, int amount = 0)
	{
		mCycle = cycle;
		mCategory = category;
		mName = name;
		mDate.setMonth(month);
		mDate.setDay(day);
		mDate.setYear(year);
		mAmount = amount;
	}
	//destructor
	~Transaction()
	{}

	//copy constructor
	Transaction(const Transaction &other)
	{
		if (this != &other)
		{
			mCycle = other.mCycle;
			mCategory = other.mCategory;
			mName = other.mName;
			mDate = other.mDate;
			mAmount = other.mAmount;
		}
	}
	//copy operator
	Transaction & operator= (const Transaction &rhs)
	{
		if (this != &rhs)
		{
			mCycle = rhs.mCycle;
			mCategory = rhs.mCategory;
			mName = rhs.mName;
			mDate = rhs.mDate;
			mAmount = rhs.mAmount;
		}

		return *this;
	}
	//move constructor
	Transaction(Transaction &&other)
	{
		mCycle = other.mCycle;
		mCategory = other.mCategory;
		mName = other.mName;
		mDate = other.mDate;
		mAmount = other.mAmount;
	}
	//move operator
	Transaction & operator= (Transaction &&rhs)
	{
		mCycle = rhs.mCycle;
		mCategory = rhs.mCategory;
		mName = rhs.mName;
		mDate = rhs.mDate;
		mAmount = rhs.mAmount;
		return *this;
	}
#pragma endregion
#pragma region Setters Getters
	void setName(string name)
	{
		mName = name;
	}

	void setDate(Date date)
	{
		mDate = date;
	}

	void setAmount(int amount)
	{
		mAmount = amount;
	}
	void setCategory(string category)
	{
		mCategory = category;
	}
	void setCycle(int cycle)
	{
		mCycle = cycle;
	}
	string getName()
	{
		return mName;
	}

	Date getDate()
	{
		return mDate;
	}

	int getAmount()
	{
		return mAmount;
	}
	string getCategory()
	{
		return mCategory;
	}
	int getCycle()
	{
		return mCycle;
	}
#pragma endregion
};
#endif