#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/*
    Aplicatia 2.4: Sa se implementeze o functie care tabeleaza o functie matematica de un
    parametru, primita ca argument. Functia tabelata primeste un parametru de tip double si
    returneaza o valoare tot de tip double. Functia de tabelare va primi ca parametri: a si b -
    capetele de tip double ale intervalului inchis de tabelat, n - un numar intreg care arata in
    cate segmente egale se imparte intervalul [a,b], incluzand capetele acestuia si f - functia
    de tabelat. Sa se testeze functia de tabelare cu valori a,b si n citite de la tastatura,
    tabeland functiile cos, sqrt si fabs din math.h
    Exemplu: tabelare(-10, 10, 20, fabs) va afisa pe cate o linie valori de forma
    f(-10)=10 f(-9)=9 ... f(10)=10

    Subiectul 2.1 Sa se scrie un program pentru tabelarea unor functii matematice. Programul
    trebuie sa tabeleze functiile (x*x*x+4)/(x*x+5), x+10 si 2*x*x-1.
    Tabelarea se va realiza pe intervalul [A,B] cu pasul P. Valorile A, B si P se vor citi de la
    tastatura. Programul va afisa valorile functiilor sub forma de tabel.
    Trebuie sa se foloseasca pointeri la functii. Scrieti o functie generica pentru tabelarea
    unei functii matematice oarecare. Aceasta functie generica va avea un parametru de tip
    pointer la functie.
    Folosind functia generica, tabelati cele patru funcrii matematice amintite mai sus.
*/

typedef double TYPE; // ca sa  pot modifica usor tipul de date dorit
typedef struct {
    TYPE x;
    TYPE y;
}POINT;
typedef POINT ARRAY_TYPE;

TYPE f1(TYPE x) {
    return (x*x*x+4) / (x*x+5);
}

TYPE f2(TYPE x) {
    return x + 10;
}

TYPE f3(TYPE x) {
    return 2*x*x - 1;
}

ARRAY_TYPE *allocArray(unsigned int size) {
    ARRAY_TYPE *array = NULL;
    if((array = (POINT *)malloc(size * sizeof(POINT))) == NULL) {
        fprintf(stderr, "Eroae la alocare\n");
        exit(-100);
    }
    return array;
}

void printData(ARRAY_TYPE points[], unsigned int size) {
    for(unsigned int i=0;i<size;i++) {
        printf("%lg %lg\n", points[i].x, points[i].y);
    }
}

ARRAY_TYPE *tabelare(TYPE a, TYPE b, unsigned int n, TYPE (*functie)(TYPE)) {
    TYPE h = (b-a)/n; // distanta intre punctele x0 - x1, x1-x2, ..., x(n-1) - x(n)
    // cream un vector in care sa stocam datele tabelate
    ARRAY_TYPE *points = allocArray(n + 1); // n = numarul de intervale => numarul de valori este n + 1 ex.: n = 1, valoei a si b => 2 valori
    for(unsigned int i=0;i<n + 1;i++) {
        points[i].x = a;
        a += h; // folosim a generarea valorilor axei x (valoarea lui a nu va fi modificata dupa iesirea din functie)
        points[i].y = functie(points[i].x); // aflam valoarea functiei in punctul x
    }
    return points; // returnam vectorul cu datele tabelate
}

int main() {
    TYPE a = 0, b = 0;
    unsigned int n = 0;
    ARRAY_TYPE *points; // vector ce va fi alocat dinamic in functie de numarul de subdiviziuni

    scanf("%lg %lg %u", &a, &b, &n);
    if(a >= b) {
        fprintf(stderr, "a >= b\n");
        exit(-1);
    }

    points = tabelare(a, b, n, f3);
    printData(points, n + 1);

    free(points);
    return 0;
}