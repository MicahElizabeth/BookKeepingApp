#ifndef DONOR_H
#define DONOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Donation.h"
using std::string;
using std::vector;
using std::unordered_map;

class Donor
{
private:
	string mAddress;
	string mEmail;
	string mPhoneNumber;
	string mName;
	unordered_map<int,vector<Donation>> mDonations; //key: year value: donations in a year
	int mTotal;
public:
#pragma region Big5
	//constructor
	Donor(string name = "", string address = "", string email = "", string phonenumber ="")
	{
		mAddress = address;
		mEmail = email;
		mPhoneNumber = phonenumber;
		mName = name;
		mTotal = 0.00;
	}
	//destructor
	~Donor(){}
	//copy constructor
	Donor(const Donor &other)
	{
		if (this != &other)
		{
			mAddress = other.mAddress;
			mEmail = other.mEmail;
			mPhoneNumber = other.mPhoneNumber;
			mName = other.mName;
			mDonations = other.mDonations;
			mTotal = other.mTotal;
		}
	}
	//copy operator
	Donor & operator= (const Donor &rhs)
	{
		if (this != &rhs)
		{
			mAddress = rhs.mAddress;
			mEmail = rhs.mEmail;
			mPhoneNumber = rhs.mPhoneNumber;
			mName = rhs.mName;
			mDonations = rhs.mDonations;
			mTotal = rhs.mTotal;
		}
		return *this;
	}
	//move constructor
	Donor(Donor &&other)
	{
		mAddress = other.mAddress;
		mEmail = other.mEmail;
		mPhoneNumber = other.mPhoneNumber;
		mName = other.mName;
		mDonations = other.mDonations;
		mTotal = other.mTotal;
	}
	//move operator
	Donor & operator= (Donor &&rhs)
	{
		mAddress = rhs.mAddress;
		mEmail = rhs.mEmail;
		mPhoneNumber = rhs.mPhoneNumber;
		mName = rhs.mName;
		mDonations = rhs.mDonations;
		mTotal = rhs.mTotal;
	
		return *this;
	}
#pragma endregion
#pragma region Setters Getters
	void setName(string name)
	{
		mName = name;
	}
	void setDonations(unordered_map<int, vector<Donation>> donations)
	{
		mDonations = donations;
	}
	void setTotal(int total)
	{
		mTotal = total;
	}
	void setAddress(string address)
	{
		mAddress = address;
	}
	void setEmail(string email)
	{
		mEmail = email;
	}
	void setPhoneNumber(string phoneNumber)
	{
		mPhoneNumber = phoneNumber;
	}

	string getName()
	{
		return mName;
	}
	unordered_map<int, vector<Donation>> getDonations()
	{
		return mDonations;
	}
	int getTotal()
	{
		return mTotal;
	}
	string getAddress()
	{
		return mAddress;
	}
	string getEmail()
	{
		return mEmail;
	}
	string getPhoneNumber()
	{
		return mPhoneNumber;
	}
#pragma endregion
	//print donation reciept (date1, date2) filename = 'name''Date1''Date2'
	//add
	void addDonation(Donation donation)
	{
		mDonations[donation.getDate().getYear()].push_back(donation);
		mTotal += donation.getAmount();
	}
	//revove(date, amount)
};
#endif