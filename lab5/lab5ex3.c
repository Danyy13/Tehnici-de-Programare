#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 5.3: Se citesc m si n de la tastatura, iar apoi o matrice a[m][n] cu elemente de tip
    intreg. Sa se scrie matricea intr-un fisier binar, prima oara scriindu-se m si n, iar apoi
    elementele, asa cum sunt dispuse ele in memorie. Sa se citeasca matricea din fisier intr-o
    variabila b si sa se afiseze.
*/

#define SIZE_MAX 100
#define FISIER "matrice.dat"

void printMatrix(unsigned int rows, unsigned int cols, int matrix[][SIZE_MAX]) {
    for(unsigned int i=0;i<rows;i++) {
        for(unsigned int j=0;j<cols;j++) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

void readMatrix(unsigned int rows, unsigned int cols, int matrix[][SIZE_MAX]) {
    for(unsigned int i=0;i<rows;i++) {
        for(unsigned int j=0;j<cols;j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void writeMatrixToFile(FILE *file, unsigned int *rows, unsigned int *cols, int matrix[][SIZE_MAX]) {
    if((file = fopen(FISIER, "wb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier\n");
        exit(-1);
    }

    fwrite(rows, sizeof(unsigned int), 1, file);
    fwrite(cols, sizeof(unsigned int), 1, file);
    // fwrite(matrix, sizeof(int), (*rows) * (*cols), file); // gresit daca m si n nu sunt exacte, adica daca matricea nu este alocata dinamic - scrie si zonele de memorie nealocate 

    // scriem matricea rand cu rand
    for(unsigned int i=0;i<*rows;i++) {
        // fseek(file, SIZE_MAX, SEEK_SET); // muta cursorul la inceput de rand
        fwrite(matrix[i], sizeof(int), *cols, file);
    }

    // o alta optiune ar fi sa aloc dinamic matricea pentru a nu avea offset-uri in memorie de la un int la altul

    fclose(file);
}

void getMatrixFromFile(FILE *file, unsigned int *rows, unsigned int *cols, int matrix[][SIZE_MAX]) {
    // se poate si fara rows si cols transmisi ca parametri, dar le pastrez pentru a generaliza
    if((file = fopen(FISIER, "rb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier\n");
        exit(-1);
    }

    fread(rows, sizeof(unsigned int), 1, file);
    fread(cols, sizeof(unsigned int), 1, file);

    // citim matricea la fell cum am scris-o => rand cu rand
    for(unsigned int i=0;i<*rows;i++) {
        fread(matrix[i], sizeof(int), *cols, file); // matrix[i] - adresa de la inceputul fiecarui rand
    }

    fclose(file);
}

int main() {
    unsigned int m = 0, n = 0;
    int a[SIZE_MAX][SIZE_MAX], b[SIZE_MAX][SIZE_MAX];
    FILE *file = NULL;

    scanf("%u %u", &m, &n);
    readMatrix(m, n, a);

    writeMatrixToFile(file, &m, &n, a);
    getMatrixFromFile(file, &m, &n, b);

    printMatrix(m, n, b);

    return 0;
}