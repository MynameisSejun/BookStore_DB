#include "UserCheckMenu.h"
#include "screenControl.h"
#include "Dao.h"
#include "LoginMenu.h" // currentUser ����
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "UserMainMenu.h"
#include "AdminMainMenu.h"

const int PAGE_SIZE = 10; // �� �������� ǥ���� ������ ��

void UserCheckMenu::printSrc() {
    // ����� role�� ���缭 ó��
    if (strcmp(currentUser.role, "user") == 0) {
        // 'user'�� ��� ���� ���� ������ ǥ��
        vector<OrdersDto> orderHistory = selectPurchaseHistory(currentUser.user_id);
        displayPurchaseHistory(orderHistory);
    }
    else if (strcmp(currentUser.role, "admin") == 0) {
        // 'admin'�� ��� ��� ����� ���� ���� ǥ��
        vector<OrdersDto> orderHistory = selectPurchaseHistory(NULL);  // NULL �����Ͽ� ��� ���� ��ȸ
        displayPurchaseHistory(orderHistory);
    }
}

void UserCheckMenu::displayPurchaseHistory(const vector<OrdersDto>& orderHistory) {
    int totalRecords = orderHistory.size();
    int currentPage = 0;
    int totalPages = (totalRecords + PAGE_SIZE - 1) / PAGE_SIZE;

    while (true) {
        clrscr();
        print_screen("./screen/UserCheckMenu.txt");

        // ������ ��� ���� ��ġ
        int startY = 8;
        int startIdx = currentPage * PAGE_SIZE;
        int endIdx = min(startIdx + PAGE_SIZE, totalRecords);

        // ���� ���� ��� ���
        gotoxy(5, 6);
        printf("   ���̵�             isbn               ����               �۰�               �帣           ����           ����     ��¥\n");

        // ���� �������� ������ ���
        for (int i = startIdx; i < endIdx; ++i) {
            const auto& order = orderHistory[i];
            gotoxy(1, startY + (i - startIdx) + 1); // 1�� ���Ͽ� �����Ͱ� ��� �Ʒ��� ��������
            printf("%-20s %-10s %-25s %-20s %-15s %10d�� %6d %12s\n",
                order.member_id, order.book_ISBN, order.title, order.author, order.genre,
                order.pay_amount, order.count, order.date);
        }

        // ��� ���� ��� �޽��� ǥ��
        if (orderHistory.empty()) {
            gotoxy(5, startY + 1);
            printf("���� ������ �����ϴ�.");
        }

        // ������ �ȳ� �� ����� �Է� ���
        gotoxy(5, 25); // �ϴ� �ȳ� �޽��� ��ġ
        if (currentPage < totalPages - 1) {
            printf("��: ���� ������ | ��: ���� ������ | ESC: ���� ȭ��");
        }
        else if (currentPage > 0) {
            printf("��: ���� ������ | ESC: ���� ȭ��");
        }
        else {
            printf("ESC: ���� ȭ��");
        }

        // Ű �Է� ó��
        int key = _getch();
        if (key == 27) { // ESC Ű�� ���� ȭ������ �̵�
            if (strcmp(currentUser.role, "user") == 0) {
                // 'user'�� ��� UserMainMenu�� �̵�
                clrscr();
                UserMainMenu mainMenu;
                mainMenu.printSrc();
            }
            else if (strcmp(currentUser.role, "admin") == 0) {
                // 'admin'�� ��� AdminMainMenu�� �̵�
                clrscr();
                AdminMainMenu adminMenu;
                adminMenu.printSrc();
            }
            return;
        }
        else if (key == 224) { // ����Ű �Է� ó��
            int arrowKey = _getch();
            if (arrowKey == 77 && currentPage < totalPages - 1) { // �� (������ ȭ��ǥ)
                ++currentPage;
            }
            else if (arrowKey == 75 && currentPage > 0) { // �� (���� ȭ��ǥ)
                --currentPage;
            }
        }
    }
}
