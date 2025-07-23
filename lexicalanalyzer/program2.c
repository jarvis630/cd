#include <stdio.h>
#include <string.h>
#include <ctype.h>

int k_count = 0, i_count = 0;

void keyword(char str[10]) {
    if (strcmp("for", str) == 0 || strcmp("printf", str) == 0 || strcmp("do", str) == 0 ||
        strcmp("while", str) == 0 || strcmp("int", str) == 0 || strcmp("float", str) == 0 ||
        strcmp("char", str) == 0 || strcmp("double", str) == 0 || strcmp("static", str) == 0 ||
        strcmp("switch", str) == 0 || strcmp("case", str) == 0 || strcmp("include", str) == 0) {
        printf("\n%s is a keyword", str);
        k_count++;
    } else {
        printf("\n%s is an identifier", str);
        i_count++;
    }
}

int main() {
    FILE *f1, *f2, *f3;
    char c, str[10], str1[10];
    int num[100], lineno = 0, tokenvalue = 0, i = 0, j = 0, k = 0, count = 0, s_count = 0;

    f1 = fopen("input.txt", "r");
    f2 = fopen("identifier", "w");
    f3 = fopen("special char", "w");

    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    while ((c = getc(f1)) != EOF) {
        if (isdigit(c)) {
            tokenvalue = c - '0';
            c = getc(f1);
            while (isdigit(c)) {
                tokenvalue = tokenvalue * 10 + (c - '0');
                c = getc(f1);
            }
            num[i++] = tokenvalue;
            ungetc(c, f1);
            count = i;
        } else if (isalpha(c)) {
            putc(c, f2);
            c = getc(f1);
            while (isdigit(c) || isalpha(c) || c == '_' || c == '$') {
                putc(c, f2);
                c = getc(f1);
            }
            putc(' ', f2);
            ungetc(c, f1);
        } else if (c == ' ' || c == '\t') {
            printf(" ");
        } else if (c == '\n') {
            lineno++;
        } else {
            putc(c, f3);
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);

    printf("\nThe numbers in the program are:\n");
    for (i = 0; i < count; i++) {
        printf("%d\t", num[i]);
    }

    printf("\n");

    f2 = fopen("identifier", "r");
    if (f2 == NULL) {
        printf("Error opening identifier file.\n");
        return 1;
    }

    printf("\nThe keywords and identifiers are:");
    while ((c = getc(f2)) != EOF) {
        if (c != ' ') {
            str[k++] = c;
        } else {
            str[k] = '\0';
            keyword(str);
            k = 0;
        }
    }
    fclose(f2);

    f3 = fopen("special char", "r");
    if (f3 == NULL) {
        printf("Error opening special char file.\n");
        return 1;
    }

    printf("\nThe special characters are:\n");
    while ((c = getc(f3)) != EOF) {
        printf("%c ", c);
        s_count++;
    }

    printf("\n");
    fclose(f3);

    printf("\nTotal number of lines are: %d\n", lineno);
    printf("Count of numbers are: %d\n", count);
    printf("Total number of keywords are: %d\n", k_count);
    printf("Total number of identifiers are: %d\n", i_count);
    printf("Total number of special characters are: %d\n", s_count);

    return 0;
}