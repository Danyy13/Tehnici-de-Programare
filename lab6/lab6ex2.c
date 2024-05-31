#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
    Aplicatia 6.2: Sa se scrie o functie float *allocVec(int n,...) care primeste pe prima
    pozitie un numar de elemente iar apoi n elemente reale. Functia va aloca dinamic un vector
    de tip float in care va depune toate elementele.
    Exemplu: allocVec(3,7.2,-1,0) => {7.2, -1, 0}
*/

#define SIZE 5

void printArray(float array[], unsigned int size) {
    for(unsigned int i=0;i<SIZE;i++) {
        printf("%g ", array[i]);
    }
    printf("\n");
}

float *allocVec(int n, ...) {
    unsigned int i = 0;
    float *array = NULL;
    // aloc memorie pentru vector
    if((array = malloc(n * sizeof(float))) == NULL) {
        printf("Eroare la alocare\n");
        exit(EXIT_FAILURE);
    }
    va_list variables;
    va_start(variables, n);

    for(i=0;i<n;i++) {
        array[i] = va_arg(variables, double);
    }

    va_end(variables);
    return array;
}

int main() {
    float *array = NULL;

    array = allocVec(SIZE, 1.1, 2.4, 3.9, 4.43, 5.11);

    printArray(array, SIZE);

    free(array);

    return 0;
}