#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include "AccountMenu.h"
#include <cstdlib>
#include <stdlib.h>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <map> 



using namespace std;

struct accInfo
{
	string user;
	string pass;
	string bal;
	string trantype;
};

AccountMenu::AccountMenu(string _title) : Menu(_title)
{
	addMenuItem("Deposit");
	addMenuItem("Withdraws");
	addMenuItem("Write Check");
	addMenuItem("List Transactions");
	addMenuItem("Log Out");
}

bool AccountMenu::selectMenuOption(int x)
{
	if (x == 1)
	{
		Deposit();
	}
	if (x == 2)
	{
		Withdraw();
	}
	if (x == 3)
	{
		Check();
	}
	if (x == 4)
	{
		Transactions();
	}

	return false;
}


void AccountMenu::Deposit()
{
	accInfo temp;
	temp.user = getTitle();
	double deposit = -1;
	while (deposit < 0)
	{
		cout << "\nHow much are you depositing?\nEnter 0 if are you not depositing\n";
		cin >> deposit;
		if (cin.fail() || deposit < 0)
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Deposit" << endl;
			deposit = -1;
		}
	}

	if (deposit > 0)
	{
		ofstream outaccountFile;
		outaccountFile.open("Account.txt", ios::out | ios::app);
		
		if (outaccountFile.is_open())
		{
			outaccountFile << endl << temp.user << ",D," << deposit;
		}
		cout << "\nSuccessfully Deposited: $" << deposit << endl;
		outaccountFile.close();
	}
	
	system("pause");

}

void AccountMenu::Withdraw()
{
	std::ifstream accountFile("Account.txt");
	accountFile.open("Account.txt");
	accountFile.clear();
	accountFile.seekg(0, ios::beg);
	//if i dont add this, i have to go through the search twice before it shows what im looking for
	accInfo accounttemp;
	std::map<string, string> balances;
	std::map<string, string>::iterator it;
	double holder = 0;

	if (accountFile.is_open())
	{
		while (!accountFile.eof())
		{
			(std::getline(accountFile, accounttemp.user, ',') &&
				std::getline(accountFile, accounttemp.trantype, ',') &&
				std::getline(accountFile, (accounttemp.bal)));

			//http://www.cplusplus.com/reference/map/map/find/
			// find value given key
			it = balances.find(accounttemp.user);
			if (it != balances.end())
			{
				double holder = 0;
				if (accounttemp.trantype == "D")
				{
					holder = std::stod(accounttemp.bal) + std::stod(balances.find(accounttemp.user)->second);
				}
				if (accounttemp.trantype == "W")
				{
					holder = std::stod(balances.find(accounttemp.user)->second) - std::stod(accounttemp.bal);
				}
				stringstream stream;
				stream << fixed << setprecision(2) << holder;
				string s = stream.str();
				accounttemp.bal = s;
				it->second = accounttemp.bal;
			}
			else
			{
				balances.insert(std::pair<string, string>(accounttemp.user, (accounttemp.bal)));
			}
		}
	}
	accounttemp.user = getTitle();
	it = balances.find(accounttemp.user);
	double withdrawing = -1;
	while (withdrawing < 0)
	{
		cout << "\nHow much are you withdrawing?\nEnter 0 if are you not withdrawing\n";
		cin >> withdrawing;
		if (cin.fail() || withdrawing < 0 || withdrawing > std::stod(it->second))
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Withdrawing" << endl;
			withdrawing = -1;
		}
	}

	if (withdrawing > 0)
	{
		ofstream outaccountFile;
		outaccountFile.open("Account.txt", ios::out | ios::app);

		if (outaccountFile.is_open())
		{
			outaccountFile << endl << accounttemp.user << ",W," << withdrawing;
		}
		cout << "\nSuccessfully Withdrew: $" << withdrawing << endl;
		outaccountFile.close();
	}

	system("pause");
	accountFile.close();
}

void AccountMenu::Check()
{
	std::ifstream accountFile("Account.txt");
	accountFile.open("Account.txt");
	accountFile.clear();
	accountFile.seekg(0, ios::beg);
	//if i dont add this, i have to go through the search twice before it shows what im looking for
	accInfo temp;
	std::map<string, string> balances;
	std::map<string, string>::iterator it;
	double bal_holder = 0;

	if (accountFile.is_open())
	{
		while (!accountFile.eof())
		{
			(std::getline(accountFile, temp.user, ',') &&
				std::getline(accountFile, temp.trantype, ',') &&
				std::getline(accountFile, (temp.bal)));
			//http://www.cplusplus.com/reference/map/map/find/
			// find value given key
			it = balances.find(temp.user);
			if (it != balances.end())
			{
				double holder = 0;
				if (temp.trantype == "D")
				{
					holder = std::stod(temp.bal) + std::stod(balances.find(temp.user)->second);
				}
				if (temp.trantype == "W")
				{
					holder = std::stod(temp.bal) - std::stod(balances.find(temp.user)->second);
				}
				temp.bal = std::to_string(holder);
				stringstream stream;
				stream << fixed << setprecision(2) << holder;
				temp.bal = stream.str();
				balances.insert(std::pair<string, string>(temp.user, (temp.bal)));
			}
			else
			{
				balances.insert(std::pair<string, string>(temp.user, (temp.bal)));
			}
		}
	}
	temp.user = getTitle();
	double withdrawing = -1;
	while (withdrawing < 0)
	{
		cout << "\nHow much are you writing the check for?\nEnter 0 if are you not writing a check\n";
		cin >> withdrawing;
		if (cin.fail() || withdrawing < 0 || withdrawing > std::stod(it->second))
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Number" << endl;
			withdrawing = -1;
		}
	}

	if (withdrawing > 0)
	{
		ofstream outaccountFile;
		outaccountFile.open("Account.txt", ios::out | ios::app);

		if (outaccountFile.is_open())
		{
			outaccountFile << endl << temp.user << ",W," << withdrawing;
		}
		cout << "\nSuccessfully Recorded: $" << withdrawing << endl;
		outaccountFile.close();
	}

	system("pause");
}


void AccountMenu::Transactions()
{
	std::ifstream accountFile("Account.txt");
	accountFile.open("Account.txt");
	accountFile.clear();
	accountFile.seekg(0, ios::beg);
	//if i dont add this, i have to go through the search twice before it shows what im looking for
	accInfo accounttemp;
	std::map<string, string> balances;
	std::map<string, string>::iterator it;
	double bal_holder = 0;

	if (accountFile.is_open())
	{
		while (!accountFile.eof())
		{
			(std::getline(accountFile, accounttemp.user, ',') &&
				std::getline(accountFile, accounttemp.trantype, ',') &&
				std::getline(accountFile, (accounttemp.bal)));
			if (accounttemp.user == getTitle())
			{
								cout << accounttemp.user;
				if (accounttemp.trantype == "W")
				{
					cout << " - $";
					bal_holder = bal_holder - std::stod(accounttemp.bal);
				}
				else
				{
					cout << " + $";
					bal_holder = bal_holder + std::stod(accounttemp.bal);
				}
				cout << accounttemp.bal << endl;
			}

			//http://www.cplusplus.com/reference/map/map/find/
			// find value given key
			
		}
	}
	cout << "Total Balance $" << bal_holder << endl;
	system("pause");
	accountFile.close();
}