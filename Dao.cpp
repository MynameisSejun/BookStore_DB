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