#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
    Aplicatia 8.10: Se citeste un numar n <= 10 de produse si pentru fiecare produs vanzarile
    lui trimestriale pe un an (4 valori). Se cere sa se afiseze care produse au inregistrat o
    crestere continua a vanzarilor in decurs de un an.

    crestere continua => cele patru valori de pe o linie trebuie sa fie in ordine crescatoare
*/

#define VANZARI 4

void eliberare(uint8_t rows, unsigned int **matrix) {
    for(uint8_t i=0;i<rows;i++) free(matrix[i]);
    free(matrix);
}

void readMatrix(uint8_t rows, uint8_t cols, unsigned int **matrix) {
    for(uint8_t i=0;i<rows;i++) {
        for(uint8_t j=0;j<cols;j++) {
            if(scanf("%u", &matrix[i][j]) != 1) {
                fprintf(stderr, "Eroare la citire\n");
                exit(-1);
            }
        }
    }
}

void crestereCrescatoare(uint8_t rows, uint8_t cols, unsigned int **matrix) {
    printf("Produsele care au inregistrat o crestere continua a vanzarilor sunt\n");
    for(uint8_t i=0;i<rows;i++) {
        uint8_t ok = 1;
        for(uint8_t j=1;j<cols;j++) { // incepem de la a doua valoare de pe linie si o verificam in functie de prima
            if(matrix[i][j] <= matrix[i][j-1]) ok = 0;
        }
        if(ok) printf("%d ", i);
    }
    putchar('\n');
}

int main() {
    uint8_t n = 0;
    unsigned int **produs = NULL;

    scanf("%hhu", &n);
    if(n > 10) {
        fprintf(stderr, "n prea mare\n");
        exit(-2);
    }

    if((produs = (unsigned int **)malloc(n * sizeof(unsigned int *))) == NULL) {
        fprintf(stderr, "Eroare la alocare linii\n");
        exit(-10);
    }
    for(uint8_t i=0;i<n;i++) {
        if((produs[i] = (unsigned int *)malloc(VANZARI * sizeof(unsigned int))) == NULL) {
            for(i--;i>=0;i--) free(produs[i]);
            free(produs);
            fprintf(stderr, "Eroare la alocare coloane\n");
            exit(-11);
        }
    }

    readMatrix(n, VANZARI, produs);
    crestereCrescatoare(n, VANZARI, produs);
    eliberare(n, produs);

    return 0;
}