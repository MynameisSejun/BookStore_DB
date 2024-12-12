#include "LoginMenu.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"
#include "Dao.h"
#include "UserMainMenu.h"
#include "AdminMainMenu.h"
#include "MainMenu.h"

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

void LoginMenu::logout()
{
	// 로그인된 사용자 정보 초기화
	memset(&currentUser, 0, sizeof(currentUser));  // currentUser 구조체를 0으로 초기화

	// 로그인 화면으로 이동
	MainMenu mainMenu;
	mainMenu.printSrc();
}