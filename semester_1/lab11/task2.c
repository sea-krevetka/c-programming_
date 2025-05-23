#include <stdio.h>
#include <string.h> //added library string to work with sprinf

typedef struct {
    char str[100]; //increased memory size (needs 4 digits for a null terminator because with 3 it just floats)
    int num;
} NumberRepr;

void format(NumberRepr* number) {
    sprintf(number->str, "%3d", number->num);
}

int main() {
    NumberRepr number = { .num = 1025 };
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}