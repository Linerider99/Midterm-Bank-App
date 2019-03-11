#pragma once

#include "Menu.h"

class AccountMenu : public Menu
{
private:
	void Deposit();
	void Withdraw();
	void Check();
	void Transactions();
public:
	AccountMenu(string);
	virtual bool selectMenuOption(int);
};
