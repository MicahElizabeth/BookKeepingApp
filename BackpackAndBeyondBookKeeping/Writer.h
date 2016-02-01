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
			outfile << "Start Balance:,$" << report.getStartBalance() / 100 << "." << abs(report.getStartBalance() % 10)<<
				",," << "Total Expenditures: ,$" << (expen / 100) << "." << abs((expen % 10) ) << endl;
			outfile << "End Balance:,$" << tempBook[cycle].getEndBalance() / 100 << "." << abs((tempBook[cycle].getEndBalance() % 10) ) <<
				",," << "Total Income: ,$" << donat / 100 << "." << abs((donat % 10) ) << endl;
			
			
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
							<< ",$" << (k->getAmount()/100)<<"."
							<< abs((k->getAmount() % 10)) << "," << endl;

						catTotal += k->getAmount();
					}

					outfile << ",,," << j.first << ",$"
						<< (catTotal / 100) << "." << abs((catTotal % 10)) << endl;

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
					<< ",$" << i->getAmount()/100 <<"."<<abs((i->getAmount()%10))<< "," << endl;
			}

			//Monthly Breakdown
			outfile << "Monthly Breakdown," << endl;
			outfile << ",," << "Month,,Expendatures,Donations," << endl;
			for (auto i : report.getMonthTotals())
			{
				outfile << ",," << get<0>(i) << ",,$" << 
					get<1>(i) / 100 << "." << abs((get<1>(i) % 10)) <<
					",$" << get<2>(i) / 100 << "." << abs((get<2>(i) % 10)) << "," << endl;
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

		if (outfile.is_open())
		{
			unordered_map<int, Report> tempBook = book.getBook();
			Report report = tempBook[cycle];
			int expen = report.getTotalExpenditures();
			int donat = report.getTotalDonations();
			//Summary: 
			outfile << "Cycle:," << cycle << endl;
			outfile << "Start Balance:,$" << report.getStartBalance() / 100 << "." << abs(report.getStartBalance() % 10) <<
				",," << "Total Expenditures: ,$" << expen / 100 << "." << abs(expen % 10) << endl;
			outfile << "End Balance:,$" << tempBook[cycle].getEndBalance() / 100 << "." << abs(tempBook[cycle].getEndBalance() % 10) <<
				",," << "Total Income: ,$" << donat / 100 << "." << abs(donat % 10) << endl;

			//Monthly Breakdown
			outfile << "Monthly Breakdown," << endl;
			outfile << ",," << "Month,,Expendatures,Donations," << endl;
			for (auto i : report.getMonthTotals())
			{
				outfile << ",," << get<0>(i) << ",,$" <<
					get<1>(i) / 100 << "." << abs((get<1>(i) % 10)) <<
					",$" << get<2>(i) / 100 << "." << abs((get<2>(i) % 10)) << "," << endl;
			}

			outfile.close();

		}

	}

	static void DonorReport(int year, unordered_map<string, Donor> donors, string account)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%m-%d-%Y", timeinfo);
		string str(buffer);

		string filename = to_string(year) + account + str + "Donors.csv";
		ofstream outfile{ filename, ios::out };

		if (outfile.is_open())
		{

			outfile << "Name,Address,Email,Phone,Year Total, Total Year To Date," << endl;
			for (auto i : donors)
			{
				int temp = 0;
				Donor d = i.second;
				unordered_map<int, vector<Donation>> rec = d.getDonations();
				for (auto j : rec[year])
				{
					temp += j.getAmount();
				}
				//name, address, email, phone, Amount this cycle, total amount, 
				outfile << d.getName() << "," << d.getAddress() << ","
					<< d.getEmail() << "," << d.getPhoneNumber() << ",$"
					<< temp / 100 << "." << abs(temp % 10) << ",$" << d.getTotal() / 100
					<< "." << abs(d.getTotal() % 10) << "," << endl;
			}
			outfile.close();
		}
	}

	static void DonorReceipt(string name, int year, unordered_map<string, Donor> donors)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%m-%d-%Y", timeinfo);
		string str(buffer);

		string filename = to_string(year) + name + str + "Receipt.csv";
		ofstream outfile{ filename, ios::out };

		if (outfile.is_open())
		{

			Donor d = donors[name];
			outfile << d.getName() << "," << endl;
			outfile << d.getAddress() << "," << d.getEmail() << "," << d.getPhoneNumber() << "," << endl;

			outfile << "Date,,Amount," << endl;
			int temp = 0;

			unordered_map<int, vector<Donation>> rec = d.getDonations();
			for (auto j : rec[year])
			{
				Date date = j.getDate();
				outfile << date.getMonth() << "-" << date.getDay() << "-" << date.getYear()
					<< ",,$" << j.getAmount() / 100 << "." << abs(j.getAmount() % 10) << "," << endl;
				temp += j.getAmount();
			}
			//name, address, email, phone, Amount this cycle, total amount, 
			outfile << "Year Total:,,$" << temp / 100 << "." << abs(temp % 10) << "," << endl;
			outfile << "Total To Date:,,$" << d.getTotal() / 100 << "."
				<< abs(d.getTotal() % 10) << "," << endl;

			outfile.close();
		}
	}

};
#endif