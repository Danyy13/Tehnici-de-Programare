#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/*
    Aplicatia 6.6: Sa se scrie o functie char *concat(int n,...) care primeste un numar de
    siruri de caractere si apoi sirurile propriu-zise. Functia va concatena intr-un nou sir,
    alocat dinamic, continuturile tuturor sirurilor date, cu cate un spatiu intre ele si va
    returna acest sir.
    Exemplu: concat(3,"Ion", "si", "Ana") => "Ion si Ana"
*/

char *concat(int n, ...) {
    char *string = NULL, *temp = NULL;
    char *argument = NULL;
    unsigned int size = 0;
    va_list args;
    va_start(args, n);

    do {
        argument = va_arg(args, char *);
        // se va concatena cu cate un spatiu intre ele => daca nu este ultimul argument trebuie sa adaugam loc pentru caracterul " "
        size += strlen(argument);
        if(n != 1) size += 1;
        if((temp = (char *)realloc(string, size * sizeof(char))) == NULL) {
            printf("Eroare la alocare\n");
            free(string);
            exit(EXIT_FAILURE);
        }
        string = temp;
        strcat(string, argument);
        if(n != 1) string[size - 1] = ' ';
    }while(--n);

    va_end(args);
    return string;
}

int main() {
    char *string = NULL;
    string = concat(3, "Ion", "si", "Ana");
    printf("%s\n", string);
    free(string);
    return 0;
}
