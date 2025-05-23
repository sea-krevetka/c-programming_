#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kakugodno.h"

#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char tmpline[MAX_LINE_LENGTH] = "";
    char longline[MAX_LINE_LENGTH] = "";
    int maxlength = 0;

    while (fgets(tmpline, sizeof(tmpline), file)) {
        int len = strlen(tmpline);
        if (len > 0 && tmpline[len - 1] == '\n') {
            tmpline[len - 1] = '\0';
            len--;
        }

        if (len > maxlength) {
            maxlength = len;
            strcpy(longline, tmpline);
        }
    }

    fclose(file);

    printf("Самая длинная строка: %s\n", longline);

    swapwords(longline);
    printf("После замены: %s\n", longline);

    FILE *outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        perror("Ошибка при открытии выходного файла");
        exit(1);
    }
    fprintf(outfile, "%s\n", longline);
    fclose(outfile);

    return 0;
}