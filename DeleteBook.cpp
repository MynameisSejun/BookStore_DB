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

    // ���� �Է� �ޱ�
    gotoxy(15, 4); // ���� �Է� ��ġ
    gets_s(inputTitle, sizeof(inputTitle));

    // ������ �������� å ��� �˻�
    BooksDto searchCriteria;
    strcpy_s(searchCriteria.title, inputTitle);
    strcpy_s(searchCriteria.author, "");
    strcpy_s(searchCriteria.genre, "");
    strcpy_s(searchCriteria.isbn, "");

    // �����ͺ��̽����� �˻� ��� ��������
    vector<BooksDto> foundBooks = selectBooks(searchCriteria);
    int totalBooks = foundBooks.size();
    int currentPage = 0;
    int totalPages = (totalBooks + PAGE_SIZE - 1) / PAGE_SIZE;

    while (true) {
        clrscr();
        print_screen("./screen/UserBuyMenu.txt");

        // ������ ���� ��ġ
        int startY = 8;
        int startIdx = currentPage * PAGE_SIZE;
        int endIdx = min(startIdx + PAGE_SIZE, totalBooks);

        // ���� ������ ������ ���
        for (int i = startIdx; i < endIdx; ++i) {
            const auto& book = foundBooks[i];
            gotoxy(5, startY + (i - startIdx));
            printf("%-20s %-25s %-20s %-15s %10d�� %10d��\n",
                book.isbn, book.title, book.author, book.genre,
                book.book_price, book.quantity);
        }

        // ��� ���� ��� �޽��� ���
        if (foundBooks.empty()) {
            gotoxy(5, startY);
            printf("�˻� ����� �����ϴ�.");
        }

        // ������ �ȳ� �� ����� �Է� ���
        gotoxy(5, 23); // �ϴ� �ȳ� �޽��� ��ġ
        if (foundBooks.empty()) {
            printf("��: �ٽ� �˻� | ESC: ���� ȭ��");
        }
        else if (currentPage < totalPages - 1) {
            printf("��: ���� ������ | ESC: ����");
        }
        else {
            printf("��: ��� �˻�   | ESC: ����");
        }

        // Ŀ�� �̵� �� ����
        int visibleRows = endIdx - startIdx; // ���� �������� ������ ����
        int prodY = cursorControl(5, startY, startY + visibleRows - 1, 1);

        int bookIndex = startIdx + (prodY - startY);

        // Ű �Է� ó��
        int key = _getch();
        if (key == 27) { // ESC Ű
            AdminMainMenu mainMenu; // UserMainMenu ȣ��
            mainMenu.printSrc();
        }
        else if (key == 224) { // ����Ű ���� ó��
            int arrowKey = _getch();
            if (arrowKey == 77 && currentPage < totalPages - 1) { // �� (������ ȭ��ǥ)
                ++currentPage;
            }
            else if (arrowKey == 75 && currentPage > 0) { // �� (���� ȭ��ǥ)
                --currentPage;
            }
        }
        else if (key == 13) { // Enter Ű�� ����
            if (foundBooks.empty()) {
                break;
            }

            // ������ å
            BooksDto selectedBook = foundBooks[bookIndex];

            // ���� ���� Ȯ��
            gotoxy(5, 24);
            printf("'%s' å�� �����Ͻðڽ��ϱ�? (Y/N): ", selectedBook.title);
            char choice = _getch();

            if (toupper(choice) == 'Y') {
                // å ����
                deleteBook(selectedBook.isbn);

                gotoxy(5, 25);
                printf("'%s' å�� �����Ǿ����ϴ�.", selectedBook.title);
            }
            else {
                gotoxy(5, 25);
                printf("������ ��ҵǾ����ϴ�.");
            }

            _getch(); // �޽��� Ȯ�� �� ���
            AdminMainMenu mainmenu;
            mainmenu.printSrc();
            break;
        }
    }
}