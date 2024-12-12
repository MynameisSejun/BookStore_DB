#include "DeleteBook.h"
#include "Dao.h"
#include "screenControl.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <conio.h>
#include "AdminMainMenu.h"

using namespace std;

const int PAGE_SIZE = 10;

void DeleteBook::printScr() {
    clrscr();
    print_screen("./screen/UserBuyMenu.txt");

    char inputTitle[100] = "";

    // 제목 입력 받기
    gotoxy(15, 4); // 제목 입력 위치
    gets_s(inputTitle, sizeof(inputTitle));

    // 제목을 기준으로 책 목록 검색
    BooksDto searchCriteria;
    strcpy_s(searchCriteria.title, inputTitle);
    strcpy_s(searchCriteria.author, "");
    strcpy_s(searchCriteria.genre, "");
    strcpy_s(searchCriteria.isbn, "");

    // 데이터베이스에서 검색 결과 가져오기
    vector<BooksDto> foundBooks = selectBooks(searchCriteria);
    int totalBooks = foundBooks.size();
    int currentPage = 0;
    int totalPages = (totalBooks + PAGE_SIZE - 1) / PAGE_SIZE;

    while (true) {
        clrscr();
        print_screen("./screen/UserBuyMenu.txt");

        // 데이터 시작 위치
        int startY = 8;
        int startIdx = currentPage * PAGE_SIZE;
        int endIdx = min(startIdx + PAGE_SIZE, totalBooks);

        // 현재 페이지 데이터 출력
        for (int i = startIdx; i < endIdx; ++i) {
            const auto& book = foundBooks[i];
            gotoxy(5, startY + (i - startIdx));
            printf("%-20s %-25s %-20s %-15s %10d원 %10d개\n",
                book.isbn, book.title, book.author, book.genre,
                book.book_price, book.quantity);
        }

        // 결과 없을 경우 메시지 출력
        if (foundBooks.empty()) {
            gotoxy(5, startY);
            printf("검색 결과가 없습니다.");
        }

        // 페이지 안내 및 사용자 입력 대기
        gotoxy(5, 23); // 하단 안내 메시지 위치
        if (foundBooks.empty()) {
            printf("→: 다시 검색 | ESC: 이전 화면");
        }
        else if (currentPage < totalPages - 1) {
            printf("→: 다음 페이지 | ESC: 종료");
        }
        else {
            printf("→: 계속 검색   | ESC: 종료");
        }

        // 커서 이동 및 선택
        int visibleRows = endIdx - startIdx; // 현재 페이지의 데이터 개수
        int prodY = cursorControl(5, startY, startY + visibleRows - 1, 1);

        int bookIndex = startIdx + (prodY - startY);

        // 키 입력 처리
        int key = _getch();
        if (key == 27) { // ESC 키
            AdminMainMenu mainMenu; // UserMainMenu 호출
            mainMenu.printSrc();
        }
        else if (key == 224) { // 방향키 조합 처리
            int arrowKey = _getch();
            if (arrowKey == 77 && currentPage < totalPages - 1) { // → (오른쪽 화살표)
                ++currentPage;
            }
            else if (arrowKey == 75 && currentPage > 0) { // ← (왼쪽 화살표)
                --currentPage;
            }
        }
        else if (key == 13) { // Enter 키로 삭제
            if (foundBooks.empty()) {
                break;
            }

            // 선택한 책
            BooksDto selectedBook = foundBooks[bookIndex];

            // 삭제 여부 확인
            gotoxy(5, 24);
            printf("'%s' 책을 삭제하시겠습니까? (Y/N): ", selectedBook.title);
            char choice = _getch();

            if (toupper(choice) == 'Y') {
                // 책 삭제
                deleteBook(selectedBook.isbn);

                gotoxy(5, 25);
                printf("'%s' 책이 삭제되었습니다.", selectedBook.title);
            }
            else {
                gotoxy(5, 25);
                printf("삭제가 취소되었습니다.");
            }

            _getch(); // 메시지 확인 후 계속
            AdminMainMenu mainmenu;
            mainmenu.printSrc();
            break;
        }
    }
}