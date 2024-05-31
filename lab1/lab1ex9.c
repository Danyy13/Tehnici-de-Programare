#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
    Aplictia 8.9: Se citeste un numar n <= 10. Se cere sa se initializeze o matrice a[n][n]
    cu 1 pe diagonale si cu 0 in rest. Sa se afiseze matricea.
*/

void eliberare(uint8_t rows, uint8_t **matrix) {
    for(uint8_t i=0;i<rows;i++) free(matrix[i]);
    free(matrix);
}

void afisare(uint8_t size, uint8_t **matrix) {
    for(uint8_t i=0;i<size;i++) {
        for(uint8_t j=0;j<size;j++) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    uint8_t n = 0;
    uint8_t **a = NULL;
    scanf("%hhu", &n);

    // alocam pointeri catre fiecare linie
    if((a = (uint8_t **)malloc(n * sizeof(uint8_t *))) == NULL) {
        fprintf(stderr, "Eroare la alocare linii\n");
        exit(-10);
    }
    for(uint8_t i=0;i<n;i++) {
        if((a[i] = (uint8_t *)malloc(n * sizeof(uint8_t))) == NULL) {
            for(i--;i>=0;i--) free(a[i]);
            free(a);
            fprintf(stderr, "Eroare la alocare coloane\n");
            exit(-11);
        }
    }

    for(uint8_t i=0;i<n;i++) {
        for(uint8_t j=0;j<n;j++) {
            if(i == j) a[i][j] = 1;
            else a[i][j] = 0;
        }
    }

    afisare(n, a);
    eliberare(n, a);

    return 0;
}