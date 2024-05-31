#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
    Aplicatia 8.8: Se citesc numerele m, n, p fiecare mai mici decat 10, apoi se citesc matricile
    a[m][n] si b[n][p]. Se cere sa se calculeze matricea "c" care rezulta din inmultirea
    matricilor a cu b si sa se afiseze.
*/

void afisare(uint8_t rows, uint8_t cols, int matrix[][cols]) {
    for(uint8_t i=0;i<rows;i++) {
        for(uint8_t j=0;j<cols;j++) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

void readMatrix(uint8_t rows, uint8_t cols, int matrix[][cols]) {
    for(uint8_t i=0;i<rows;i++) {
        for(uint8_t j=0;j<cols;j++) {
            if(scanf("%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Eroare la citire\n");
                exit(-1);
            }
        }
    }
}

void initMatrix(uint8_t rows, uint8_t cols, int *matrix) {
    memset(matrix, 0, rows * cols);
}

void multiply(uint8_t m, uint8_t n, uint8_t p, int a[m][n], int b[n][p], int c[m][p]) {
    for(uint8_t i=0;i<m;i++) {
        for(uint8_t j=0;j<n;j++) {
            for(uint8_t k=0;k<p;k++) {
                c[i][k] += a[i][j] * b[j][k]; 
            }
        }
    }
}

int main() {
    uint8_t m = 0, n = 0, p = 0;
    int a[10][10], b[10][10], c[10][10];

    scanf("%hhu %hhu %hhu", &m, &n, &p);
    if(m > 10 || n > 10 || p > 10) {
        fprintf(stderr, "Marimile matricelor depasesc valoarea maxima\n");
        exit(-2);
    }

    readMatrix(m, n, a);
    readMatrix(n, p, b);

    multiply(m, n, p, a, b, c);

    afisare(m, p, c);

    return 0;
}