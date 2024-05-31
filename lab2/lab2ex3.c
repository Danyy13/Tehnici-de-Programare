#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
    Aplicatia 2.3: Se introduce un numar intreg n < 10 si apoi n numere de tip float. Sa se
    foloseasca functia qsort pentru a sorta aceste numere in mod crescator. Se va introduce
    apoi un numar x de tip float. Folosind functia bsearch, sa se determine daca x exista in
    vectorul sortat. Se pot consulta paginile de manual pentru functiile qsort si bsearch.
*/

void readArray(float array[], uint8_t size) {
    for(uint8_t i=0;i<size;i++) {
        scanf("%g", &array[i]);
    }
}

void printArray(float array[], uint8_t size) {
    for(uint8_t i=0;i<size;i++) {
        printf("array[%d]: %.2f\n", i, array[i]);
    }
    putchar('\n');
}

float absFloat(float x) {
    if(x > 0) return x;
    else return -x;
}

int compareFloat(const void *a, const void *b) {
    float elem1 = *(float *)a; // fac conversia din (void *) in (float *) cu (float *)a, apoi dereferentiez pentru a afla valoarea 
    float elem2 = *(float *)b;
    return elem1 - elem2; // valoare negativa => valorile NU se schimba, deci pentru elem1 < elem2 nu se schimba

    // return *(float *)a - *(float *)b;
}

int searchFunction(const void *x, const void *arrayMember) {
    if(*(float *)x < *(float *)arrayMember) return -1; // dereferentiere la pointer-ul castuit in float (float *)x
    else if(*(float *)x == *(float *)arrayMember) return 0;
    else return 1;
}

int main() {
    uint8_t n = 0;
    float array[9]; // n<10
    float x = 0;

    scanf("%hhu", &n);
    if(n >= 10) {
        fprintf(stderr, "Nu s-a citit bine n\n");
        exit(-1);
    }
    readArray(array, n);
    scanf("%g", &x);

    qsort(array, n, sizeof(float), compareFloat);
    if((int *)bsearch(&x, array, n, sizeof(float), searchFunction) == NULL) {
        printf("Nu s-a gasit valoarea in vector\n");
    } else {
        printf("Valoarea este in vector\n");
    }

    return 0;
}