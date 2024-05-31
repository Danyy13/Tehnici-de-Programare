#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
    Aplicatia 6.1: Sa se modifice exemplul 2 astfel incat functia err sa incapsuleze si conditia
    de eroare. Pentru aceasta, ea primeste in plus pe prima pozitie o variabila de tip int care
    reprezinta o valoare logica. Daca valoarea este true, se va executa err ca in exemplu,
    altfel err nu va avea niciun efect.
    Exemplu de folosire: err(n<=0||n>100,"n invalid: %d\n",n); // fara if in fata, deoarece err
    incapsuleaza conditia
*/

void err(int conditie, const char *fmt, ...) {
    va_list va; // pointer la lista de argumente variabile (varargs)
    va_start(va, fmt); // va trebuie initializat cu ultimul argument fix al functiei
    if(conditie) {
        fprintf(stderr, "eroare: ");
        vfprintf(stderr, fmt, va); // varianta de fprintf care primeste o lista de argumente variabile
        fputc('\n', stderr);
        va_end(va); // dupa folosirea argumentelor variabile, trebuie apelat va_end
        exit(EXIT_FAILURE);
    } else {
        va_end(va); // dupa folosirea argumentelor variabile, trebuie apelat va_end
    }
}

int main() {
    int i, n;
    float x, y, e, min, max;
    printf("n="); scanf("%d",&n);
    err(n<=0 || n>100, "n invalid: %d\n",n);
    printf("x="); scanf("%g",&x);
    printf("y="); scanf("%g",&y);
    err(x >= y, "x=%g nu este mai mic decat y=%g\n", x, y);
    max = x;
    min = y;
    for(i=0;i<n;i++) {
        printf("e="); scanf("%g",&e);
        err(e<x || e>y, "element invalid: %g\n", e);
        if(e < min) min=e;
        if(e > max) max=e;
    }
    printf("min: %g, max: %g\n", min, max);
    return 0;
}