#include <stdio.h>
#include <stdint.h>

/*
    Aplicatia 12.1: Se citesc doua numere naturale n si k. Generati si afisati toate numerele
    naturale formate din n cifre care contin exact k cifre de 1.
*/

#define MAX_SIZE 100
#define CIFRA 1

void afisare(unsigned int array[], unsigned int size) {
    for(unsigned int i=0;i<size;i++) {
        printf("%d", array[i]);
    }
    putchar('\n');
}

int valid(unsigned int k, unsigned int v[], int numarCifre) {
    if(k == 0 && v[k] == 0) return 0;
    return 1;
}

void back(unsigned int k, unsigned int v[], int numarCifre, unsigned int n) {
    if(k == n) {
        if(!numarCifre) afisare(v, k);
        return;
    }

    for(unsigned int i=0;i<=9;i++) {
        v[k] = i;
        if(valid(k, v, numarCifre)) {
            if(v[k] == CIFRA)
                back(k + 1, v, numarCifre - 1, n);
            else
                back(k + 1, v, numarCifre, n);
        }
    }
}

int main() {
    unsigned int n = 0;
    int numarCifre = 0;
    unsigned int v[MAX_SIZE];

    scanf("%d %d", &n, &numarCifre);

    back(0, v, numarCifre, n);

    return 0;
}