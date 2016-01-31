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

public:
#pragma region Big5
	//constructor
	Account(string username = "", string password = "", int initialBalance = 0)
	{
		mUsername = username;
		mPassword = password;
		mBalance = 0.00;
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
#pragma endregion
#pragma region Edits
	//add donation
	void addDonation(int cycle, string name, Date date, string category, int amount)
	{
		unordered_map<int, Report> temp = mBook.getBook();
		if (temp.find(cycle) == temp.end())
		{
			//creat new report
			temp[cycle] = Report{ mBalance, mBalance, mYearStart.getDay(), mYearStart.getDay(), date.getYear(),
				mYearEnd.getMonth(), mYearEnd.getDay(), date.getYear(), cycle };
			mBook.setBook(temp);
		}
		mBook.addDonation(cycle, name, date, category, amount);
		
		mDonors[name].addDonation(Donation{ cycle, category, name, date.getMonth(), date.getDay(), date.getYear(), amount });
		
		mBalance += amount;
	}
	void addDonation(Donation donation)
	{
		unordered_map<int, Report> temp = mBook.getBook();
		Date date = donation.getDate();
		if (temp.find(donation.getCycle()) == temp.end())
		{
			
			//creat new report
			temp[donation.getCycle()] = Report{ mBalance, mBalance, mYearStart.getDay(), mYearStart.getDay(), date.getYear(),
				mYearEnd.getMonth(), mYearEnd.getDay(), date.getYear(), donation.getCycle() };
			mBook.setBook(temp);
		}
		mBook.addDonation(donation.getCycle(), donation.getName(), donation.getDate(), donation.getCategory(), donation.getAmount());

		mDonors[donation.getName()].addDonation(Donation{ donation.getCycle(), donation.getCategory(), donation.getName(), 
			date.getMonth(), date.getDay(), date.getYear(), donation.getAmount() });

		mBalance += donation.getAmount();
	}
	//add expense
	void addExpense(int cycle, string name, Date date, string category, double amount, string store, int numItems)
	{
		unordered_map<int, Report> temp = mBook.getBook();
		if (temp.find(cycle) == temp.end())
		{
			//creat new report
			temp[cycle] = Report{ mBalance, mBalance, mYearStart.getDay(), mYearStart.getDay(), date.getYear(), 
				mYearEnd.getMonth(), mYearEnd.getDay(), date.getYear(), cycle };
			mBook.setBook(temp);
		}
		mBook.addExpense(cycle, name, date, category, amount, store, numItems);
		mBalance += amount;
	}
	void addExpense(Expense expense)
	{
		unordered_map<int, Report> temp = mBook.getBook();
		Date date = expense.getDate();
		if (temp.find(expense.getCycle()) == temp.end())
		{
			//creat new report
			temp[expense.getCycle()] = Report{ mBalance, mBalance, mYearStart.getDay(), mYearStart.getDay(), date.getYear(),
				mYearEnd.getMonth(), mYearEnd.getDay(), date.getYear(), expense.getCycle() };
			mBook.setBook(temp);
		}
		mBook.addExpense(expense.getCycle(), expense.getName(), date, expense.getCategory(), expense.getAmount(), expense.getStore(), expense.getNumItems());
		mBalance += expense.getAmount();
	}
	//save
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
							outfile << static_cast<Expense*>(f)->getStore() << "," << static_cast<Expense*>(f)->getNumItems() << "," << endl;
						}
					}
				}
			}
				
			
			outfile.close();
		}

	}
	//load
	void load(string username, string password)
	{
		mUsername = username;
		mPassword = password;
		string filename = mUsername + ".csv";
		ifstream infile{ filename, ios::in };
		
		if (infile.is_open())
		{
			int tempAmount = 0;
			int tempInt = 0;
			string tempString = "";

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
				tempString = tempQ.front();
				tempQ.pop();
				mDonors[tempString].setName(tempString);
				tempString = tempQ.front();
				tempQ.pop();
				mDonors[tempString].setAddress(tempString);
				tempString = tempQ.front();
				tempQ.pop();
				mDonors[tempString].setEmail(tempString);
				tempString = tempQ.front();
				tempQ.pop();
				mDonors[tempString].setPhoneNumber(tempString);
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