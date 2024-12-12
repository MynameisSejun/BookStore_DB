#include "AdminMainMenu.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"
#include "AddBook.h"
#include "UserCheckMenu.h"
#include "SignupMenu.h"
#include "AdminBookMenu.h"
#include "LoginMenu.h"

void AdminMainMenu::printSrc()
{
	clrscr();

	print_screen("./screen/AdminMainMenu.txt");

	int y = cursorControl(17, 5, 13, 2);

	switch (y) {
	case BOOKMENU:
		AdminBookMenu ademinBookMenu;
		ademinBookMenu.printSrc();
		break;

	case SALES:
		UserCheckMenu admincheck;
		admincheck.printSrc();
		break;

	case INOUT:
		break;

	case ADDADMIN:
		SignupMenu adminSignup;
		adminSignup.printSrc();
		break;

	case LOGOUT:
		LoginMenu mainMenu;
		mainMenu.logout();
		break;
	}

}
