#include "SignupMenu.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"
#include "Dao.h"
#include "LoginMenu.h"



void SignupMenu::printSrc()
{
	clrscr();

	print_screen("./screen/SignUpMenu.txt");

	char inputId[20];
	char inputPw[20];
	char inputName[20];

	while (1) {
		gotoxy(22, 5);	//ID 입력
		gets_s(inputId);

		MembersDto member = findByMemberId(inputId);

		if (strcmp(member.member_id, inputId) == 0) {
			print_screen("./screen/SignupMenu.txt");
			gotoxy(22, 6);
			printf("이미 사용중인 아이디입니다.");
		}
		else {
			gotoxy(22, 6);
			printf("사용 가능한 아이디입니다.  ");
			break;
		}
	}

	gotoxy(22, 7);	//PW 입력
	gets_s(inputPw);


	gotoxy(22, 9);	//이름
	gets_s(inputName);

	MembersDto member;
	strcpy_s(member.member_id, inputId);
	strcpy_s(member.pw, inputPw);
	strcpy_s(member.name, inputName);
	strcpy_s(member.role, "user");

	int y = cursorControl(17, 11, 13, 2);

	switch (y) {
	case COMPLETE:
		addMember(member);
		LoginMenu loginmenu;
		//loginmenu.printSrc();
		break;

	case CANCLE:
		//MainMenu mainmenu;
		//mainmenu.printSrc();
		break;
	}
}