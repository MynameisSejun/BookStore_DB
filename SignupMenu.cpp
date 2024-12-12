#include "SignupMenu.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#include "screenControl.h"
#include "Dao.h"
#include "LoginMenu.h"
#include "MainMenu.h"
#include "AdminMainMenu.h"  // ������ ���� �޴� �߰�

void SignupMenu::printSrc()
{
    clrscr();

    print_screen("./screen/SignUpMenu.txt");

    char inputId[20];
    char inputPw[20];
    char inputName[20];

    // ���̵� �Է�
    while (1) {
        gotoxy(22, 5);    // ID �Է� ��ġ
        gets_s(inputId);

        MembersDto member = findByMemberId(inputId);

        if (strcmp(member.member_id, inputId) == 0) {
            print_screen("./screen/SignupMenu.txt");
            gotoxy(22, 6);
            printf("�̹� ������� ���̵��Դϴ�.");
        }
        else {
            gotoxy(22, 6);
            printf("��� ������ ���̵��Դϴ�.  ");
            break;
        }
    }

    // ��й�ȣ �Է�
    gotoxy(22, 7);    // PW �Է� ��ġ
    gets_s(inputPw);

    // �̸� �Է�
    gotoxy(22, 9);    // �̸� �Է� ��ġ
    gets_s(inputName);

    // ���� ������ ����� ���� ����
    MembersDto member;
    strcpy_s(member.member_id, inputId);
    strcpy_s(member.pw, inputPw);
    strcpy_s(member.name, inputName);

    // �α��ε� ������� role�� ���� �� ������ role ����
    if (strcmp(currentUser.role, "admin") == 0) {
        strcpy_s(member.role, "admin");
    }
    else {
        strcpy_s(member.role, "user");
    }

    // ����� �Է� �Ϸ� �� ó��
    int y = cursorControl(17, 11, 13, 2);

    switch (y) {
    case COMPLETE:
        addMember(member);   // �� ����� �߰�
        if (strcmp(member.role, "admin") == 0) {
            // ������ ������ ������� ���� ������ ���� ȭ������ �̵�
            AdminMainMenu adminMainMenu;
            adminMainMenu.printSrc();
        }
        else {
            // �Ϲ� ����� ������ ��� �α��� ȭ������ �̵�
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
            mainmenu.printSrc();   // ���� ȭ������ �̵�
        }
        break;
    }
}
