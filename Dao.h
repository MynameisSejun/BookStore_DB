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

vector<BooksDto> selectBooks(const BooksDto& criteria);

void deleteBook(char findIsbn[]);

#endif DAO