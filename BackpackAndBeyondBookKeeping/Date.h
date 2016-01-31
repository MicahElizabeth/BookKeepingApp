#ifndef DATE_H
#define DATE_H

class Date
{
private:
	int mMonth;
	int mDay;
	int mYear;
	
public:
#pragma region Big5
	//constructor
	Date(int month=0, int day=0, int year=0)
	{
		mMonth = month;
		mDay = day;
		mYear = year;
	}
	//destructor
	~Date(){}
	//copy constructor
	Date(const Date &other)
	{
		if (this != &other)
		{
			mMonth = other.mMonth;
			mDay = other.mDay;
			mYear = other.mYear;
		}
	}
	//copy operator
	Date & operator= (const Date &rhs)
	{
		if (this != &rhs)
		{
			mMonth = rhs.mMonth;
			mDay = rhs.mDay;
			mYear = rhs.mYear;
		}
		return *this;
	}
	//move constructor
	Date(Date &&other)
	{
		mMonth = other.mMonth;
		mDay = other.mDay;
		mYear = other.mYear;
	}
	//move operator
	Date & operator= (Date &&rhs)
	{
		mMonth = rhs.mMonth;
		mDay = rhs.mDay;
		mYear = rhs.mYear;
	
		return *this;
	}
	
#pragma endregion
#pragma region Setters Getters
	void setMonth(int month)
	{
		mMonth = month;
	}

	void setDay(int day)
	{
		mDay = day;
	}

	void setYear(int year)
	{
		mYear = year;
	}
	int getYear()
	{
		return mYear;
	}
	int getMonth()
	{
		return mMonth;
	}
	int getDay()
	{
		return mDay;
	}

#pragma endregion
#pragma region overloaded operators
	bool operator> (Date rhs)
	{
		if (mYear > rhs.mYear)
		{
			return true;
		}
		else if (mYear < rhs.mYear)
		{
			return false;
		}
		else
		{
			if (mMonth > rhs.mMonth)
			{
				return true;
			}
			else if (mMonth < rhs.mMonth)
			{
				return false;
			}
			else
			{
				if (mDay > rhs.mDay)
				{
					return true;
				}
				else if (mDay <= rhs.mDay)
				{
					return false;
				}
				
			}
		}
	}
#pragma endregion
#pragma region Other
	bool isValid()
	{
		if (mMonth > 12 || mMonth < 1)
		{
			return false;
		}
		if (mDay > 31 || mDay < 1)
		{
			return false;
		}
		if (mYear > 9999 || mYear < 1900)
		{
			return false;
		}

		return true;
	}
#pragma endregion
};
#endif