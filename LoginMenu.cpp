#include "LoginMenu.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"
#include "Dao.h"
#include "UserMainMenu.h"
#include "AdminMainMenu.h"

UserDto currentUser = {};

void LoginMenu::printSrc()
{
	clrscr();

	print_screen("./screen/LoginMenu.txt");

	char id[20];
	char pw[20];

	gotoxy(22, 5);
	gets_s(id);

	gotoxy(22, 7);
	gets_s(pw);

	int y = cursorControl(17, 9, 11, 2);

	switch (y) {
		case SIGNIN:
			if (strcmp(pw, (findByMemberId(id)).pw) == 0) {
				MembersDto user = select_MemberId(id);

				strcpy_s(currentUser.user_id, user.member_id);
				strcpy_s(currentUser.name, user.name);
				strcpy_s(currentUser.role, user.role);

				if (strcmp(user.role, "admin") == 0) {
					AdminMainMenu adminMainMenu;
					adminMainMenu.printSrc();
					break;
				}
				UserMainMenu userMainMenu;
				userMainMenu.printSrc();
			}
		case CANCLE:
			return;
	}
}