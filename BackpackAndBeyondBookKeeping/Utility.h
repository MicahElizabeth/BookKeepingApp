/*******************************************************************
* Programmer: Micah Jenkins                                        *
* Date Created: October 9 2015                                     *
* Date Last modified: February 16 2016                             *
********************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <queue>

using std::string;
using std::queue;

class Utility
{
public:
	
	//Splitter takes a string and a single character as a delimiter 
	//and returns the peices of the string split on the delimiters
	//in a queue. Removeing the delimiter.
	static queue<string> splitter(string s, char delim)
	{
		string temp = "";
		queue<string> result{};
		for (auto i : s)
		{
			if (i != delim)
			{
				temp += i;
			}
			else
			{
				result.push(temp);
				temp = "";
			}
		}
		return result;
	}
};
#endif