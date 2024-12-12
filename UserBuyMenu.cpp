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

using namespace std;

const int PAGE_SIZE = 10;

void UserBuyMenu::printSrc()
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
                printf("%-20s %-25s %-20s %-15s %10d원 %10d개",
                    book.isbn, book.title, book.author, book.genre, book.book_price, book.quantity);
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
                UserMainMenu mainMenu; // UserMainMenu 호출
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
            else if (key == 13) { // Enter 키로 구매
                if (foundBooks.empty()) {
                    break;
                }

                // 구매 처리
                BooksDto selectedBook = foundBooks[bookIndex];
                if (selectedBook.quantity > 0) {
                    int purchaseQuantity = 0;

                    // 수량 입력받기
                    gotoxy(5, 24);
                    printf("구매할 수량을 입력하세요 (재고: %d개): ", selectedBook.quantity);
                    scanf_s("%d", &purchaseQuantity);

                    if (purchaseQuantity <= 0 || purchaseQuantity > selectedBook.quantity) {
                        gotoxy(5, 25);
                        printf("잘못된 수량입니다. 다시 시도해주세요.");
                        _getch(); // 메시지 확인 후 계속
                        continue;
                    }

                    // 구매 여부 확인
                    gotoxy(5, 25);
                    printf("'%s' 책을 %d개 구매하시겠습니까? (Y/N): ", selectedBook.title, purchaseQuantity);

                    char choice = _getch(); // 사용자 입력
                    if (toupper(choice) == 'Y') { // 'Y' 또는 'y' 입력 시 구매 진행
                        int totalAmount = purchaseQuantity * selectedBook.book_price;

                        // 전역 변수 currentUser를 활용해 구매 내역 저장
                        savePurchaseHistory(currentUser.user_id, selectedBook.isbn, purchaseQuantity, totalAmount);

                        selectedBook.quantity -= purchaseQuantity; // 수량 감소
                        updateBookQuantity(selectedBook.isbn, selectedBook.quantity); // 데이터베이스 업데이트

                        gotoxy(5, 26);
                        printf("'%s' 책을 %d개 구매하였습니다. (남은 수량: %d)", selectedBook.title, purchaseQuantity, selectedBook.quantity);
                    }
                    else {
                        gotoxy(5, 26);
                        printf("구매가 취소되었습니다.");
                    }
                }
                else {
                    gotoxy(5, 25);
                    printf("'%s' 책은 품절입니다.", selectedBook.title);
                }

                _getch(); // 메시지 확인 후 계속
                break;
            }
        }
    }
}
