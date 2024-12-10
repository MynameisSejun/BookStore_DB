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