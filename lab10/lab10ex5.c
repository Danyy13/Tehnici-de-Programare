#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Aplicatia 10.5: Se considera sirul-de-caractere de tip Fibonacci, in care primii doi termeni
    sunt sirurile de caractere s1 si s2 (pot fi transmise ca si parametri functiei), iar orice
    alt termen se obtine prin concatenarea celor doi termeni anteriori. Sa se implementeze o
    functie care un numar natural n (si orice alti parametri considerati necesari) si afiseaza
    termenul de pe pozitia n din sirul construit conform celor de mai sus.
*/

#define REPEAT 5

void allocString(char string[], unsigned int size) {
    char *temp = NULL;
    if((temp = (char *)realloc(string, size * sizeof(char))) == NULL) {
        fprintf(stderr, "Eroare la alocare");
        free(string);
        exit(-1);
    }
    string = temp;
}

char *concatString(char *string, char *string1, char *string2) {
    // unsigned int size = strlen(string1) + strlen(string2);
    // allocString(string, size);
    strcpy(string, string1);
    strcat(string, string2);
    return string;
}

char *fiboString(unsigned int n, char *string, char *string1, char *string2) {
    if(!n) {
        return string;
    }
    // printf("string: %s string1: %s string2: %s\n", string, string1, string2);
    strcpy(string, concatString(string, string1, string2));
    strcpy(string1, string2);
    strcpy(string2, string);
    
    return fiboString(n - 1, string, string1, string2);
}

int main() {
    char string1[10000] = "a", string2[10000] = "b";
    char string[10000] = "";

    // strcpy(string, concatString(string, string1, string2));

    strcpy(string, fiboString(REPEAT, string, string1, string2));
    printf("%s\n", string); 

    // free(string);
    return 0;
}