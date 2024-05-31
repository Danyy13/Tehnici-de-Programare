#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
    Aplicatia 8.1: Se citeste de la tastatura un numar natural n<=10. Se citesc apoi elementele
    intregi ale unei matrici a[n][n]. Sa se afiseze daca matricea a este o matrice unitate.
    Nota: o matrice unitate are pe diagonala principala 1 si in rest 0.
*/

#define SIZE_READ_ERR -2
#define VALUE_READ_ERR -1

void afisare(unsigned int size, int *matrix) {
    for(unsigned int i=0;i<size;i++) {
        for(unsigned int j=0;j<size;j++) {
            printf("%d ", *(matrix + (i * size) + j)); // daca are numar de linii si coloane diferite atunci (i * cols)
        }
        putchar('\n');
    }
}

void readMatrix(uint8_t size, int *matrix) {
    unsigned int i = 0;
    for(i=0;i<size;i++) {
        for(unsigned int j=0;j<size;j++) {
            if(scanf("%d", matrix + (i * size) + j) != 1) {
                fprintf(stderr, "Eroare la citire\n");
                exit(VALUE_READ_ERR);
            }
        }
    }
    size = i;
}

uint8_t unitate(unsigned int size, int *matrix) {
    for(unsigned int i=0;i<size;i++) {
        for(unsigned int j=0;j<size;j++) {
            if(i == j && 1 != *(matrix + (i * size) + j)) return 0;
            if(i != j && 0 != *(matrix + (i * size) + j)) return 0;
        }
    }
    return 1;
}

int main() {
    uint8_t n = 0; // marimea matricii, n <= 10
    int matrix[10][10];
    // printf("n = ");
    if(scanf("%hhd", &n) != 1) {
        fprintf(stderr, "Nu s-a citit marimea matricii\n");
        exit(SIZE_READ_ERR);
    }
    readMatrix(n, *matrix);
    if(unitate(n, *matrix)) printf("Matricea este unitate\n");
    else printf("Matricea NU este unitate\n");
    return 0;
}