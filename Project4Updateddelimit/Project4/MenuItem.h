#pragma once

#include <iostream>
#include <string>

using namespace std;

class MenuItem
{
private:
	string menuItemName;
public:
	string getMenuItemName();
	void setMenuItemName(string);
};