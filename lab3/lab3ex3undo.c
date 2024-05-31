#include <stdio.h>
#include <string.h>

/*
    Aplicatia 3.3 Sa se implementeze cu ajutorul unei stive functia undo dintr-un fisier text.
    Functia undo permite utilizatorului sa se revina la o versiune mai veche a documentului,
    eliminand ultimile modificari. Pentru a implementa functia undo cu o stiva fiecare modificare
    va fi retinuta pe stiva, iar cand e necesar sa se revina la o versiune anterioara se va
    elimina din stiva ultima modificare adaugata. Pe stiva se va retine la fiecare modificare:
    textul nou scris (sir de maxim 100 de caractere), randul unde a fost scris (int).

    se retine randul unde a fost scris prin variabila top
*/

#define SIZE_MAX 100
#define CHAR_MAX 100
int top = -1;
char stringStack[SIZE_MAX][CHAR_MAX + 1];

void printText(char lines[][CHAR_MAX + 1], int size) {
    for(int i=0;i<=size;i++) { // top = size incepe de la -1
        printf("%s", lines[i]);
    }
    putchar('\n');
}

void push(char string[]) {
    if(top == SIZE_MAX - 1) {
        fprintf(stderr, "Stiva este plina\n");
        return;
    }
    strcpy(stringStack[++top], string);
}

char *pop() {
    if(top == -1) {
        fprintf(stderr, "Stiva este goala\n");
        return "";
    }
    return stringStack[top--];
}

int main() {
    char buffer[CHAR_MAX + 1];
    char option[6]; // write, undo sau end

    printf("Optiuni: write, undo, end\n");

    while(1) {
        scanf("%s", option);
        getchar();
        if(strcmp(option, "end") == 0) break;
        if(strcmp(option, "write") == 0) {
            fgets(buffer, CHAR_MAX + 1, stdin);
            push(buffer);
        } else if(strcmp(option, "undo") == 0) {
            strcpy(buffer, pop());
        } else {
            printf("Optiunea nu exista\n");
        }
        printText(stringStack, top);
    }

    return 0;
}