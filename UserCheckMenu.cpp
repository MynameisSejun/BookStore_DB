#include "UserCheckMenu.h"
#include "screenControl.h"
#include "Dao.h"
#include "LoginMenu.h" // currentUser 포함
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "UserMainMenu.h"
#include "AdminMainMenu.h"

const int PAGE_SIZE = 10; // 한 페이지에 표시할 데이터 수

void UserCheckMenu::printSrc() {
    // 사용자 role에 맞춰서 처리
    if (strcmp(currentUser.role, "user") == 0) {
        // 'user'일 경우 본인 구매 내역만 표시
        vector<OrdersDto> orderHistory = selectPurchaseHistory(currentUser.user_id);
        displayPurchaseHistory(orderHistory);
    }
    else if (strcmp(currentUser.role, "admin") == 0) {
        // 'admin'일 경우 모든 사용자 구매 내역 표시
        vector<OrdersDto> orderHistory = selectPurchaseHistory(NULL);  // NULL 전달하여 모든 내역 조회
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

        // 데이터 출력 시작 위치
        int startY = 8;
        int startIdx = currentPage * PAGE_SIZE;
        int endIdx = min(startIdx + PAGE_SIZE, totalRecords);

        // 구매 내역 헤더 출력
        gotoxy(5, 6);
        printf("   아이디             isbn               제목               작가               장르           가격           수량     날짜\n");

        // 현재 페이지의 데이터 출력
        for (int i = startIdx; i < endIdx; ++i) {
            const auto& order = orderHistory[i];
            gotoxy(1, startY + (i - startIdx) + 1); // 1을 더하여 데이터가 헤더 아래에 나오도록
            printf("%-20s %-10s %-25s %-20s %-15s %10d원 %6d %12s\n",
                order.member_id, order.book_ISBN, order.title, order.author, order.genre,
                order.pay_amount, order.count, order.date);
        }

        // 결과 없을 경우 메시지 표시
        if (orderHistory.empty()) {
            gotoxy(5, startY + 1);
            printf("구매 내역이 없습니다.");
        }

        // 페이지 안내 및 사용자 입력 대기
        gotoxy(5, 25); // 하단 안내 메시지 위치
        if (currentPage < totalPages - 1) {
            printf("→: 다음 페이지 | ←: 이전 페이지 | ESC: 이전 화면");
        }
        else if (currentPage > 0) {
            printf("←: 이전 페이지 | ESC: 이전 화면");
        }
        else {
            printf("ESC: 이전 화면");
        }

        // 키 입력 처리
        int key = _getch();
        if (key == 27) { // ESC 키로 이전 화면으로 이동
            if (strcmp(currentUser.role, "user") == 0) {
                // 'user'일 경우 UserMainMenu로 이동
                clrscr();
                UserMainMenu mainMenu;
                mainMenu.printSrc();
            }
            else if (strcmp(currentUser.role, "admin") == 0) {
                // 'admin'일 경우 AdminMainMenu로 이동
                clrscr();
                AdminMainMenu adminMenu;
                adminMenu.printSrc();
            }
            return;
        }
        else if (key == 224) { // 방향키 입력 처리
            int arrowKey = _getch();
            if (arrowKey == 77 && currentPage < totalPages - 1) { // → (오른쪽 화살표)
                ++currentPage;
            }
            else if (arrowKey == 75 && currentPage > 0) { // ← (왼쪽 화살표)
                --currentPage;
            }
        }
    }
}
