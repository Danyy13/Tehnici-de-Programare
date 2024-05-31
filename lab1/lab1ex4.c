#include <stdio.h>

/*
    Aplicatia 8.4: Se citeste de la tastatura o matrice patratica cu n <= 50 linii si coloane.
    Sa se interschimbe elementele de deasupra diagonalei principale, considerata ca axa de
    simetrie, cu elementele de sub diagonala principala, elementele de pe diagonala principala
    ramanand la fel. De exemplu matricea:
1 2 3
4 5 6
7 8 9

Va deveni:
1 4 7
2 5 8
3 6 9
*/

int main() {
    unsigned int n = 0, i = 0, j = 0;
    scanf("%d", &n);

    int a[n][n];

    // citesc matricea
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // inversez
    for(i=0;i<n-1;i++) {
        for(j=i+1;j<n;j++) {
            int aux = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = aux;
        }
    }

    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}