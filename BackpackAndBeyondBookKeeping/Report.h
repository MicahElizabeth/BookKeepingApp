#ifndef REPORT_H
#define REPORT_H

#include <unordered_map>
#include <vector>
#include "Transaction.h"
#include "Expense.h"
#include "Donation.h"
#include <queue>
using std::unordered_map;
using std::vector;

//report file names will be 'username''type''date-date'
class Report
{
private:
	unordered_map<string, vector<Transaction*>> mReport; // key: category vaule: vector of Transactions
	int mStartBalance;
	int mEndBalance;
	Date mStartDate;
	Date mEndDate;
	int mId;

public:
#pragma region Big5
	//constructor
	Report(int startbalance=0, int endbalance = 0, int startMonth=0, int startDay=0, int startYear = 0, int endMonth=0, int endDay=0, int endYear = 0, int id = -1)
	{
		mStartBalance = startbalance;
		mEndBalance = endbalance;
		Date temp1{ startMonth, startDay, startYear };
		Date temp2{ endMonth, endDay, endYear };

		mStartDate = temp1;
		mEndDate = temp2;
		mId = id;
	}

	//destructor
	~Report(){}
	//copy constructor
	Report(const Report &other)
	{
		if (this != &other)
		{
			mReport = other.mReport;
			mStartBalance = other.mStartBalance;
			mEndBalance = other.mEndBalance;
			mStartDate = other.mStartDate;
			mEndDate = other.mEndDate;
			mId = other.mId;
		}
	}
	//copy operator
	Report & operator= (const Report &rhs)
	{
		if (this != &rhs)
		{
			mReport = rhs.mReport;
			mStartBalance = rhs.mStartBalance;
			mEndBalance = rhs.mEndBalance;
			mStartDate = rhs.mStartDate;
			mEndDate = rhs.mEndDate;
			mId = rhs.mId;
		}
		return *this;
	}
	//move constructor
	Report(Report &&other)
	{


		mReport = other.mReport;
		mStartBalance = other.mStartBalance;
		mEndBalance = other.mEndBalance;
		mStartDate = other.mStartDate;
		mEndDate = other.mEndDate;
		mId = other.mId;

	}

	//move operator
	Report & operator= (Report &&rhs)
	{
		mReport = rhs.mReport;
		mStartBalance = rhs.mStartBalance;
		mEndBalance = rhs.mEndBalance;
		mStartDate = rhs.mStartDate;
		mEndDate = rhs.mEndDate;
		mId = rhs.mId;
	
		return *this;
	}
#pragma endregion
#pragma region Setters Getters
	void setReport(unordered_map<string, vector<Transaction*>> report)
	{
		mReport = report;
	}
	void setStartBalance(int startBalance)
	{
		mStartBalance = startBalance;
	}
	void setEndBalance(int endBalance)
	{
		mEndBalance = endBalance;
	}
	void setStartDate(Date startDate)
	{
		mStartDate = startDate;
	}
	void setEndDate(Date endDate)
	{
		mEndDate = endDate;
	}
	void setId(int id)
	{
		mId = id;
	}
	unordered_map<string, vector<Transaction*>> getReport()
	{
		return mReport;
	}
	int getStartBalance()
	{
		return mStartBalance;
	}
	int getEndBalance()
	{
		return mEndBalance;
	}
	Date getStartDate()
	{
		return mStartDate;
	}
	Date getEndDate()
	{
		return mEndDate;
	}
	int getId()
	{
		return mId;
	}
#pragma endregion
#pragma region writing and saving
	
	//produce report(string startdate, string enddate) --> by date, month sepparated, donations and expenses separated
	//produce report donations
	//produce report expenses
	//produce report by type
	//produce report(month)
#pragma endregion
#pragma region add and remove
	//add donation
	void addDonation(int cycle, string name, Date date, string category, int amount)
	{
		if (date > mEndDate)
		{
			mEndDate = date;
		}
		mReport[category].push_back(new Donation{cycle, category, name, date.getMonth(), date.getDay(), date.getYear(), amount });
		mEndBalance += amount;
	}
	//add expense
	void addExpense(int cycle, string name, Date date, string category, int amount, string store, int numItems)
	{
		if (date > mEndDate)
		{
			mEndDate = date;
		}
		mReport[category].push_back(new Expense{cycle, category, store, numItems, name, date.getMonth(), date.getDay(), date.getYear(), amount });
		mEndBalance += amount;
	}
	//remove donation
	//remove expense
#pragma endregion
};
#endif