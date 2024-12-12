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

void deleteBook(const char* isbn) {
    // 책을 삭제하는 SQL 쿼리 실행
    char query[1000];
    sprintf(query, "DELETE FROM books WHERE isbn = '%s'", isbn);
    execute_update(query);  // execute_update는 쿼리를 실행하는 함수
}

void updateBookDetails(BooksDto& book) {
    // 책 정보를 수정하는 SQL 쿼리 실행
    char query[1000];
    sprintf(query, "UPDATE books SET title = '%s', author = '%s', genre = '%s', book_price = %d, quantity = %d WHERE isbn = '%s'",
        book.title, book.author, book.genre, book.book_price, book.quantity, book.isbn);
    execute_update(query);  // execute_update는 쿼리를 실행하는 함수
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

vector<OrdersDto> selectPurchaseHistory(const char* user_id) {
    int rowCount = 0;

    // Pro*C 함수 호출
    struct OrdersDto* rawOrders = selectPurchaseHistory_C(user_id, &rowCount);

    vector<OrdersDto> result;
    for (int i = 0; i < rowCount; i++) {
        result.push_back(rawOrders[i]);
    }

    free(rawOrders); // 메모리 해제
    return result;
}


void deleteBook(char findIsbn[]) {
    sprintf(query, "delete from books where isbn = '%s'", findIsbn);
    execute_update(query);
}