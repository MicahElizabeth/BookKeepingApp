#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <vector>
#include "Account.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::fflush;
using std::getline;

class UI
{
private:
public:
#pragma region Big5
	//constructor
	UI(){}
	//destructor
	~UI(){}
	//copy constructor
	UI(const UI &other){ if (this != &other){} }
	//copy operator
	UI & operator= (const UI &rhs){ if (this != &rhs){} return *this; }
	//move constructor
	UI(UI &&other){}
	//move operator
	UI & operator= (UI &&rhs){ return *this; }
#pragma endregion
#pragma region Getters and Putters
	//These will be phrases to prompt the user, read and return their response. 
		//will NOT validate information given(that's up to the individual classes)
	//username or new username
	static string getUsername()
	{
		fflush(stdin);
		cout << "Username: ";
		string username = "";
		cin >> username;//does not read in the ending newline
		return username;
	}
	//password
	static string getPassword()
	{
		fflush(stdin);
		string password = "";

		cout << "Password: ";
		cin>>password;
		return password;
	}
	
	//new password
	static vector<string> getNewPassword()
	{
		fflush(stdin);
		vector<string> passwords{};
		string p1 = "", p2 = "";

			cout << "Password: ";
			cin >> p1;
			fflush(stdin);
			cout << "Confirm Password: ";
			cin >> p2;
			passwords.push_back(p1);
			passwords.push_back(p2);
		
		return passwords;
	}
	//get address
	static string getAddress()
	{
		fflush(stdin);
		string address = "";

		cout << "Address: ";
		getline(cin, address);
		return address;

	}
	//get email
	static string getEmail()
	{
		fflush(stdin);
		string email = "";

		cout << "Email: ";
		getline(cin, email);
		return email;
	}
	//get phone number
	static string getPhoneNumber()
	{
		fflush(stdin);
		string phone = "";

		cout << "Phone Number: ";
		getline(cin, phone);
		return phone;
	}
	//get date
	static Date getDate()
	{
		Date date{};
		string temp = "";
		queue<string> q{};
		do
		{
			cout << "Date (MM-DD-YYYY): ";
			fflush(stdin);
			cin >> temp;
			temp += "-";
			q = Utility::splitter(temp, '-');
			if (q.size() == 3)
			{
				date.setMonth(stoi(q.front()));
				q.pop();
				date.setDay(stoi(q.front()));
				q.pop();
				date.setYear(stoi(q.front()));
			}
		
		} while (!date.isValid());

		return date;
	}

	//get month
	static int getMonth()
	{
		int month=0;
		string temp = "";
		do
		{
			cout << "Month (1-12): ";
			fflush(stdin);
			cin >> temp;
			month = stoi(temp);

		} while (month > 12 || month < 1);
		return month;
	}

	//get day
	static int getDay()
	{
		int day=0;
		string temp = "";
		do
		{
			cout << "Day (1-31): ";
			fflush(stdin);
			cin >> temp;
			day = stoi(temp);

		} while (day > 31 || day < 1);
		return day;
	}

	//get year
	static int getYear()
	{
		int year = 0;
		string temp = "";
		do
		{
			cout << "Year: ";
			fflush(stdin);
			cin >> temp;
			year = stoi(temp);

		} while (year < 1900 || year > 9999);

		return year;
	}

	//getName
	static string getName()
	{
		fflush(stdin);
		cout << "Name: ";
		string name = "";
		getline(cin, name);
		return name;
	}
	//get category
	static string getCategory()
	{
		fflush(stdin);
		cout << "Category: ";
		string category = "";
		cin >> category;
		return category;
	}
	//get store
	static string getStore()
	{
		fflush(stdin);
		cout << "Store: ";
		string store = "";
		cin >> store;
		return store;
	}
	//get cycle
	static int getCycle()
	{
		int cycle = 0;
		string temp = "";

		cout << "Financial Cycle Number: ";
		fflush(stdin);
		cin >> temp;
		cycle = stoi(temp);

		return cycle;
	}
	//get num items
	static int getNumItems()
	{
		int numItems = 0;
		string temp = "";

		cout << "Number of Items: ";
		fflush(stdin);
		cin >> temp;
		numItems = stoi(temp);

		return numItems;
	}
	//get amount returns the number of cents
	static int getAmount()
	{
		string str = "";
		int amount = 0;

		cout << "Amount: ";
		fflush(stdin);
		cin >> str;
		str += "."; //for the splitter
		queue<string> q = Utility::splitter(str, '.');

		amount = stoi(q.front()) * 100;
		q.pop();
		if (!q.empty())
		{
			amount += stoi(q.front());
		}

		return amount;
	}

	//get balance in cents
	static int getBalance()
	{
		string str = "";
		int balance = 0;

		cout << "New Initial Balance: ";
		fflush(stdin);
		cin >> str;
		str += "."; //for the splitter
		queue<string> q = Utility::splitter(str, '.');

		balance = stoi(q.front()) * 100;
		q.pop();
		if (!q.empty())
		{
			balance += stoi(q.front());
		}

		return balance;
	}

	static int putLoginError()
	{
		int choice = -1;
		string temp = "";
		do
		{
			cout << "Incorrect username and/or password" << endl
				<< endl
				<< "1. Try again?" << endl
				<< "2. Back to Home" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 2 || choice < 1);
		return choice;
	}

	static int putNewUserError()
	{
		int choice = -1;
		string temp = "";
		do
		{
			cout << "Invalid Username" << endl
				<< endl
				<< "1. Try again?" << endl
				<< "2. Back to Home" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 2 || choice < 1);
		return choice;
	}

	static int putNewPasswordError()
	{
		int choice = -1;
		string temp = "";
		do
		{
			cout << "Invalid password or passwords do not match" << endl
				<< endl
				<< "1. Try again?" << endl
				<< "2. Back to Home" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 2 || choice < 1);
		return choice;
	}
	static int balanceChangeWarning()
	{
		int choice = -1;
		string temp = "";
		do
		{
			cout << "WARNING!!!" << endl
				<< "You are about to change your initial account balance." << endl
				<< "Account balances are adjusted automatically." << endl
				<< "Unless you are setting up your account for the first time, it is not recomended to change your account balance." << endl
				<< "Because of this, you will have to approve the change with your password before \ncontinuing." << endl
				<< "1. Continue to change balance" << endl
				<< "2. Back" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 2 || choice < 1);

		return choice;
	}
	static bool isAllCycles()
	{
		int choice = -1;
		string temp = "";
		do
		{
			cout << "Choose one" << endl
				<< "1. All Cycles" << endl
				<< "2. One Cycle" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 2 || choice < 1);
		if (choice == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	static bool isAllDonors()
	{
		int choice = -1;
		string temp = "";
		do
		{
			cout << "Choose one" << endl
				<< "1. All Donors" << endl
				<< "2. One Donor" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 2 || choice < 1);
		if (choice == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
#pragma endregion
#pragma region Views
	// These will be selection screens, read selection and return.
		//will prompt until the number selected is valid
		//let the user select option 1,2, 3... on every page, but
			//add to that number depending on the page so that options
			//are destiguishable.

	//Home Screen no offset needed[70]
	//New Links: Log in, Create Account, Help, Back, Exit
	static int homeScreen()
	{
		system("cls");
		int choice = -1;
		string temp = "";
		do
		{

			cout << "\t\t\t\tMy Black Book" << endl
				<< endl
				<< "Welcome! Type the number of your action and press <enter>." << endl
				<< "1. Log in" << endl
				<< "2. Create Account" << endl
				<< "3. Help" << endl
				<< "4. Exit" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 4 || choice < 1);

		
		return choice;
		
	}

	//help screen[3] will send back the int corrensponding to the screen they went to help from
	//external check to see if the peraon is logged in already
	static int helpScreen()
	{
		system("cls");
		int choice = -1;
		string temp = "";
		do
		{
			cout << "\t\t\t\tHelp" << endl
				<< endl
				<< "NOTE: This product is a prototype. Please Keep additional records for at least \n"
				<< "the first year to ensure accuracy." << endl <<endl
				<< "To save your changes, you must log out of the account from your homescreen.\n"<<endl
				<< "To allow you flexibility in the year start and end dates, this program uses \n"
				<< "financial cycles to keep your data organized. Be sure to keep track of what \n"
				<< "cycle you are on. But don't worry too much, if you make a mistake, you can \n"
				<< "always remove the entry and enter it correctly." << endl <<endl
				<< "Make sure to enter data as instructed and DO NOT enter any commas (,) into your\n"
				<< "responses." << endl <<endl
				<< "To Remove data, you must match the cycle number, date, name, and amount. All \n"
				<< "this information can be found in the detailed records."<<endl <<endl
				<< "To view your data, go to the file that this app is in and select the report you\n"
				<< "wish to view. It will open in Microsoft Excel and you can rearrage the data as \n"
				<< "you see fit. You will see a document called Accounts and one labled with only \n"
				<< "your username. It is best not to open these files and DO NOT delete them." <<endl <<endl
				<< "(1)Back (2)MyHomePage (3)Logout And Save" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 3 || choice < 1);

		if (choice == 2)
		{
			return 6; //logged in home screen
		}
		else if (choice == 3)
		{
			return 90;
		}
		else
		{
			return -1; //back
		}
	}
	//login Screen[1]
	//New Link: continue(0)
	static int loginTitle()
	{
		system("cls");
		int choice = -1;
		string temp;
		do
		{
			cout << "\t\t\t\tLog In" << endl
				<<endl
				<< "1. Continue" << endl
				<< "2. Back" << endl
				<< "3. Help" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice >3 || choice < 1);

		if (choice == 1)
		{
			return 0;
		}
		else if (choice == 3)
		{
			return choice;
		}
		else
		{
			return -1;
		}
	}
	//new user screen[2]
	static int newAccountTitle()
	{
		system("cls");
		int choice = -1;
		string temp = "";
		do
		{
			cout << "\t\t\t\tCreate Account" << endl
				<< endl
				<< "Usernames and Passwords may contain letters, numbers, and symbols." << endl
				<< "Niether Usernames nor passwords may be blank or contain spaces" << endl
				<< endl;
			cout << endl
				<< "1. Continue" << endl
				<< "2. Back" << endl
				<< "3. Help" << endl
				<< "4. Home" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice >4 || choice < 1);

		if (choice == 1)
		{
			return 0;
		}
		else if (choice == 3)
		{
			return choice;
		}
		else if (choice == 4)
		{
			return 70;
		}
		else
		{
			return -1;
		}
	}

	//logged in user screen[6] offset by 10 (previously used commands are set to original call)
	//New Links: View Account Info, Edit Account Info, New Expense, 
		//New Donation, Reports, Log out and Save
	static int loggedIn(string username)
	{
		system("cls");
		int choice = 0;
		string temp = "";
		do
		{
			cout << "\t\t\t\t" << username
				<< endl
				<< "1. View Account Info" << endl
				<< "2. Edit Account Info" << endl
				<< "3. New Expense" << endl
				<< "4. New Donation" << endl
				<< "5. Remove Expense" << endl
				<< "6. Remove Donation" << endl
				<< "7. Reports" << endl
				<< "8. Help" << endl
				<< "9. Log out and Save" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 9 || choice < 1);

		if (choice == 8)
		{
			choice = 3;
		}
		else
		{
			choice *= 10;
		}
		return choice;
	}

	//add expense screen[30]
	static int addExpenseTitle()
	{
		system("cls");
		int choice = -1;
		string temp = "";
		do
		{
			cout << "\t\t\t\tNew Expense" << endl
				<<endl
				<< "1. Continue" << endl
				<< "2. Back" << endl
				<< "3. Help" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice >3 || choice < 1);

		if (choice == 1)
		{
			return 0;
		}
		else if (choice == 3)
		{
			return choice;
		}
		else
		{
			return  -1;
		}
	}
	//add donation screen[40]
	static int addDonationTitle()
	{
		system("cls");
		int choice = -1;
		string temp = "";
		do
		{
			cout << "\t\t\t\tNew Donation" << endl
				<< endl
				<< "1. Continue" << endl
				<< "2. Back" << endl
				<< "3. Help" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice >3 || choice < 1);

		if (choice == 1)
		{
			return 0;
		}
		else if (choice == 3)
		{
			return choice;
		}
		else
		{
			return -1;
		}
	}
	//view account info screen[10]
	static int viewAccountInfo(Account info)
	{
		system("cls");
		int choice = -1;
		int initialBalance = info.getInitialBalance();
		int balance = info.getBalance();
		string temp = "";
		do
		{
			cout << "\t\t\t\tAccount Info" << endl
				<< endl
				<< "Username: " << info.getUsername() << endl
				<< "Password: " << info.getPassword() << endl
				<< "Year Start: " << info.getYearStart().getMonth() << "/" << info.getYearStart().getDay() << endl
				<< "Year End: " << info.getYearEnd().getMonth() << "/" << info.getYearEnd().getDay() << endl
				<< "Initial Balance: " << initialBalance/100<< "."<< initialBalance%100 << endl
				<< "Balance: " <<balance / 100 << "." << balance % 100 << endl
				<< endl;
			cout << "1. Edit" << endl
				<< "2. Back" << endl
				<< "3. Help" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice >3 || choice < 1);

		if (choice == 1)
		{
			return 20;
		}
		else if (choice == 3)
		{
			return choice;
		}
		else
		{
			return -1;
		}
	}
	//edit account info screen[20]
	static int editInfoTitle()
	{
		system("cls");
		int choice = -1;
		string temp = "";
		do
		{
			cout << "\t\t\t\tEdit Info" << endl
				<< endl
				<< "1. Continue" << endl
				<< "2. Back" << endl
				<< "3. Help" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice >3 || choice < 1);

		if (choice == 1)
		{
			return 0;
		}
		else if (choice == 3)
		{
			return choice;
		}
		else
		{
			return -1;
		}
	}
	//edit info [20-0]
	static int editInfoChoose()
	{
		int choice = -1;
		string temp = "";
		do
		{
			cout << "What would you like to edit?" << endl
				<< endl
				<< "1. Username" << endl
				<< "2. Password" << endl
				<< "3. Year Start" << endl
				<< "4. Year End" << endl
				<< "5. Initial Balance" << endl
				<< "6. All" << endl
				<< "7. Home" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 7 || choice < 1);

		return choice;
	}
	//Select Reports[6] screen --> select report, remove donation or remove expense
	//***NOTE: For now, all reports will be sent to csv type files not to the screen
	static int reportsChooseView()
	{
		system("cls");
		int choice = -1;
		string temp = "";
		do
		{
			cout << "\t\t\t\tReports" << endl
				<< endl
				<< "Choose which report(s) to produce:" << endl
				<< "1. Detailed" << endl
				<< "2. Summary" << endl
				<< "3. Donation Recipts" << endl
				<< "4. All Types" << endl
				<< "5. Done" << endl;
			fflush(stdin);
			cin >> temp;
			choice = stoi(temp);
		} while (choice > 5 || choice < 1);
		
		if (choice == 5)
		{
			return 6;
		}
		else
		{
			return choice;
		}
	}
#pragma endregion
};
#endif