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

        // ���� �Է¹ޱ�
        gotoxy(15, 4); // ���� �Է� ��ġ
        gets_s(inputTitle, sizeof(inputTitle));

        // �˻� ���� ����
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
                // �� �׸��� ��� �� �� �ٲ��� ��������� ó��
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
            gotoxy(5, 21); // �ϴ� �ȳ� �޽��� ��ġ
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
                return;
            }
            else if (key == 224) { // ����Ű ���� ó��
                int arrowKey = _getch();
                if (arrowKey == 77 && currentPage < totalPages - 1) { // �� (������ ȭ��ǥ)
                    ++currentPage;
                }
                else if (arrowKey == 77 && currentPage == totalPages - 1) { // ������ ���������� ��
                    break;
                }
            }
            else if (key == 13) { // Enter Ű�� ���� �Ǵ� ����
                if (foundBooks.empty()) {
                    break;
                }

                // ������ å
                BooksDto selectedBook = foundBooks[bookIndex];

                // ���� ���� Ȯ��
                gotoxy(5, 22);
                printf("'%s' å�� �����Ͻðڽ��ϱ�? (Y/N): ", selectedBook.title);
                char choice = _getch();

                if (toupper(choice) == 'Y') {
                    // ������ �� �ִ� å ���� �Է¹ޱ�
                    int newPrice, newQuantity;
                    char newTitle[100], newAuthor[100], newGenre[100];

                    gotoxy(5, 23);
                    printf("���ο� ������ �Է��ϼ��� (����: %s): ", selectedBook.title);
                    gets_s(newTitle, sizeof(newTitle));
                    if (newTitle[0] == '\0') {
                        strcpy_s(newTitle, selectedBook.title); // ������ ��������� ���� ���� ����
                    }

                    gotoxy(5, 24);
                    printf("���ο� �۰��� �Է��ϼ��� (����: %s): ", selectedBook.author);
                    gets_s(newAuthor, sizeof(newAuthor));
                    if (newAuthor[0] == '\0') {
                        strcpy_s(newAuthor, selectedBook.author); // �۰��� ��������� ���� �۰� ����
                    }

                    gotoxy(5, 25);
                    printf("���ο� �帣�� �Է��ϼ��� (����: %s): ", selectedBook.genre);
                    gets_s(newGenre, sizeof(newGenre));
                    if (newGenre[0] == '\0') {
                        strcpy_s(newGenre, selectedBook.genre); // �帣�� ��������� ���� �帣 ����
                    }

                    gotoxy(5, 26);
                    printf("���ο� ������ �Է��ϼ��� (����: %d): ", selectedBook.book_price);
                    scanf_s("%d", &newPrice);


                    // ���ο� ������ å ����
                    selectedBook.book_price = newPrice;
                    strcpy_s(selectedBook.title, newTitle);
                    strcpy_s(selectedBook.author, newAuthor);
                    strcpy_s(selectedBook.genre, newGenre);

                    // �����ͺ��̽����� å ���� ������Ʈ
                    updateBookDetails(selectedBook);

                    // ���� �Ϸ� �޽���
                    gotoxy(5, 27);
                    printf("'%s' å ������ �����Ǿ����ϴ�.", selectedBook.title);
                }
                else {
                    gotoxy(5, 27);
                    printf("������ ��ҵǾ����ϴ�.");
                }

                _getch(); // �޽��� Ȯ�� �� ���
                break;
            }
        }
    }
}
