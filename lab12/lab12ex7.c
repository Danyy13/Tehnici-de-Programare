#include <stdio.h>

/*
    Aplicatia 12.7: Se cere 0 < n <= 100 si apoi n valori pozitive intregi, reprezentand laturile
    unor patrate. In final se cere 0 < p <= 100, valoare intreaa, reprezentand latura unui patrat.
    Se cere sa se determine daca exista un aranjament al celor n patrate in interiorul patratului
    de latura p, astfel incat toate patratele sa fie continute in acesta si sa nu existe
    suprapuneri intre patrate.
*/

#define MAX_SIZE 100

int squared(int n) {
    return n * n;
}

void citire(int *d, int *n, int latura[]) {
    scanf("%d %d", d, n);
    for(int i=1;i<=*n;i++) {
        scanf("%d", latura + i);
    }
}

void afisare(int array[], int size) {
    for(int i=1;i<=size;i++) {
        printf("%d ", array[i]);
    }
    putchar('\n');
}

int valid(int v[], int k) {
    for(int i=1;i<k;i++) {
        if(v[i] >= v[i + 1]) return 0;
    }
    return 1;
}

void back(int k, int suma, int v[], int latura[], int n, int d, int *solutionFound) {
    for(int i=1;i<=n;i++) {
        v[k] = latura[i];
        if(valid(v, k)) {
            if(suma + squared(latura[i]) == d) { // solutie
                afisare(v, k);
                *solutionFound = 1;
            } else {
                back(k + 1, suma + squared(latura[i]), v, latura, n, d, solutionFound);
            }
        }
    }
}

int main() {
    int d = 0;
    int n = 0;
    int latura[MAX_SIZE];
    int v[MAX_SIZE];
    int solutionFound = 0;

    citire(&d, &n, latura); // se citesc segmenetele in ordine crescatoare
    back(1, 0, v, latura, n, d, &solutionFound);

    if(!solutionFound) {
        printf("Nu exista un aranjament satisfacator al patratelor\n");
    }

    return 0;
}