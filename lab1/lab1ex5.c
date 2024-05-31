#include <stdio.h>

/*
    Aplicatia 8.5: Se citeste de la tastatura o matrice cu n <= 20 linii si coloane. Sa se
    memoreze intr-un vector suma tuturor elementelor de pe fiecare linie si intr-un alt vector,
    suma tuturor elementelor de pe fiecare coloana. Sa se afiseze cei doi vectori. Se vor
    utiliza pointeri atat pentru vectori cat si pentru matrici.
*/

void initialize(int array[], unsigned int size) {
    int *p = NULL;
    for(p=array;p-array<size;p++) {
        *p = 0;
    }
}

int main() {
    unsigned int size = 0; // size = numarul de elemente
    scanf("%d", &size);

    int matrix[size][size];
    int rowSums[size], colSums[size];

    // initializam toate valorile din vectori pe 0 pentru a putea face suma
    initialize(rowSums, size);
    initialize(colSums, size);

    int *p = NULL, *row = rowSums, *col = colSums;

    // pentru eficienta facem suma pe linii odata cu citirea
    for(p=&matrix[0][0];p<&matrix[size][0];++p) {
        scanf("%d", p);
        *row += *p; // adaug a[i][j] la row care pointeaza la adresele din rowSums
        if((p - &matrix[0][0] + 1) % size == 0 && (p - &matrix[0][0]) != 0) {
            row++;
        }
    }

    printf("Suma pe randuri: ");
    for(row=rowSums;(row - rowSums)<size;row++) {
        printf("%d ", *row);
    }
    printf("\n");

    for(p=&matrix[0][0];p<&matrix[size][0];++p) {
        colSums[(p - &matrix[0][0]) % 3] += *p;
    }

    printf("Suma pe coloane: ");
    for(col=colSums;(col - colSums)<size;col++) {
        printf("%d ", *col);
    }
    printf("\n");

    return 0;
}