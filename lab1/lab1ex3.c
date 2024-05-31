#include <stdio.h>

/*
    Aplicatia 8.3: Se citeste de la tastaturaa un numar n<=10 si un numar m<=20. Se cere sa se
    scrie un program care genereaza o matrice cu m linii si n coloane in care sunt puse toate
    numerele de la 1,2,3,...,m*n. Se vor utiliza pointeri.
*/

int main() {
    unsigned int n = 0, m = 0;
    scanf("%d %d", &m, &n);

    int a[m][n];
    int *p = NULL;

    for(p=&a[0][0];p<&a[m][0];++p) {
        *p = p - &a[0][0] + 1;
    }

    // citire si afisare
    for(p=&a[0][0];p<&a[m][0];++p) {
        // scanf("%d", p); // citire
        if((p - &a[0][0]) % n == 0 && (p - &a[0][0]) != 0) { 
            printf("\n"); // afisez linie noua daca am scris n elemente si daca nu e primul element
        }
        printf("%5d ", *p);
    }
    printf("\n");

    return 0;
}