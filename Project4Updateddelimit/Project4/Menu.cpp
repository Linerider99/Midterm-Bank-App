#include "Menu.h"

Menu::Menu(string _title)
{
	setTitle(_title);
}
string Menu::getTitle()
{
	return title;
}

void Menu::setTitle(string s)
{
	title = s;
}

void Menu::printTitle()
{
	system("cls");
	cout << "*** " << getTitle() << " ***" << endl;
	cout << endl;
}

void Menu::addMenuItem(string _itemName)
{
	MenuItem item = MenuItem();
	item.setMenuItemName(_itemName);
	menuItems.push_back(item);
}

bool Menu::displayMenu()
{
	printTitle();

	int item = 0;

	for each(MenuItem mi in menuItems)
	{
		cout << ++item << ". "
			<< mi.getMenuItemName()
			<< endl;
	}

	cin >> item;

	if (item == menuItems.size())
	{
		return false;
	}

	selectMenuOption(item);

	return true;
}