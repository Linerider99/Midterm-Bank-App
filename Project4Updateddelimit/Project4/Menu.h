#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MenuItem.h"

using namespace std;

class Menu
{
private:
	string title;
	vector<MenuItem> menuItems;
public:
	Menu(string);
	string getTitle();
	void setTitle(string);
	void printTitle();
	void addMenuItem(string);
	bool displayMenu();
	virtual bool selectMenuOption(int) = 0;
};