#pragma once

#include "Menu.h"

class BankMenu : public Menu
{
private:
	void NewAccount();
	void Login();
	void ListAccounts();
public:
	BankMenu(string);
	virtual bool selectMenuOption(int);
};
