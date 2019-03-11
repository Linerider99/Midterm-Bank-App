#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include "AccountMenu.h"
#include <cstdlib>

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

}

void AccountMenu::Check()
{

}

void AccountMenu::Transactions()
{

}