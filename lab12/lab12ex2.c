#include <stdio.h>

/*
    Aplicatia 12.2: Se citeste un numar natural n. Afisati permutarile multimii 1,2,3...n in care
    pana la jumatate elementele sunt in ordine descrescatoare, iar de la jumatate pana la final
    in ordine crescatoare.
    Exemplu:
    n = 5
    permutarile care respecta conditia sunt:
    3 2 1 4 5
    4 2 1 3 5
    4 3 1 2 5
    5 2 1 3 4
    5 3 1 2 4
    5 4 1 2 3
*/

void afisare(unsigned int array[], unsigned int size) {
    for(unsigned int i=0;i<size;i++) {
        printf("%d", array[i]);
    }
    putchar('\n');
}

int valid(unsigned int k, unsigned int v[]) {
    for(unsigned int i=0;i<k;i++) {
        if(v[i] == v[k]) return 0;
    }
    return 1;
}

int solutie(unsigned int k, unsigned int v[], unsigned int n) {
    for(unsigned int i=0;i<n/2 - 1;i++) {
        if(v[i] <= v[i + 1]) return 0;
    }
    for(unsigned int i=n/2;i<n - 1;i++) {
        if(v[i] >= v[i + 1]) return 0;
    }
    return 1;
}

void back(int k, unsigned int v[], unsigned int n) {
    if(k == n) {
        if(solutie(k, v, n)) afisare(v, k);
        return;
    }

    for(unsigned int i=1;i<=n;i++) {
        v[k] = i;
        if(valid(k, v))
            back(k + 1, v, n);
    }
}

int main() {
    unsigned int n = 0;
    unsigned int v[10];

    scanf("%d", &n);

    back(0, v, n);

    return 0;
}