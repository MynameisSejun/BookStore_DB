#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "screenControl.h"

#include "MainMenu.h"
#include "userLogin.h"
#include "adminLogin.h"
#include "SignupMenu.h"

void MainMenu::printSrc()
{
	while (1) {
		clrscr();

		print_screen("./screen/mainMenu.txt");

		int y = cursorControl(17, 5, 11, 2);

		switch (y) {
		case USERLOGIN:
			UserLogin userLogin;
			//userLogin.printSrc();
			break;

		case SIGNUP:
			SignupMenu singupMenu;
			singupMenu.printSrc();
			break;

		case ADMINLOGIN:
			AdminLogin adminLogin;
			//adminLogin.printSrc();
			break;

		case EXIT:
			exit(0);
		}
	}
}
