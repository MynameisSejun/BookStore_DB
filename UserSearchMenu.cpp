#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <vector>

#include "UserSearchMenu.h"
#include "screenControl.h"
#include "Dao.h"
#include "UserMainMenu.h" // UserMainMenu를 위해 추가

using namespace std;

const int PAGE_SIZE = 10; // 한 페이지에 표시할 데이터 개수

void UserSearchMenu::printSrc()
{
    while (1) {
        clrscr(); // 기존 화면 유지하면서 클리어

        // 기존 화면 출력
        print_screen("./screen/UserSearchMenu.txt");

        char inputTitle[100] = "";
        char inputAuthor[100] = "";
        char inputGenre[100] = "";

        // 사용자 입력 받기
        gotoxy(15, 4); // 제목 입력 위치
        gets_s(inputTitle, sizeof(inputTitle));

        gotoxy(15, 6); // 작가 입력 위치
        gets_s(inputAuthor, sizeof(inputAuthor));

        gotoxy(15, 8); // 장르 입력 위치
        gets_s(inputGenre, sizeof(inputGenre));

        // 검색 조건 설정
        BooksDto searchCriteria;
        strcpy_s(searchCriteria.title, inputTitle);
        strcpy_s(searchCriteria.author, inputAuthor);
        strcpy_s(searchCriteria.genre, inputGenre);
        strcpy_s(searchCriteria.isbn, "");

        // 데이터베이스 검색
        vector<BooksDto> foundBooks = selectBooks(searchCriteria);

        // 검색 결과 출력 위치
        int startY = 12; // 데이터 시작 위치
        int totalBooks = foundBooks.size();
        int currentPage = 0;
        int totalPages = (totalBooks + PAGE_SIZE - 1) / PAGE_SIZE;

        while (true) {
            // 검색 결과 헤더 유지
            for (int y = startY; y < startY + PAGE_SIZE; ++y) {
                gotoxy(5, y);
                printf("                                                                                  "); // 기존 내용 삭제
            }

            // 현재 페이지 데이터 출력
            int startIdx = currentPage * PAGE_SIZE;
            int endIdx = min(startIdx + PAGE_SIZE, totalBooks);

            for (int i = startIdx; i < endIdx; ++i) {
                const auto& book = foundBooks[i];
                gotoxy(5, startY + (i - startIdx));
                printf("%-20s %-25s %-20s %-15s %10d원 %10d개",
                    book.isbn, book.title, book.author, book.genre, book.book_price, book.quantity);
            }

            // 결과 없을 경우 메시지 출력
            if (foundBooks.empty()) {
                gotoxy(5, startY);
                printf("검색 결과가 없습니다.");
            }

            // 페이지 안내 및 사용자 입력 대기
            gotoxy(5, 25); // 하단 안내 메시지 위치
            if (foundBooks.empty()) {
                printf("Enter 키: 다시 검색 | ESC 키: 이전 화면");
            }
            else if (currentPage < totalPages - 1) {
                printf("Enter 키: 다음 페이지 | ESC 키: 종료");
            }
            else {
                printf("Enter 키: 계속 검색   | ESC 키: 종료");
            }

            int key = _getch();
            if (key == 27) { // ESC 키
                UserMainMenu mainMenu; // UserMainMenu 호출
                mainMenu.printSrc();
                return;
            }
            else if (key == 13 && foundBooks.empty()) { // Enter 키로 다시 검색
                break;
            }
            else if (key == 13 && currentPage < totalPages - 1) { // Enter 키로 다음 페이지
                ++currentPage;
            }
            else if (key == 13 && currentPage == totalPages - 1) { // 마지막 페이지에서 Enter 키
                break;
            }
        }
    }
}
