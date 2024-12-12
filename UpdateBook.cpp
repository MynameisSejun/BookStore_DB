#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <vector>

#include "LoginMenu.h"
#include "UserSearchMenu.h"
#include "screenControl.h"
#include "Dao.h"
#include "UserMainMenu.h"
#include "UserBuyMenu.h"
#include <ctype.h>
#include "UpdateBook.h"
#include "AdminMainMenu.h"

using namespace std;

const int PAGE_SIZE = 10;

void UpdateBook::printSrc()
{
    while (1) {
        clrscr();

        print_screen("./screen/UserBuyMenu.txt");

        char inputTitle[100] = "";

        // 제목 입력받기
        gotoxy(15, 4); // 제목 입력 위치
        gets_s(inputTitle, sizeof(inputTitle));

        // 검색 조건 설정
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
                // 각 항목을 출력 후 줄 바꿈을 명시적으로 처리
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
            gotoxy(5, 21); // 하단 안내 메시지 위치
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
                return;
            }
            else if (key == 224) { // 방향키 조합 처리
                int arrowKey = _getch();
                if (arrowKey == 77 && currentPage < totalPages - 1) { // → (오른쪽 화살표)
                    ++currentPage;
                }
                else if (arrowKey == 77 && currentPage == totalPages - 1) { // 마지막 페이지에서 →
                    break;
                }
            }
            else if (key == 13) { // Enter 키로 구매 또는 수정
                if (foundBooks.empty()) {
                    break;
                }

                // 선택한 책
                BooksDto selectedBook = foundBooks[bookIndex];

                // 수정 여부 확인
                gotoxy(5, 22);
                printf("'%s' 책을 수정하시겠습니까? (Y/N): ", selectedBook.title);
                char choice = _getch();

                if (toupper(choice) == 'Y') {
                    // 수정할 수 있는 책 정보 입력받기
                    int newPrice, newQuantity;
                    char newTitle[100], newAuthor[100], newGenre[100];

                    gotoxy(5, 23);
                    printf("새로운 제목을 입력하세요 (현재: %s): ", selectedBook.title);
                    gets_s(newTitle, sizeof(newTitle));
                    if (newTitle[0] == '\0') {
                        strcpy_s(newTitle, selectedBook.title); // 제목이 비어있으면 기존 제목 유지
                    }

                    gotoxy(5, 24);
                    printf("새로운 작가를 입력하세요 (현재: %s): ", selectedBook.author);
                    gets_s(newAuthor, sizeof(newAuthor));
                    if (newAuthor[0] == '\0') {
                        strcpy_s(newAuthor, selectedBook.author); // 작가가 비어있으면 기존 작가 유지
                    }

                    gotoxy(5, 25);
                    printf("새로운 장르를 입력하세요 (현재: %s): ", selectedBook.genre);
                    gets_s(newGenre, sizeof(newGenre));
                    if (newGenre[0] == '\0') {
                        strcpy_s(newGenre, selectedBook.genre); // 장르가 비어있으면 기존 장르 유지
                    }

                    gotoxy(5, 26);
                    printf("새로운 가격을 입력하세요 (현재: %d): ", selectedBook.book_price);
                    scanf_s("%d", &newPrice);


                    // 새로운 정보로 책 수정
                    selectedBook.book_price = newPrice;
                    strcpy_s(selectedBook.title, newTitle);
                    strcpy_s(selectedBook.author, newAuthor);
                    strcpy_s(selectedBook.genre, newGenre);

                    // 데이터베이스에서 책 정보 업데이트
                    updateBookDetails(selectedBook);

                    // 수정 완료 메시지
                    gotoxy(5, 27);
                    printf("'%s' 책 정보가 수정되었습니다.", selectedBook.title);
                }
                else {
                    gotoxy(5, 27);
                    printf("수정이 취소되었습니다.");
                }

                _getch(); // 메시지 확인 후 계속
                break;
            }
        }
    }
}
