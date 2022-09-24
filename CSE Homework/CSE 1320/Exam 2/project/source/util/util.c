#include "util.h"

void trim(char *str) {
    int l = strlen(str);
    if (str[l] == '\n') {
        str[l] = 0;
    }
}

void clear_buffer() {
    int c = 0;

    while ((c = getchar()) != '\n' && c != EOF);
}
