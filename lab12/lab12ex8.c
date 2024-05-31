#include <stdio.h>

/*
    Aplicatia 12.8: Se cere d de tip intreg reprezentand lungimea unei drepte si 0 < n <= 100 un
    numar de segmente. In cate feluri se poate imparti dreapta data in n segmente consecutive,
    avand fiecare lungimi intregi pozitive, astfel incat fiecare segment sa fie strict mai mare
    decat cel de dinaintea sa?
*/

#define MAX_SIZE 100

void citire(int *d, int *n, int segment[]) {
    scanf("%d %d", d, n);
    for(int i=1;i<=*n;i++) {
        scanf("%d", segment + i);
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

void back(int k, int suma, int v[], int segment[], int n, int d) {
    for(int i=1;i<=n;i++) {
        v[k] = segment[i];
        if(valid(v, k)) {
            if(suma + segment[i] == d) { // solutie
                afisare(v, k);
            } else {
                back(k + 1, suma + segment[i], v, segment, n, d);
            }
        }
    }
}

int main() {
    int d = 0;
    int n = 0;
    int segment[MAX_SIZE];
    int v[MAX_SIZE];

    citire(&d, &n, segment); // se citesc segmenetele in ordine crescatoare
    back(1, 0, v, segment, n, d);

    return 0;
}