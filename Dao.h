#pragma once
extern "C" {
#include "execute_query.h"
}

#include<vector>
using namespace std;

void addMember(MembersDto member);

struct MembersDto findByMemberId(char id[]);

