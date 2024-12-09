#include "LoginMenu.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"
#include "Dao.h"

void LoginMenu::printSrc()
{
	clrscr();

	print_screen("./screen/Login_User_Menu.txt");
}