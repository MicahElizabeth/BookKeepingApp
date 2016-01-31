#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <queue>

using std::string;
using std::queue;

class Utility
{
public:
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