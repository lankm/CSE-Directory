#include "users.h"
#include "util/util.h"

void list_users(user_t users[], int num_users) {
    for (int i = 0; i < num_users; i++) {
        printf("%.10ld %20.20s %20.20s\n",
                users[i].id, users[i].name, users[i].email);
    }
}

void add_user(user_t *u, int *num_users) {
    printf("Enter name: ");
    fgets(u->name, MAX_STR, stdin);
    trim(u->name);

    printf("Enter password: ");
    fgets(u->pass, MAX_PASS, stdin);
    trim(u->pass);

    printf("Enter email: ");
    fgets(u->email, MAX_STR, stdin);
    trim(u->email);

    u->id = ++(*num_users);
}
