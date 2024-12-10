#pragma once
#ifndef DAO
#define DAO
extern "C" {
#include "execute_query.h"
}

#include<vector>
using namespace std;

void addMember(MembersDto member);

struct MembersDto findByMemberId(char id[]);

void addBook(BooksDto book);

void updateBook(BooksDto book, char findIsbn[]);

void deleteBook(char findIsbn[]);
#endif DAO