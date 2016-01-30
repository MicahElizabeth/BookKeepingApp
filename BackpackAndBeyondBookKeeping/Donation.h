#ifndef DONATION_H
#define DONATION_H
#include "Transaction.h"

class Donation :public Transaction
{
private:
	//the amount will be positive
public:
#pragma region Big5
	//constructor
	Donation(int cycle = 0, string category = "", string name = "", int month = 0, int day = 0, int year = 0, int amount = 0)
		:Transaction(cycle, category, name, month, day, year, amount){}
	//destructor
	~Donation(){}
	//copy constructor
	Donation(const Donation &other) :Transaction(other){}
	//copy operator
	Donation & operator= (const Donation &rhs)
	{
		if (this != &rhs)
		{
			mName = rhs.mName;
			mDate = rhs.mDate;
			mAmount = rhs.mAmount;
		}

		return *this;
	}
	//move constructor
	Donation(Donation &&other) :Transaction(other){}
	//move operator
	Donation & operator= (Donation &&rhs)
	{
		mName = rhs.mName;
		mDate = rhs.mDate;
		mAmount = rhs.mAmount;

		return *this;
	}
#pragma endregion
#pragma region Setters Getters
	//all inherited Transaction
#pragma endregion
};
#endif