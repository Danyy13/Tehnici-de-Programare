#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
    Aplicatia 2.2: Sa se implementeze o functie care primeste ca parametri un vector de intregi,
    numarul elementelor din vector transmis prin adresa si un predicat care testeaza daca un
    intreg indeplineste o anumita conditie. Functia va sterge din vector toate elementele care
    nu indeplinesc conditia data si va actualiza numarul elementelor cu numarul de elemente
    ramas in vector.
    Sa se testeze functia cu un predicat care testeaza daca un numar este negativ si sa se
    afiseze vectorul rezultat.

    practic o functie de filtrare
*/

#define SIZE 100

uint8_t par(int x) {
    return x % 2 == 0;
}

uint8_t negativ(int x) {
    return x < 0;
}

void readArray(int array[], unsigned int *size) {
    unsigned int i = 0;
    while(scanf("%d", &array[i]) == 1 && i < *size) {
        i++;
    }
    *size = i;
}

void printArray(int array[], unsigned int size) {
    for(unsigned int i=0;i<size;i++) {
        printf("%d ", array[i]);
    }
    putchar('\n');
}

void filter(int array[], unsigned int *size, uint8_t (*conditie)(int)) {
    for(unsigned int i=0;i<*size;i++) {
        if(!conditie(array[i])) {
            // scoatem elementul din vector daca nu respecta conditia
            for(unsigned int j=i;j<*size-1;j++) {
                array[j] = array[j+1];
            }
            i--;
            (*size)--;
        }
    }
}

int main() {
    unsigned int size = SIZE;
    int array[SIZE];

    readArray(array, &size);
    filter(array, &size, negativ);
    printArray(array, size);

    return 0;
}