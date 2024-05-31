#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 11.4: La un campionat iau parte n jucatori, fiecare definit prin nume (max 15
    caractere) si valoare (int). Jucatorii sunt distribuiti in m grupe, n divizibil cu m.
    Distributia jucatorilor in grupe se face dupa valoarea lor, astfel incat cei mai valorosi m
    jucatori sa fie fiecare in alta grupa, apoi urmatorii m cei mai valorosi ramasi sa fie si ei
    in grupe diferite si tot asa, pana cand toti jucatorii sunt distribuiti. Sa se afiseze
    impartirea jucatorilor pe grupe, pentru valori citite dintr-un fisier.
*/

#define MAX_SIZE 100

typedef struct {
    int val;
    char nume[16];
}JUCATOR;

int compar(const void *elem1, const void *elem2) {
    const JUCATOR *jucator1 = (const JUCATOR *)elem1;
    const JUCATOR *jucator2 = (const JUCATOR *)elem2;
    return (jucator2->val - jucator1->val); // jucator2 - jucator1 => descrescator
}

void afisare(JUCATOR jucatori[], unsigned int numarJucatori) {
    for(unsigned int i=0;i<numarJucatori;i++) {
        printf("%s %d\n", jucatori[i].nume, jucatori[i].val);
    }
}

int main() {
    unsigned int numarJucatori = 0, grupe = 0;
    JUCATOR jucatori[MAX_SIZE];

    scanf("%u %u", &grupe, &numarJucatori);
    for(unsigned int i=0;i<numarJucatori;i++) {
        scanf("%s %d", jucatori[i].nume, &jucatori[i].val);
    }

    qsort(jucatori, numarJucatori, sizeof(JUCATOR), compar);

    for(unsigned int i=0;i<grupe;i++) {
        printf("Grupa %d\n", i + 1);
        for(unsigned int j=0;j<numarJucatori/grupe;j++) {
            printf("%s %d\n", jucatori[j * (grupe) + i].nume, jucatori[j * (grupe) + i].val);
        }
        putchar('\n');
    }

    // afisare(jucatori, numarJucatori);

    return 0;
}