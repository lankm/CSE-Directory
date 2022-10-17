#include "practice.hpp"

int main() {
    Number n = Number("5");
    char str[31];

    n = n + n;
    printf("%s", n.toString(str));
}
