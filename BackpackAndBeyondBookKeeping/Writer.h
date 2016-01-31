#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <ctime> //for time stuff
#include "Book.h"
using std::string;
using std::to_string;

static class Writer
{
public:

	static void DetailedReport(int cycle, Book book, string account)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%m-%d-%Y", timeinfo);
		string str(buffer);

		string filename = to_string(cycle) + account + str + "Detailed.csv";
		ofstream outfile{filename, ios::out};

		if (outfile.is_open())
		{
			unordered_map<int, Report> tempBook = book.getBook();
			Report report = tempBook[cycle];
			int expen = report.getTotalExpenditures();
			int donat = report.getTotalDonations();
			//Summary: 
			outfile << "Cycle:," << cycle << endl;
			outfile << "Start Balance:,$" << report.getStartBalance() / 100 << "." << report.getStartBalance() % 10<<
				",,"<<"Total Expenditures: ,$"<<expen/100<<"."<<expen%10 << endl;
			outfile << "End Balance:,$" << tempBook[cycle].getEndBalance() / 100 << "." << tempBook[cycle].getEndBalance() % 10 <<
				",," << "Total Income: ,$" << donat / 100 << "." << donat % 10 << endl;
			
			
			//Expenditures
			outfile << "," << endl;
			outfile << "Expenditures," << endl;
			outfile << ",Date,Item,Store,Amount," << endl;
			for (auto j : report.getReport())
			{
				int catTotal = 0;
				if (j.first != "Donation")
				{

					for (auto k : j.second)
					{
						Date date = k->getDate();
						outfile << "," << date.getMonth() << "-" << date.getDay()
							<< "-" << date.getYear() << "," << k->getName()
							<< "," << static_cast<Expense*>(k)->getStore() 
							<< "," << k->getAmount() << ","<<endl;
					}

					outfile << ",,," << j.first << ",$"
						<< catTotal / 100 << "." << catTotal % 10 << endl;

				}
			}

			//Donations
			outfile << "," << endl;
			outfile << "Donations," << endl;
			outfile << ",Date,,Name,Amount," << endl;
			unordered_map<string, vector<Transaction*>> rep = report.getReport();
			for (auto i : rep["Donation"])
			{
				Date date = i->getDate();
				outfile << "," << date.getMonth() << "-" << date.getDay()
					<< "-" << date.getYear() << ",," << i->getName()
					<< "," << i->getAmount() << "," << endl;
			}

			//Monthly Breakdown
			outfile << "Monthly Breakdown," << endl;
			outfile << ",," << "Month,,Expendatures,Donations," << endl;
			for (auto i : report.getMonthTotals())
			{
				outfile << ",," << get<0>(i) << ",," << get<1>(i) <<
					"," << get<2>(i) << "," << endl;
			}

			outfile.close();
		}
		

	}

	static void SummaryReport(int cycle, Book book, string account)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%m-%d-%Y", timeinfo);
		string str(buffer);

		string filename = to_string(cycle) + account + str + "Summary.csv";
		ofstream outfile{ filename, ios::out };

	}

	static void DonorReport(int cycle, Book book, string account)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%m-%d-%Y", timeinfo);
		string str(buffer);

		string filename = to_string(cycle) + account + str + "Donors.csv";
		ofstream outfile{ filename, ios::out };
	}

	static void DonorReport(string name, int cycle, Book book)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%m-%d-%Y", timeinfo);
		string str(buffer);

		string filename = to_string(cycle) + name + str + "Recipt.csv";
		ofstream outfile{ filename, ios::out };
	}

};
#endif