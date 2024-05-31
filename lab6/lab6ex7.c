#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

/*
    Aplicatia 6.7: Sa se scrie o functie int comune(int nVec,...) care primeste un numar de
    vectori cu valori de tip int si vectorii propriu-zisi. Fiecare vector se da prin doua
    argumente: un pointer la elementele sale si dimensiunea. Functia va returna numarul de
    elemente comune care se regasesc in toti vectorii.
    Exemplu: comune(3,v1,2,v2,3,v3,3) => returneaza 2 pentru v1={5,8}, v2={8,3,5}, v3={5,0,8}
*/

// presupunem ca avem o valoare maxima pe care elementele din vectori nu o poate depasi ca sa putem folosi metoda cu un vector de frecventa 
#define MAX 1000

int comune(int nVec, ...) {
    int *array = NULL;
    unsigned int arraySize = 0, common = 0; // common - numarul de elemente comune
    uint8_t frecventa[MAX]; // vector de frecventa cu maxim MAX elemente
    // initializam vectorul frecventa
    memset(frecventa, 0, MAX * sizeof(uint8_t));
    va_list args;
    va_start(args, nVec);

    // !presupunem ca valorile nu apar de doua ori in acelasi vector 
    while(nVec--) { // arrayNumber retine vectorul la care suntem cu iteratia
        array = va_arg(args, int *); // retinem adresa vectorului in array
        arraySize = va_arg(args, int);
        for(unsigned int i=0;i<arraySize;i++) {
            // printf("val: %d\n", array[i]);
            frecventa[array[i]]++;
        }
    }

    for(unsigned int i=0;i<MAX;i++) {
        printf("%d %d\n", i, frecventa[i]);
        if(frecventa[i] == 3) common++;
    }

    va_end(args);
    return common;
}

int main() {
    int v1[] = {5, 8}, v2[] = {8, 3, 5}, v3[] = {5, 0, 8};

    printf("%d\n", comune(3, v1,2, v2,3, v3,3));
    
    return 0;
}