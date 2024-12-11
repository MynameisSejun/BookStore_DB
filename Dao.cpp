#define _CRT_SECURE_NO_WARNINGS

#include "Dao.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <vector>

using namespace std;

char query[1000];

void addMember(MembersDto member) {
    sprintf(query, "INSERT INTO user_accounts (id, password, name, role) VALUES ('%s', '%s', '%s', '%s')",
        member.member_id, member.pw, member.name, member.role);
    execute_update(query);
}

struct MembersDto findByMemberId(char id[]) {
    return select_MemberId(id);
}

void addBook(BooksDto book) {
    sprintf(query, "INSERT INTO books (isbn, title, author, genre, book_price) VALUES ('%s', '%s', '%s', '%s', %d)",
        book.isbn, book.title, book.author, book.genre, book.book_price);
    execute_insert(query);
}

void updateBook(BooksDto book, char findIsbn[]) {
    sprintf(query, "update books set isbn = '%s', title = '%s', author = '%s', genre = '%s', book_price = %d where isbn = '%s'",
        book.isbn, book.title, book.author, book.genre, book.book_price, findIsbn);
    execute_update(query);
}

vector<BooksDto> selectBooks(const BooksDto& criteria) {
    int rowCount = 0;

    // Pro*C �Լ� ȣ��
    struct BooksDto* rawBooks = selectBooks_C(criteria.isbn, criteria.title, criteria.author, criteria.genre, &rowCount);

    vector<BooksDto> result;
    for (int i = 0; i < rowCount; i++) {
        result.push_back(rawBooks[i]);
    }

    free(rawBooks); // �޸� ����
    return result;
}

void deleteBook(char findIsbn[]) {
    sprintf(query, "delete from books where isbn = '%s'", findIsbn);
    execute_delete(query);
}
