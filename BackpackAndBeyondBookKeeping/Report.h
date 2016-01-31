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

	int getTotalExpenditures()
	{
		int total = 0;

		for (auto i : mReport)
		{
			if (i.first != "Donation")
			{
				for (auto j : mReport[i.first])
				{
					total += j->getAmount();
				}
			}
		}
		return total;
	}

	int getTotalDonations()
	{
		int total;
		for (auto i : mReport["Donation"])
		{
			total += i->getAmount();
		}
		return total;
	}

	vector<tuple<string, int, int> > getMonthTotals()
	{
		vector<tuple<string, int, int> > result{};
		unordered_map < int, tuple<int, int>> temp{};

		//sort by month
		for (auto i : mReport)
		{
			for (auto j : mReport[i.first])
			{
				if (i.first == "Donation")
				{
					Date d = j->getDate();
					get<1>(temp[d.getMonth()]) += j->getAmount();
				}
				else
				{
					Date d = j->getDate();
					get<0>(temp[d.getMonth()]) += j->getAmount();
				}
			}
		}

		//put into the vector
		result.push_back(tuple<string, int, int>{"January", get<0>(temp[1]), get<1>(temp[1])});
		result.push_back(tuple<string, int, int>{"February", get<0>(temp[2]), get<1>(temp[2])});
		result.push_back(tuple<string, int, int>{"March", get<0>(temp[3]), get<1>(temp[3])});
		result.push_back(tuple<string, int, int>{"April", get<0>(temp[4]), get<1>(temp[4])});
		result.push_back(tuple<string, int, int>{"May", get<0>(temp[5]), get<1>(temp[5])});
		result.push_back(tuple<string, int, int>{"June", get<0>(temp[6]), get<1>(temp[6])});
		result.push_back(tuple<string, int, int>{"July", get<0>(temp[7]), get<1>(temp[7])});
		result.push_back(tuple<string, int, int>{"August", get<0>(temp[8]), get<1>(temp[8])});
		result.push_back(tuple<string, int, int>{"September", get<0>(temp[9]), get<1>(temp[9])});
		result.push_back(tuple<string, int, int>{"October", get<0>(temp[10]), get<1>(temp[10])});
		result.push_back(tuple<string, int, int>{"November", get<0>(temp[11]), get<1>(temp[11])});
		result.push_back(tuple<string, int, int>{"December", get<0>(temp[12]), get<1>(temp[12])});
	}

	vector<tuple<string, int>> getCategoryTotals()
	{
		vector<tuple<string, int> > result{};
		
		for (auto i : mReport)
		{
			int temp = 0;
			for (auto j : mReport[i.first])
			{
				temp += j->getAmount();
			}

			result.push_back(tuple<string, int>{i.first, temp});
		}

		return result;
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
	bool removeDonation(Date date, string name, int amount)
	{
		for (int i = 0; i < mReport["Donation"].size(); i++)
		{
			if (mReport["Donation"][i]->getDate() == date && mReport["Donation"][i]->getName() == name && mReport["Donation"][i]->getAmount() == amount)
			{
				mReport["Donation"].erase(mReport["Donation"].begin() + i);
				mEndBalance -= amount;
				return true;
			}
		}

		return false;
	}
	//remove expense
	bool removeExpense(string category,Date date,string name,int amount)
	{
		for (int i = 0; i < mReport[category].size(); i++)
		{
			if (mReport[category][i]->getDate() == date && mReport[category][i]->getName() == name && mReport[category][i]->getAmount() == amount)
			{
				mReport[category].erase(mReport[category].begin()+i);
				mEndBalance -= amount;
				return true;
			}
		}

		return false;
	}
#pragma endregion
};
#endif