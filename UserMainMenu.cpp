#include "UserMainMenu.h"
#include "screenControl.h"
#include "UserSearchMenu.h"

void UserMainMenu::printSrc()
{
	clrscr();

	print_screen("./screen/UserMainMenu.txt");

	int y = cursorControl(17, 5, 13, 2);

	switch (y) {
	case SEARCH:
		UserSearchMenu bookSearch;
		bookSearch.printSrc();
		break;

	case BUY:
		break;

	case CHECK:
		break;

	case CANCLE:
		break;

	case LOGOUT:
		return;
	}
}
