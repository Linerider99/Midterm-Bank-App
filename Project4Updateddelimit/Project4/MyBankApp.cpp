#include "BankMenu.h"
#include <cstdlib>
int main()
{
	BankMenu bankMenu = BankMenu("My Bank");
	while (bankMenu.displayMenu());
}