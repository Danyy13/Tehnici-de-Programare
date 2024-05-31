#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
    Aplicatia 2.1: Se cere un numar n si apoi un vector de n rezultate ale studentilor la un
    examen. Fiecare rezultat este definit prin (nume,nota). Se cere sa se sorteze folosind
    qsort vectorul in ordinea notelor, notele cele mai mari fiind primele. Daca doua note sunt
    identice, rezultatele respective se vor sorta in ordinea alfabetica a numelor.
*/

typedef struct {
    char nume[60];
    uint8_t nota; // nota : 4 ar fi folosit doar 4 biti -> de ajuns pentru numere de la 0 la 10
}Rezultat;

void afisare(Rezultat *rezultat, unsigned int size) {
    unsigned int i = 0;
    for(i=0;i<size;i++) {
        printf("%s %d\n", rezultat[i].nume, rezultat[i].nota);
    }
}

void citire(Rezultat *rezultat, unsigned int *size) {
    unsigned int i = 0;
    for(i=0;i<*size;i++) {
        if(scanf("%s %hhd", rezultat[i].nume, &rezultat[i].nota) != 2) {
            break;
        }
    }

    *size = i;
    // realocam daca am citit mai putine
    rezultat = (Rezultat*)realloc(rezultat, (long unsigned int)size * sizeof(Rezultat));
    // nu trebuie verificat deoarece alocam mai putina memorie deci soto avem
}

int cmpNume(Rezultat *a, Rezultat *b) {
    if(strcmp(a->nume, b->nume) > 0) return 1;
    else if(strcmp(a->nume, b->nume) < 0) return -1;
    return 0;
}

int cmpNote(const void *a, const void *b) {
    const Rezultat *p1 = (const Rezultat*)a;
    const Rezultat *p2 = (const Rezultat*)b;
    if(p1->nota > p2->nota) return 1;
    else if(p1->nota < p2->nota) return -1;
    else {
        qsort(rezultat, size, sizeof(Rezultat), cmpNume);
        return 0;
    }
}

int main(int argc, char **argv) {
    Rezultat *rezultat;
    unsigned int size = 0;

    scanf("%d", &size);

    if((rezultat = (Rezultat*)malloc(size * sizeof(Rezultat))) == NULL) {
        printf("Eroare la malloc\n");
        free(rezultat);
        exit(-1);
    }

    citire(rezultat, &size);
    afisare(rezultat, size);

    qsort(rezultat, size, sizeof(Rezultat), cmpNote);

    afisare(rezultat, size);

    free(rezultat);

    return 0;
}