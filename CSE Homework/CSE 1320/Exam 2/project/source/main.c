#include "users.h"

#define MAX_USERS 1024

void print_menu() {
    printf("A. Add User\n");
    printf("L. List Users\n");
    printf("Q. Quit\n");
}

int main() {
    int num_users = 0;
    char choice = 0;
    user_t users[MAX_USERS] = { 0 };

    while (toupper(choice) != 'Q') {
        // Print menu and get user selection
        print_menu();
        printf("Enter selection: ");
        scanf("%c", &choice);
        while (getchar() != '\n');

        switch (toupper(choice)) {
            case 'A':
                add_user(&users[num_users], &num_users);
                break;
            case 'L':
                list_users(users, num_users);
                break;
            case 'Q':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid selection.\n");
        }
    }

    return 0;
}
