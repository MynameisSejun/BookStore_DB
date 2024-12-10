#include "AdminMainMenu.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"

void AdminMainMenu::printSrc()
{
	clrscr();

	print_screen("./screen/AdminMainMenu.txt");

	int y = cursorControl(17, 5, 13, 2);

	switch (y) {
	case BOOKMENU:
		break;

	case SALES:
		break;

	case INOUT:
		break;

	case ADDADMIN:
		break;

	case LOGOUT:
		return;
	}

}
