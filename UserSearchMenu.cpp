#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <vector>

#include "UserSearchMenu.h"
#include "screenControl.h"
#include "Dao.h"
#include "UserMainMenu.h" // UserMainMenu�� ���� �߰�

using namespace std;

const int PAGE_SIZE = 10; // �� �������� ǥ���� ������ ����

void UserSearchMenu::printSrc()
{
    while (1) {
        clrscr(); // ���� ȭ�� �����ϸ鼭 Ŭ����

        // ���� ȭ�� ���
        print_screen("./screen/UserSearchMenu.txt");

        char inputTitle[100] = "";
        char inputAuthor[100] = "";
        char inputGenre[100] = "";

        // ����� �Է� �ޱ�
        gotoxy(15, 4); // ���� �Է� ��ġ
        gets_s(inputTitle, sizeof(inputTitle));

        gotoxy(15, 6); // �۰� �Է� ��ġ
        gets_s(inputAuthor, sizeof(inputAuthor));

        gotoxy(15, 8); // �帣 �Է� ��ġ
        gets_s(inputGenre, sizeof(inputGenre));

        // �˻� ���� ����
        BooksDto searchCriteria;
        strcpy_s(searchCriteria.title, inputTitle);
        strcpy_s(searchCriteria.author, inputAuthor);
        strcpy_s(searchCriteria.genre, inputGenre);
        strcpy_s(searchCriteria.isbn, "");

        // �����ͺ��̽� �˻�
        vector<BooksDto> foundBooks = selectBooks(searchCriteria);

        // �˻� ��� ��� ��ġ
        int startY = 12; // ������ ���� ��ġ
        int totalBooks = foundBooks.size();
        int currentPage = 0;
        int totalPages = (totalBooks + PAGE_SIZE - 1) / PAGE_SIZE;

        while (true) {
            // �˻� ��� ��� ����
            for (int y = startY; y < startY + PAGE_SIZE; ++y) {
                gotoxy(5, y);
                printf("                                                                                  "); // ���� ���� ����
            }

            // ���� ������ ������ ���
            int startIdx = currentPage * PAGE_SIZE;
            int endIdx = min(startIdx + PAGE_SIZE, totalBooks);

            for (int i = startIdx; i < endIdx; ++i) {
                const auto& book = foundBooks[i];
                gotoxy(5, startY + (i - startIdx));
                printf("%-20s %-25s %-20s %-15s %10d�� %10d��",
                    book.isbn, book.title, book.author, book.genre, book.book_price, book.quantity);
            }

            // ��� ���� ��� �޽��� ���
            if (foundBooks.empty()) {
                gotoxy(5, startY);
                printf("�˻� ����� �����ϴ�.");
            }

            // ������ �ȳ� �� ����� �Է� ���
            gotoxy(5, 25); // �ϴ� �ȳ� �޽��� ��ġ
            if (foundBooks.empty()) {
                printf("Enter Ű: �ٽ� �˻� | ESC Ű: ���� ȭ��");
            }
            else if (currentPage < totalPages - 1) {
                printf("Enter Ű: ���� ������ | ESC Ű: ����");
            }
            else {
                printf("Enter Ű: ��� �˻�   | ESC Ű: ����");
            }

            int key = _getch();
            if (key == 27) { // ESC Ű
                UserMainMenu mainMenu; // UserMainMenu ȣ��
                mainMenu.printSrc();
                return;
            }
            else if (key == 13 && foundBooks.empty()) { // Enter Ű�� �ٽ� �˻�
                break;
            }
            else if (key == 13 && currentPage < totalPages - 1) { // Enter Ű�� ���� ������
                ++currentPage;
            }
            else if (key == 13 && currentPage == totalPages - 1) { // ������ ���������� Enter Ű
                break;
            }
        }
    }
}
