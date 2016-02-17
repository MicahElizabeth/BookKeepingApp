/*******************************************************************
* Programmer: Micah Jenkins                                        *
* Date Created: October 9 2015                                     *
* Date Last modified: February 16 2016                             *
********************************************************************/

#ifndef TEST_H
#define TEST_H
#include "UI.h"

class Test
{
public:
#pragma region UI

	static void testGetAmount()
	{
		int cents = 0;
		cout << "Testing UI getAmount\nType 1.00 to exit" << endl;
		while (cents != 100)
		{
			cents = UI::getAmount();
			cout << cents << endl;
			fflush(stdin);
		}
	}
#pragma endregion
};
#endif