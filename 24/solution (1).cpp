#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[256];
int pos = 0;

void skipSpaces() {
    while (expr[pos] == ' ')
        pos++;
}

void parseFactor(char result[]) {
    skipSpaces();

    if (expr[pos] == '(') {
        int start = pos;
        int balance = 0;

        do {
            if (expr[pos] == '(') balance++;
            if (expr[pos] == ')') balance--;
            pos++;
        } while (balance > 0);

        int len = pos - start;
        strncpy(result, expr + start, len);
        result[len] = '\0';
    }
    else {
        int start = pos;

        while (isalnum(expr[pos]))
            pos++;

        int len = pos - start;
        strncpy(result, expr + start, len);
        result[len] = '\0';
    }
}

int main() {
    fgets(expr, sizeof(expr), stdin);

    char factors[20][50];
    int negativeCount = 0;
    int count = 0;

    while (expr[pos] != '\0' && expr[pos] != '\n') {
        char factor[50];

        parseFactor(factor);

        if (factor[0] == '(' && factor[1] == '-') {
            negativeCount++;

            char temp[50];
            int len = strlen(factor);

            strncpy(temp, factor + 2, len - 3);
            temp[len - 3] = '\0';

            strcpy(factors[count++], temp);
        }
        else {
            strcpy(factors[count++], factor);
        }

        skipSpaces();

        if (expr[pos] == '*')
            pos++;
    }

    if (negativeCount % 2 == 1)
        printf("-(");

    for (int i = 0; i < count; i++) {
        printf("%s", factors[i]);

        if (i != count - 1)
            printf(" * ");
    }

    if (negativeCount % 2 == 1)
        printf(")");

    return 0;
}