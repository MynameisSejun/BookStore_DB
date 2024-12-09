#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"
#include "MainMenu.h"
#include "SignupMenu.h"
#include "Dao.h"
#include "UserLogin.h"


void UserLogin::printSrc()
{
	while (1) {
		clrscr();

		print_screen("./screen/login_screen.txt");

		char id[20];
		char pw[20];

		gotoxy(35, 8);
		gets_s(id);

		gotoxy(35, 10);
		gets_s(pw);

		int y = cursorControl(34, 18, 20, 2);

	}
}
