#include "UserMainMenu.h"
#include "screenControl.h"
#include "UserSearchMenu.h"
#include "UserBuyMenu.h"
#include "LoginMenu.h"
#include <stdio.h>
#include "UserCheckMenu.h"

void UserMainMenu::printSrc()
{
	clrscr();

	print_screen("./screen/UserMainMenu.txt");

	gotoxy(37, 2);
	printf("%s", currentUser.user_id);

	int y = cursorControl(17, 5, 13, 2);

	switch (y) {
	case SEARCH:
		UserSearchMenu bookSearch;
		bookSearch.printSrc();
		break;

	case BUY:
		UserBuyMenu bookbuy;
		bookbuy.printSrc();
		break;

	case CHECK:
		UserCheckMenu checkMenu;
		checkMenu.printSrc();
		break;

	case CANCLE:
		break;

	case LOGOUT:
		return;
	}
}
