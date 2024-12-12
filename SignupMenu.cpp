#include "SignupMenu.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"
#include "Dao.h"
#include "LoginMenu.h"
#include "MainMenu.h"
#include "AdminMainMenu.h"  // 관리자 메인 메뉴 추가

void SignupMenu::printSrc()
{
    clrscr();

    print_screen("./screen/SignUpMenu.txt");

    char inputId[20];
    char inputPw[20];
    char inputName[20];

    // 아이디 입력
    while (1) {
        gotoxy(22, 5);    // ID 입력 위치
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

    // 비밀번호 입력
    gotoxy(22, 7);    // PW 입력 위치
    gets_s(inputPw);

    // 이름 입력
    gotoxy(22, 9);    // 이름 입력 위치
    gets_s(inputName);

    // 새로 생성할 사용자 정보 설정
    MembersDto member;
    strcpy_s(member.member_id, inputId);
    strcpy_s(member.pw, inputPw);
    strcpy_s(member.name, inputName);

    // 로그인된 사용자의 role에 따라 새 계정의 role 설정
    if (strcmp(currentUser.role, "admin") == 0) {
        strcpy_s(member.role, "admin");
    }
    else {
        strcpy_s(member.role, "user");
    }

    // 사용자 입력 완료 후 처리
    int y = cursorControl(17, 11, 13, 2);

    switch (y) {
    case COMPLETE:
        addMember(member);   // 새 사용자 추가
        if (strcmp(member.role, "admin") == 0) {
            // 관리자 계정을 만들었을 때는 관리자 메인 화면으로 이동
            AdminMainMenu adminMainMenu;
            adminMainMenu.printSrc();
        }
        else {
            // 일반 사용자 계정일 경우 로그인 화면으로 이동
            LoginMenu loginmenu;
            loginmenu.printSrc();
        }
        break;

    case CANCLE:
        if (strcmp(currentUser.role, "admin") == 0) {
            AdminMainMenu adminMainMenu;
            adminMainMenu.printSrc();
        }
        else {
            MainMenu mainmenu;
            mainmenu.printSrc();   // 메인 화면으로 이동
        }
        break;
    }
}
