/*TODO: print reports, (make date entry more user friendly), remove expense/donation
Future updates: Add GUI*/

#ifndef APP_H
#define APP_H

#include <unordered_map>
#include <string>
#include <stack>
#include <tuple>
#include "Account.h"
#include "UI.h"
#include "Writer.h"
using std::unordered_map;
using std::string;
using std::stack;
using std::tuple;
using std::get;

class App
{
private:
	unordered_map<string, tuple<string, string>> mAccounts; //key:username value:password
	Account mUser;
	stack<int> mHistory;
	bool mLoggedIn;
	//encrypt
	void encryptAccountInfo(string &username, string &password)
	{
		int temp;
		string tempS = "";
		for (auto i : username)
		{
			temp = i; 
			temp = (((temp -'!') + 20) % 94) + '!';//asccii characters 33 to 126
			tempS += temp;
		}
		username = tempS;
		tempS = "";
		for (auto i : password)
		{
			temp = i;
			temp = (((temp -'!') + 10) % 94 )+ '!';//asccii characters 33 to 126
			tempS += temp;
		}
		password = tempS;
	}
	//decrypt
	void decryptUserInfo(string &username, string &password)
	{
		int temp;
		string tempS = "";
		for (auto i : username)
		{
			temp = i;
			temp = temp - '!' - 20;
			if (temp < 0)
			{
				temp = ('~' + 1) + temp;
			}
			else
			{
				temp += '!';
			}
			tempS += temp;
		}
		username = tempS;
		tempS = "";
		for (auto i : password)
		{
			temp = i;
			temp = temp - '!' - 10;//asccii characters 33 to 126
			if (temp < 0)
			{
				temp = ('~' + 1) + temp;
			}
			else
			{
				temp += '!';
			}
			tempS += temp;
		}
		password = tempS;
	}
	
public:
#pragma region Big5
	//constructor
	App()
	{
		mLoggedIn = false;
	}
	//destructor
	~App(){}
	//copy Constructor
	App(const App &other)
	{
		if (this != &other)
		{
			mAccounts = other.mAccounts;
			mUser = other.mUser;
			mHistory = other.mHistory;
			mLoggedIn = other.mLoggedIn;
		}
	}
	//copy operator
	App & operator= (const App &rhs)
	{
		if (this != &rhs)
		{
			mAccounts = rhs.mAccounts;
			mUser = rhs.mUser;
			mHistory = rhs.mHistory;
			mLoggedIn = rhs.mLoggedIn;
		}
		return *this;
	}
	//move constructor
	App(App &&other)
	{
		mAccounts = other.mAccounts;
		mUser = other.mUser;
		mHistory = other.mHistory;
		mLoggedIn = other.mLoggedIn;
	}
	//move operator
	App & operator= (App &&rhs)
	{
		mAccounts = rhs.mAccounts;
		mUser = rhs.mUser;
		mHistory = rhs.mHistory;
		mLoggedIn = rhs.mLoggedIn;
		return *this;
	}
#pragma endregion
#pragma region Setters Getters
	void setAccounts(unordered_map<string, tuple<string, string>> accounts)
	{
		mAccounts = accounts;
	}
	void setUser(Account user)
	{
		mUser = user;
	}
	void setHistory(stack<int> history)
	{
		mHistory = history;
	}
	void setLoggedIn(bool status)
	{
		mLoggedIn = status;
	}
	unordered_map<string,tuple<string, string>> getAccounts()
	{
		return mAccounts;
	}
	Account getUser()
	{
		return mUser;
	}
	stack<int> getHistory()
	{
		return mHistory;
	}
	bool getLoggedIn()
	{
		return mLoggedIn;
	}
#pragma endregion
#pragma region Login Stuff
	
	//make new account(username, password)
	void newAccount()
	{
		mHistory.push(UI::newAccountTitle());
		if (mHistory.top() == 0)
		{
			//take off the continue
			mHistory.pop();
			string temp1{};
			vector<string> tempPass{};
			int temp = 1;

			do
			{
				temp1 = UI::getUsername();
				if (isValidNewUsername(temp1))
				{
					temp = 0;
				}
				else
				{
					temp = UI::putNewUserError();
				}
			} while (temp == 1);

			if (temp == 0)//successful new username
			{
				do
				{
					tempPass = UI::getNewPassword();
					if (isValidNewPassword(tempPass[0], tempPass[1]))
					{
						temp == 0;
					}
					else
					{
						temp = UI::putNewPasswordError();
					}
				} while (temp == 1);

				if (temp == 0)//vaild new username and password
				{
					//put in list of accounts
					mAccounts[temp1] = tuple<string,string>(temp1, tempPass[0]);
					
					//create new account
					mUser = *(new Account(temp1, tempPass[0], UI::getBalance())); //initialbalance
					mUser.setBalance(mUser.getInitialBalance());
					mLoggedIn = true;
					editYearStart();
					editYearEnd();
					mHistory.push(6);
				}
			}
			
		}
	}
	//log in
	void logIn()
	{
		//make sure they want to log in
		mHistory.push(UI::loginTitle());
		if (mHistory.top() == 0)
		{
			//take off the continue
			mHistory.pop();
			string temp1{}, temp2{};
			int temp = 1;
			do
			{
				temp1 = UI::getUsername();
				temp2 = UI::getPassword();
				if (isUsername(temp1) && isCorrectPassword(temp1, temp2))
				{
					temp = 0;
					mLoggedIn = true;
					mUser.load(temp1, temp2);
				}
				else
				{
					temp = UI::putLoginError();
				}
			} while (temp == 1);

			if (temp == 0)
			{
				mHistory.push(6);
			}
			else if (temp == 2)
			{
				mHistory.push(90);
			}
		}
	}
	//check new username
	bool isValidNewUsername(string username)
	{
		if (!isUsername(username) && username.find(' ')==username.npos && username != "")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//new password
	bool isValidNewPassword(string p1, string p2)
	{
		//password and confermation match, contains no spaces
		//and is not empty ===> valid
		if (p1 == p2 && p1.find(' ') == p1.npos && p1 != "")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//check username exists
	bool isUsername(string username)
	{
		if (mAccounts.find(username) != mAccounts.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//check password matches username
	bool isCorrectPassword(string username, string password)
	{
		if (get<1>(mAccounts[username]) == password)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
#pragma endregion
#pragma region Edit/Add/Remove
	void editUsername()
	{
		string tempS{};
		do
		{
			tempS = UI::getUsername();
		} while (!isValidNewUsername(tempS));

		//Re-associate password
		mAccounts[tempS] = mAccounts[mUser.getUsername()];
		//Remove old username
		mAccounts.erase(mUser.getUsername());
		//Change info in user
		mUser.setUsername(tempS);
	}
	void editPassword()
	{
		vector<string> tempV{};
		do
		{
			tempV = UI::getNewPassword();
		} while (!isValidNewPassword(tempV[0], tempV[1]));

		//Re-associate password
		get<1>(mAccounts[mUser.getUsername()]) = tempV[0];

		//Change info in user
		mUser.setPassword(tempV[0]);
	}
	void editYearStart()
	{
		Date tempD{};
		tempD.setMonth(UI::getMonth());
		tempD.setDay(UI::getDay());
		mUser.setYearStart(tempD);
	}
	void editYearEnd()
	{
		Date tempD{};
		tempD.setMonth(UI::getMonth());
		tempD.setDay(UI::getDay());
		mUser.setYearEnd(tempD);
	}
	void editBalance()
	{
		if (UI::balanceChangeWarning() == 1 && mUser.getPassword() == UI::getPassword())
		{
			mUser.setInitialBalance(UI::getBalance());
		}
	}
	void editInfo()
	{
		mHistory.push(UI::editInfoTitle());
		if (mHistory.top() == 0)
		{
			mHistory.pop(); //pop off the continue
	

			do
			{

				switch (UI::editInfoChoose())
				{
				case 1:
					editUsername();
					break;
				case 2:
					editPassword();
					break;
				case 3:
					editYearStart();
					break;
				case 4:
					editYearEnd();
					break;
				case 5:
					editBalance();
					break;
				case 6:
					editUsername();
					editPassword();
					editYearStart();
					editYearEnd();
					editBalance();
					break;
				case 7: mHistory.push(6);
					break;
				}
			} while (mHistory.top() != 6);

		}
	}

	void addExpense()
	{
		mHistory.push(UI::addExpenseTitle());
		if (mHistory.top() == 0)
		{
			mHistory.pop();
			string name = UI::getName(), category = UI::getCategory(), store = UI::getStore();
			int amount = UI::getAmount() * (-1); //expenses are negative
			int numItems = UI::getNumItems(), cycle = UI::getCycle();
			Date date = UI::getDate();

			mUser.addExpense(cycle, name, date, category, amount, store, numItems);
			mHistory.push(-1);
		}
	}
	void addDonation()
	{
		mHistory.push(UI::addDonationTitle());
		if (mHistory.top() == 0)
		{
			mHistory.pop();
			string name = UI::getName(), category = "Donation";
			int amount = UI::getAmount();
			int cycle = UI::getCycle();
			Date date = UI::getDate();
			unordered_map<string, Donor> temp = mUser.getDonors();
			if (temp.find(name) == temp.end())
			{
				temp[name] = Donor{ name, UI::getAddress(), UI::getEmail(), UI::getPhoneNumber() };
			}
			mUser.setDonors(temp);
			mUser.addDonation(cycle, name, date, category, amount);
			mHistory.push(-1);
		}
		
	}
	void removeExpense()
	{
		//get date, cycle, category, name

		//remove from user.book and update user.balance -> remove from user->book[id]->report[category].find(transaction),update endbalance and end Date?
	}
	void removeDonation()
	{
		//same as removeExpense
		//remove from user.donors[name]->donations[year].remove(transaction), update total
	}
	void reports()
	{
		do
		{
			mHistory.push(UI::reportsChooseView());
			if (mHistory.top() != 6)
			{
				switch (mHistory.top())
				{
				case 1:
					if (UI::isAllCycles())
					{
						Writer::DetailedReport(-1, mUser.getBook());
					}
					else
					{
						Writer::DetailedReport(UI::getCycle(), mUser.getBook());
					}
					break;
				case 2:
					if (UI::isAllCycles())
					{
						//mUser.summaryReport(-1);
					}
					else
					{
						//mUser.summarydReport(UI::getCycle());
					}
					break;
				case 3:
					if (UI::isAllDonors())
					{
						if (UI::isAllCycles())
						{
							//mUser.donorReports(-1);
						}
						else
						{
							//mUser.donorReports(UI::getCycle());
						}
					}
					else
					{
						if (UI::isAllCycles())
						{
							//mUser.donorReports(UI::getName(), -1);
						}
						else
						{
							//mUser.donorReports(UI::getName(), UI::getCycle());
						}
					}
					break;
				case 4:
					if (UI::isAllCycles())
					{
						/*mUser.detailedReport(-1);
						mUser.summaryReport(-1);
						mUser.donorReports(-1);*/
					}
					else
					{
						int cycle = UI::getCycle();
						/*mUser.detailedReport(cycle);
						mUser.summaryReport(cycle);
						mUser.donorReports(cycle);*/
					}
					break;
				default: mHistory.push(-1);
					break;
				}
				mHistory.pop();
			}
		} while (mHistory.top() != 6);
		mHistory.pop();
	}
#pragma endregion
#pragma region Running stuff
	//run() Use a stack to keep track of going back?
	void run()
	{
		//load accounts
		int view = 90;
		loadAccounts();

		mHistory.push(view);
		do
		{
			view = mHistory.top();
			switch (view)
			{
			case -1://BACK
				mHistory.pop(); //pops off the -1
				mHistory.pop();//pops off the top view to go to the previous screen
				//does NOT undo any changes
				break;

			case 90: //HOME & Logout and Save
				if (mLoggedIn)
				{
					//log out and save
					mUser.save();
					//save
					mLoggedIn = false;
				}
				mHistory.push(UI::homeScreen());
				break;

			case 3://HELP
				mHistory.push(UI::helpScreen());
				if (!mLoggedIn && mHistory.top() == 6)
				{
					mHistory.pop();
					mHistory.push(90);
				}
				break;

			case 1://LOGIN
				logIn();
				break;

			case 2: //CREATE ACCOUNT
				newAccount();
				break;
			case 6: //LOGGED IN HOME
				if (mLoggedIn)
				{
					mHistory.push(UI::loggedIn(mUser.getUsername()));
				}
				else
				{
					mHistory.push(-1);
				}
				break;
			case 10://VIEW ACCOUNT INFO
				if (mLoggedIn)
				{
					mHistory.push(UI::viewAccountInfo(mUser));
				}
				else
				{
					mHistory.push(-1);
				}
				break;
			case 20://EDIT ACCOUNT INFO
				if (mLoggedIn)
				{
					editInfo();
				}
				else
				{
					mHistory.push(-1);
				}
				break;
			case 30://ADD EXPENSE
				addExpense();
				break;
			case 40: //ADD DONATION
				addDonation();
				
				break;
			case 70: //REPORTS
				reports();
			case 50: //REMOVE EXPENSE
				removeExpense();
				break;
			case 60: //REMOVE DONATION
				removeDonation();
				break;
			default:
				break;
			}
		} while (mHistory.top() != 4);
		
		saveAccounts();
		
	}
	
	//laod user/passwords
	void loadAccounts()
	{
		ifstream infile{ "Accounts.txt", ios::in };

		if (infile.is_open())
		{
			string line = "";
			queue<string> q{};

			while (infile.good())
			{
				getline(infile, line);
				q = Utility::splitter(line, ' ');
				if (!q.empty())
				{
					string tempName = q.front();
					q.pop();
					string tempPass = q.front();
					decryptUserInfo(tempName, tempPass);
					tuple<string, string> tempTupe{ tempName, tempPass };

					mAccounts[tempName] = tempTupe;
				}
			}

			infile.close();
		}
		else
		{
			cout << "Error: Could not open accounts file" << endl;
		}
	}

	void saveAccounts()
	{
		ofstream outfile{"Accounts.txt", ios::out };
		if (outfile.is_open())
		{
			for (auto a : mAccounts)
			{
				//encrypt
				encryptAccountInfo(get<0>(a.second), get<1>(a.second));
				//print name, password, \n
				outfile << get<0>(a.second) << " " << get<1>(a.second)<< " " << endl;
			}

			outfile.close();
		}
		else
		{
			cout << "Error: Could not open accounts file" << endl;
		}
	}
#pragma endregion
};
#endif