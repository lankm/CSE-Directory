#ifndef USERS_H_
#define USERS_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STR 50
#define MAX_PASS 16

typedef struct {
    long id;
    char name[MAX_STR];
    char pass[MAX_PASS];
    char email[MAX_STR];
} user_t;

void list_users(user_t [], int);
void add_user(user_t *, int *);

#endif
