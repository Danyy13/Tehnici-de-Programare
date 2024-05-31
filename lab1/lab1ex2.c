#include <stdio.h>

/*
    Aplicatia 8.2: Se citesc de la tastatura m si n, fiecare mai mici decat 10. Sa se creeze o
    matrice in care la fiecare pozitie sa fie maximul indecsilor acelei pozitii si sa se
    afiseze matricea.
*/

int main() {
    unsigned int m = 0, n = 0, i = 0, j = 0;
    scanf("%d %d", &m, &n);

    int a[m][n];

    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            if(i > j) {
                a[i][j] = i;
            } else {
                a[i][j] = j;
            } // a[i][j] ia valoarea maxima dintre cei doi indecsi
        }
    }

    // afisare matrice
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}