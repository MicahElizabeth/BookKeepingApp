#include "App.h"
#include "Test.h"
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		
		App myApp{};
		myApp.run();
	}
	else
	{
		Test::testGetAmount();
		//Writer::DetailedReport(1, "Micah");
	}

	return 0;
}