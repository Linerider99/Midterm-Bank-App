#include <iostream>
#include <fstream>
#include <sstream>
#include "BankMenu.h"
#include "AccountMenu.h"
#include <string>
#include <stdlib.h>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <map> 

struct accInfo
{
	string user;
	string pass;
	string bal;
	string trantype;
};
BankMenu::BankMenu(string _title) : Menu(_title)
{
	addMenuItem("New Account");
	addMenuItem("List Accounts");
	addMenuItem("Login to Account");
	addMenuItem("Exit");
}

bool BankMenu::selectMenuOption(int x)
{
	if (x == 1)
	{
		NewAccount();
	}
	if (x == 2)
	{
		ListAccounts();
	}
	if (x == 3)
	{
		Login();
	}

	return false;
}

void BankMenu::Login()
{
	accInfo tempLogin;
	accInfo tempSearch;
	tempLogin.user = "0";
	tempLogin.pass = "0";
	std::ifstream loginFile("Login.txt");



	while (tempLogin.user != "9" && tempLogin.pass != "9")
	{
		system("cls");
		cout << "To go back enter 9\nPlease enter your username: \n";
		cin >> tempLogin.user;
		if (tempLogin.user == "9")
		{
			return;
		}
		cout << "Please enter your password: \n";
		cin >> tempLogin.pass;
		if (tempLogin.pass == "9")
		{
			return;
		}

		int offset;
		string line;
		ifstream usersFile;
		loginFile.open("Login.txt");
		bool found = false;

		loginFile.clear();
		loginFile.seekg(0, ios::beg);
		//if i dont add this, i have to go through the search before it finds the login info.

		if (loginFile.is_open())
		{
			while (!loginFile.eof())
			{
				(std::getline(loginFile, tempSearch.user, ',') &&
					std::getline(loginFile, tempSearch.trantype, ',') &&
					std::getline(loginFile, (tempSearch.bal)));

				if (tempSearch.user == tempLogin.user)
				{
					system("cls");
					cout << "\nWelcome " << tempLogin.user << '\n';
					system("pause");
					AccountMenu menu = AccountMenu(tempLogin.user);
					while (menu.displayMenu());
					tempLogin.user = "9";
					tempLogin.pass = "9";
					break;
				}
				else
				{
					cout << "\nUsername and/or password incorrect!\n";
					system("pause");
				}
			}
		}
		loginFile.close();
	}
}

void BankMenu::NewAccount()
{
	
	accInfo temp;
	double deposit = -1;
	system("cls");
	cout << "\nPlease enter a username: ";
	cin >> temp.user;
	cout << "\nPlease enter a password: ";
	cin >> temp.pass;
	
	cout << "\nHow much are you depositing?\nEnter 0 if are you not depositing\n";
	while (deposit < 0)
	{
		cin >> deposit;
		if (cin.fail() || deposit < 0)
		{
			cin.clear();
			cin.ignore();
			system("cls");
			cout << "Invalid Deposit" << endl;
			cout << "How much are you depositing?\nEnter 0 if are you not depositing\n";
			deposit = -1;
		}
	}
	
	ofstream loginFile("Login.txt", std::ios::app);
		if (!loginFile.is_open())
		{
			loginFile.open("Login.txt", std::ios::app);
		}
		loginFile << temp.user << "," << temp.pass << endl;
		loginFile.close();

	ofstream accountFile("Account.txt", std::ios::app);
		if (!accountFile.is_open())
		{
			accountFile.open("Account.txt", std::ios::app);
		}

		accountFile << endl << temp.user << "," << "D," << deposit ;
		accountFile.close();
		cout << "\n Thank you for creating a new account with 'BANK APP 2019!'";
		cout << "\nUsername: " << temp.user;
		cout << "\nBalance: " << deposit << endl;
		system("pause");

}

void BankMenu::ListAccounts()
{	
	std::ifstream loginFile("Login.txt");
	loginFile.open("Login.txt");
	loginFile.clear();
	loginFile.seekg(0, ios::beg);

	std::ifstream accountFile("Account.txt");
	accountFile.open("Account.txt");
	accountFile.clear();
	accountFile.seekg(0, ios::beg);
	//if i dont add this, i have to go through the search twice before it shows what im looking for
	
	accInfo accounttemp;
	accInfo logintemp;
	system("cls");
	cout << "\nList of all current accounts\n\n";

	map<string, string> balances;
	map<string, string>::iterator it;
	double bal_holder = 0;

	if (accountFile.is_open() && loginFile.is_open())
	{
			while (!accountFile.eof())
			{
				(std::getline(accountFile, accounttemp.user, ',') &&
					std::getline(accountFile, accounttemp.trantype, ',') &&
					std::getline(accountFile, (accounttemp.bal)));
				if (!loginFile.eof())
				{
					(std::getline(loginFile, logintemp.user, ',') &&
						std::getline(loginFile, (logintemp.pass)));
					cout << logintemp.user << endl;
				}

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
		cout << "\n";



		int showmore = -1;
		while (showmore < 0)
		{
			cout << "\nShow Balances?\n1. Yes\n2. No\n";
			cin >> showmore;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				cout << "Invalid Option" << endl;
				showmore = -1;
			}
			if (showmore < 0 || showmore > 2)
			{
				cin.clear();
				cin.ignore();
				cout << "Invalid Option" << endl;
				showmore = -1;
			}
		}


		if (showmore == 1)
		{

			system("cls");
			cout << "\nList of all current accounts\n\n";


			for (it = balances.begin(); it != balances.end(); it++)
			{
				std::cout << it->first  // string (key)
					<< "\t $"
					<< fixed << setprecision(2) << it->second   // string's value 
					<< std::endl;
			}
			cout << "\n";
			system("pause");
	}
	loginFile.close();
	accountFile.close();
}