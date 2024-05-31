#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
    Aplicatia 6.8: Sa se scrie o functie sortare(int n,...) care pe prima pozitie are numarul de
    elemente de sortat, iar pe urmatoarele pozitii n adrese de valori de tip int. Functia va
    sorta crescator valorile de la adresele date.
    Exemplu: sortare(3, &i, &j, &k); // sorteaza crescator valorile lui i, j si k

    // voi pune valorile intr-un vetor de adrese si le sortez cu bubblesort / qsort()
*/

#define CHUNK 10

void *sortare(int n, ...) {
    int **array = NULL;
    va_list args;
    va_start(args, n);

    // am n = numarul de argumente, deci aloc memorie pentru acestea cu malloc()
    if((array = (int **)malloc(n * sizeof(int *))) == NULL) {
        printf("Eroare la alocare\n");
        exit(EXIT_FAILURE);
    }

    for(unsigned int i = 0;i<n;i++) {
        array[i] = va_arg(args, int *);
    }

    for(unsigned int i=0;i<n-1;i++) {
        for(unsigned int j=i+1;j<n;j++) {
            if(*array[i] > *array[j]) {
                int *aux = array[i];
                array[i] = array[j];
                array[j] = aux;
            }
        }
    }

    printf("%d %d %d\n", *array[0], *array[1], *array[2]);

    va_end(args);
    return *array;
}

int main() {
    int i, j, k; i=j=k=0;

    scanf("%d", &i);
    scanf("%d", &j);
    scanf("%d", &k);

    sortare(3, &i, &j, &k);

    return 0;
}