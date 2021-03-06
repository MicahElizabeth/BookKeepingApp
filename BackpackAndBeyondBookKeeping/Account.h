/*******************************************************************
* Programmer: Micah Jenkins                                        *
* Date Created: October 9 2015                                     *
* Date Last modified: February 16 2016                             *
********************************************************************/ 

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <queue>
#include "Book.h"
#include "Donor.h"
#include "Utility.h"

using std::string;
using std::unordered_map;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::endl;
using std::getline;
using std::queue;
//using std::find;

//This class manages all the user's information
class Account
{
private:
	string mUsername;
	string mPassword;
	int mBalance;
	int mInitialBalance;
	Book mBook; // key:year value:detailed report for the year
	unordered_map<string, Donor> mDonors; //key:name value:Donor
	Date mYearStart;
	Date mYearEnd;
	vector<int> mCycles;
	vector<int> mYears;

public:
#pragma region Big5
	//constructor
	Account(string username = "", string password = "", int initialBalance = 0)
	{
		mUsername = username;
		mPassword = password;
		mBalance = 0;
		mInitialBalance = initialBalance;
		
	}
	//desetructer
	~Account(){}
	//copy constructor
	Account(const Account &other)
	{
		if (this != &other)
		{
			mUsername = other.mUsername;
			mPassword = other.mPassword;
			mBalance = other.mBalance;
			mBook = other.mBook;
			mDonors = other.mDonors;
			mYearStart = other.mYearStart;
			mYearEnd = other.mYearEnd;
			mInitialBalance = other.mInitialBalance;
			mCycles = other.mCycles;
			mYears = other.mYears;
		}
	}
	//copy operator
	Account & operator= (const Account &rhs)
	{
		if (this != &rhs)
		{
			mUsername = rhs.mUsername;
			mPassword = rhs.mPassword;
			mBalance = rhs.mBalance;
			mBook = rhs.mBook;
			mDonors = rhs.mDonors;
			mYearStart = rhs.mYearStart;
			mYearEnd = rhs.mYearEnd;
			mInitialBalance = rhs.mInitialBalance;
			mCycles = rhs.mCycles;
			mYears = rhs.mYears;
		}
		return *this;
	}
	//move constructor
	Account(Account &&other)
	{
		mUsername = other.mUsername;
		mPassword = other.mPassword;
		mBalance = other.mBalance;
		mBook = other.mBook;
		mDonors = other.mDonors;
		mYearStart = other.mYearStart;
		mYearEnd = other.mYearEnd;
		mInitialBalance = other.mInitialBalance;
		mCycles = other.mCycles;
		mYears = other.mYears;
	}
	//move operator 
	Account & operator= (Account &&rhs)
	{
		mUsername = rhs.mUsername;
		mPassword = rhs.mPassword;
		mBalance = rhs.mBalance;
		mBook = rhs.mBook;
		mDonors = rhs.mDonors;
		mYearStart = rhs.mYearStart;
		mYearEnd = rhs.mYearEnd;
		mInitialBalance = rhs.mInitialBalance;
		mCycles = rhs.mCycles;
		mYears = rhs.mYears;

		return *this;
	}
#pragma endregion
#pragma region Setters Getters
	void setUsername(string username)
	{
		mUsername = username;
	}
	void setPassword(string password)
	{
		mPassword = password;
	}
	void setBalance(int balance)
	{
		mBalance = balance;
	}
	void setBook(Book book)
	{
		mBook = book;
	}
	void setDonors(unordered_map<string, Donor> donors)
	{
		mDonors = donors;
	}
	void setYearStart(Date start)
	{
		mYearStart = start;
	}
	void setYearEnd(Date end)
	{
		mYearEnd = end;
	}
	void setInitialBalance(int balance)
	{
		mInitialBalance = balance;
	}
	void setCycles(vector<int> cycles)
	{
		mCycles = cycles;
	}
	void setYears(vector<int> years)
	{
		mYears = years;
	}
	string getUsername()
	{
		return mUsername;
	}
	string getPassword()
	{
		return mPassword;
	}
	int getBalance()
	{
		return mBalance;
	}
	Book getBook()
	{
		return mBook;
	}
	unordered_map<string, Donor> getDonors()
	{
		return mDonors;
	}
	Date getYearStart()
	{
		return mYearStart;
	}
	Date getYearEnd()
	{
		return mYearEnd;
	}
	int getInitialBalance()
	{
		return mInitialBalance;
	}
	vector<int> getCycles()
	{
		return mCycles;
	}
	vector<int> getYears()
	{
		return mYears;
	}
#pragma endregion
#pragma region Edits

	//addDonation takes in the cycle, name of the donor, 
	//date of the donation, category (which should be donation),
	//and the amount of the donation. It finds the correct place to
	// insert it into the donor list and book and then inserts it,
	//then updates the account balance.
	void addDonation(int cycle, string name, Date date, string category, int amount)
	{
		unordered_map<int, Report> temp = mBook.getBook();
		if (temp.find(cycle) == temp.end())
		{
			mCycles.push_back(cycle);
			//creat new report
			temp[cycle] = Report{ mBalance, mBalance, mYearStart.getDay(), mYearStart.getDay(), date.getYear(),
				mYearEnd.getMonth(), mYearEnd.getDay(), date.getYear(), cycle };
			mBook.setBook(temp);
		}

		if (find(mYears.begin(), mYears.end(), date.getYear()) == mYears.end())
		{
			mYears.push_back(date.getYear());
		}
		mBook.addDonation(cycle, name, date, category, amount);
		
		mDonors[name].addDonation(Donation{ cycle, category, name, date.getMonth(), date.getDay(), date.getYear(), amount });
		
		mBalance += amount;
	}
	
	//Taking in a Donation type, it finds the correct place to insert 
	//it into book and Donor list and inserts it there and updates the balance
	void addDonation(Donation donation)
	{
		unordered_map<int, Report> temp = mBook.getBook();
		Date date = donation.getDate();
		if (temp.find(donation.getCycle()) == temp.end())
		{
			mCycles.push_back(donation.getCycle());
			//creat new report
			temp[donation.getCycle()] = Report{ mBalance, mBalance, mYearStart.getDay(), mYearStart.getDay(), date.getYear(),
				mYearEnd.getMonth(), mYearEnd.getDay(), date.getYear(), donation.getCycle() };
			mBook.setBook(temp);
		}
		if (find(mYears.begin(), mYears.end(), date.getYear()) == mYears.end())
		{
			mYears.push_back(date.getYear());
		}
		mBook.addDonation(donation.getCycle(), donation.getName(), donation.getDate(), donation.getCategory(), donation.getAmount());

		mDonors[donation.getName()].addDonation(Donation{ donation.getCycle(), donation.getCategory(), donation.getName(), 
			date.getMonth(), date.getDay(), date.getYear(), donation.getAmount() });

		mBalance += donation.getAmount();
	}

	//addDonation takes in the cycle, name/description of the item, 
	//date of the purchase, category, and the amount spent, the store
	// and the number of Items. It finds the correct place to
	// insert it into the book and then inserts it and updates the account balance
	void addExpense(int cycle, string name, Date date, string category, double amount, string store, int numItems)
	{
		unordered_map<int, Report> temp = mBook.getBook();
		if (temp.find(cycle) == temp.end())
		{
			mCycles.push_back(cycle);
			//creat new report
			temp[cycle] = Report{ mBalance, mBalance, mYearStart.getDay(), mYearStart.getDay(), date.getYear(), 
				mYearEnd.getMonth(), mYearEnd.getDay(), date.getYear(), cycle };
			mBook.setBook(temp);
		}
		if (find(mYears.begin(), mYears.end(), date.getYear()) == mYears.end())
		{
			mYears.push_back(date.getYear());
		}
		mBook.addExpense(cycle, name, date, category, amount, store, numItems);
		mBalance += amount;
	}

	//Taking in an Expense type, it finds the correct place to insert 
	//it into book, inserts and updates the balance
	void addExpense(Expense expense)
	{
		unordered_map<int, Report> temp = mBook.getBook();
		Date date = expense.getDate();
		if (temp.find(expense.getCycle()) == temp.end())
		{
			mCycles.push_back(expense.getCycle());
			//creat new report
			temp[expense.getCycle()] = Report{ mBalance, mBalance, mYearStart.getDay(), mYearStart.getDay(), date.getYear(),
				mYearEnd.getMonth(), mYearEnd.getDay(), date.getYear(), expense.getCycle() };
			mBook.setBook(temp);
		}
		if (find(mYears.begin(), mYears.end(), date.getYear()) == mYears.end())
		{
			mYears.push_back(date.getYear());
		}
		mBook.addExpense(expense.getCycle(), expense.getName(), date, expense.getCategory(), expense.getAmount(), expense.getStore(), expense.getNumItems());
		mBalance += expense.getAmount();
	}

	//Passes the information on to the book class to remove the information, If it is 
	// successfully completed, it updates the balance, this is to account for user error, 
	// in case the user tries to remove an expense that was never entered.
	void removeExpense(int cycle, string category, Date date, string name, int amount)
	{
		if (mBook.removeExpense(cycle, category, date, name, amount))
		{
			mBalance -= amount; //amount will be negative, so it will actually add to the balance
		}
	}

	//RemoveDonation, checks the donor records and removes that donor from
	//the donor list (since they have not made any donations, saving space)
	//It also passes the info to the book and the donor list to remove the donation
	//if it was successfully removed, the balance is adjusted
	void removeDonation(int cycle, Date date, string name, int amount)
	{
		unordered_map<int, vector<Donation>> temp = mDonors[name].getDonations();
		if (temp.size() == 1)
		{
			vector<Donation> vect = temp[date.getYear()];

			//there is only one entry in the donor's records and the record is meant to be deleted
			if (vect.size() == 1 && vect[0].getDate() == date && vect[0].getAmount() == amount)
			{
				//delete the donor
				// this causes printing problems ==>
				mDonors.erase(name);

				if (mBook.removeDonation(cycle, date, name, amount))
				{
					mBalance -= amount;
				}
			}
		}
		else if (mBook.removeDonation(cycle, date, name, amount) && mDonors[name].removeDonation(date, amount))
		{
			mBalance -= amount;
		}
	}

	//Save makes the name of the file from 'username'.csv
	// It prints the initial account balance, year start and end dates
	// the donor names and contact info, and then the transactions
	// ToDo: Encrypt info before printing to file
	void save()
	{
		string filename = mUsername + ".csv";
		ofstream outfile{filename, ios::out };
		if (outfile.is_open())
		{
			//initialbalance (set at setup)
			outfile << mInitialBalance << endl;
			//yearstart,yearend
			outfile << mYearStart.getDay() << "," << mYearStart.getMonth() << ","
				<< mYearEnd.getDay() << "," << mYearEnd.getMonth() <<","<< endl;
			//donors: mName,mAddress,mEmail,mPhoneNumber,etc
			if (!mDonors.empty())
			{
				for (auto i : mDonors)
				{
					outfile << i.second.getName() << "," << i.second.getAddress() << "," << i.second.getEmail() << "," << i.second.getPhoneNumber() << ",";
				}
			}
			else
			{
				outfile << "," << "," << "," << ",";
			}
			outfile << endl;
			//itterate through cycles
				//cycle,year,day,month,category,name,amount,store,numItems (for donations the "extra info will be blank)
			unordered_map<int, Report> temp = mBook.getBook();
			for (auto j : temp)
			{
				for (auto k : j.second.getReport())
				{
					for (auto f : k.second)
					{
						Date tempD = f->getDate();
						outfile << f->getCycle() << "," << tempD.getYear() << "," << tempD.getDay() << "," << tempD.getMonth() << ","
							<< f->getCategory() << "," << f->getName() << "," << f->getAmount() << ",";
						if (f->getCategory() != "Donation")
						{
							//Transaction *tempT = new Transaction(f);
							outfile << static_cast<Expense*>(f)->getStore() << "," << static_cast<Expense*>(f)->getNumItems() << ",";
						}
						outfile << endl;
					}
				}
			}
				
			
			outfile.close();
		}

	}

	

	//Load reads in the user's info from 'username'.csv
	//Reads each line of the file and parses it appropriately
	// It starts with the initial account balance and then 
	// as transactions are added, it "recalculates" the balance as
	// if all the transactions are being entered.
	// Add, Dycrypt info
	void load()
	{
		string filename = mUsername + ".csv";
		ifstream infile{ filename, ios::in };
		
		if (infile.is_open())
		{
			int tempAmount = 0;
			int tempInt = 0;
			string tempString = "";
			string tempName = "";
			//read first line: initial balance
			getline(infile, tempString);
			tempAmount = stoi(tempString);
			mInitialBalance = tempAmount;
			mBalance = tempAmount;
			//read second line: startyear endyear
			getline(infile, tempString);
			queue<string> tempQ = Utility::splitter(tempString, ',');
			while (!tempQ.empty())
			{
				tempString = tempQ.front();
				tempQ.pop();
				mYearStart.setDay(stoi(tempString));
				tempString = tempQ.front();
				tempQ.pop();
				mYearStart.setMonth(stoi(tempString));
				tempString = tempQ.front();
				tempQ.pop();
				mYearEnd.setDay(stoi(tempString));
				tempString = tempQ.front();
				tempQ.pop();
				mYearEnd.setMonth(stoi(tempString));

			}
			//read third line list of donors: name address email phone
			getline(infile, tempString);
			tempQ = Utility::splitter(tempString, ',');
			while (!tempQ.empty())
			{
				tempName = tempQ.front();
				tempQ.pop();
				mDonors[tempName].setName(tempName);
				tempString = tempQ.front();
				tempQ.pop();
				mDonors[tempName].setAddress(tempString);
				tempString = tempQ.front();
				tempQ.pop();
				mDonors[tempName].setEmail(tempString);
				tempString = tempQ.front();
				tempQ.pop();
				mDonors[tempName].setPhoneNumber(tempString);
			}
			//read all other lines: cycle year day month category name amount store numItems
			Date tempD{};
			while (infile.good())
			{
				getline(infile, tempString);
				queue<string> tempQ = Utility::splitter(tempString, ',');
				while (!tempQ.empty())
				{
					if (tempQ.size() == 7)
					{
						Donation newDonation{};
						
						newDonation.setCycle(stoi(tempQ.front()));
						tempQ.pop();

						tempD.setYear(stoi(tempQ.front()));
						tempQ.pop();
						tempD.setDay(stoi(tempQ.front()));
						tempQ.pop();
						tempD.setMonth(stoi(tempQ.front()));
						tempQ.pop();
						newDonation.setDate(tempD);

						newDonation.setCategory(tempQ.front());
						tempQ.pop();

						newDonation.setName(tempQ.front());
						tempQ.pop();

						newDonation.setAmount(stod(tempQ.front()));
						tempQ.pop();
						addDonation(newDonation);
					}
					else
					{
						Expense newExpense{};

						newExpense.setCycle(stoi(tempQ.front()));
						tempQ.pop();

						tempD.setYear(stoi(tempQ.front()));
						tempQ.pop();
						tempD.setDay(stoi(tempQ.front()));
						tempQ.pop();
						tempD.setMonth(stoi(tempQ.front()));
						tempQ.pop();
						newExpense.setDate(tempD);

						newExpense.setCategory(tempQ.front());
						tempQ.pop();

						newExpense.setName(tempQ.front());
						tempQ.pop();

						newExpense.setAmount(stoi(tempQ.front()));
						tempQ.pop();

						newExpense.setStore(tempQ.front());
						tempQ.pop();
						newExpense.setNumItems(stoi(tempQ.front()));
						tempQ.pop();

						addExpense(newExpense);
					}
				}//end while 2
			}//end while 1

			infile.close();
		}
	}

	
#pragma endregion
};
#endif