#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
    Subiect 8.1: Se citesc de la tastatura doua numere n si m, n >= m. Pe urma se citesc doua
    matrici patratice de dimensiuni n, respectiv m, continand numere intregi. Afisati toate
    pozitiile unde a doua matrice apare in prima matrice. Afisarea se va face pe ecran sub
    forma unor perechi de forma (linie, coloana). Daca a doua matrice nu apare in prima matrice,
    se va afisa textul "Nu apare".
    Spre exemplu daca se introduce:

    5 3
    1 0 1 1 1
    0 1 0 1 1
    1 0 1 1 1
    0 1 0 1 1
    1 0 1 1 1

    0 1 1
    1 0 1
    0 1 1
    
    se va afisa pe ecran:
    (0,1) (2,1)
*/

#define TYPE int // pot schimba tipul de date pe care il are matricea alocata schimband define-ul

void eliberare(uint16_t rows, TYPE **matrix) {
    for(uint16_t i=0;i<rows;i++) free(matrix[i]);
    free(matrix);
}

TYPE **allocMatrix(uint16_t rows, uint16_t cols) {
    TYPE **matrix = NULL;
    if((matrix = (TYPE **)malloc(rows * sizeof(TYPE *))) == NULL) {
        fprintf(stderr, "Eroare la alocare linii\n");
        exit(-10);
    }
    for(uint16_t i=0;i<rows;i++) {
        if((matrix[i] = (TYPE *)malloc(cols * sizeof(TYPE))) == NULL) {
            for(i--;i>=0;i--) free(matrix[i]);
            free(matrix);
            fprintf(stderr, "Eroare la alocare coloane\n");
            exit(-11);
        }
    }
    return matrix;
}

void readMatrix(uint16_t size, int **matrix) {
    for(uint16_t i=0;i<size;i++) {
        for(uint16_t j=0;j<size;j++) {
            if(scanf("%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Eroare la citire\n");
                exit(-1);
            }
        }
    }
}

void inside(uint16_t sizeA, uint16_t sizeB, TYPE **a, TYPE **b) {
    if(sizeA == sizeB) { // verific daca matricile sunt egale
        uint8_t ok = 1; 
        for(uint16_t i=0;i<sizeA;i++) {
            for(uint16_t j=0;j<sizeB;j++) {
                if(a[i][j] != b[i][j]) {
                    ok = 0;
                    break;
                }
                if(!ok) break;
            }
        }
        if(ok) printf("(0, 0)"); // doar in 0 si 0 poate fi aparitia lui b in a in acest caz
    } else {
        TYPE firstB = b[0][0];
        for(uint16_t iA=0;iA<(sizeA - sizeB + 1);iA++) {
            for(uint16_t jA=0;jA<(sizeA - sizeB + 1);jA++) { 
                // nu trebuie sa parcurg pe coloane decat pana la (sizeA - sizeB + 1) deoarece si matricea b are o marime sizeB ce poate depasi sizeA - jA (cat ramane de parcurs) 
                // ex.: daca sunt pe elementul de pe coloana jA = 3 si sizeA = 5, iar matricea b are sizeB = 4 elemente clar nu voi putea gasi matricea B in A
                // (cu indexare de la 0 as putea gasi matricea b in a daca sizeB este maxim 2)
                // parcurgem prima matrice si vedem daca se potriveste un element cu primul element al matricei b
                if(a[iA][jA] == firstB) {
                    // printf("%d %d\n", iA, jA);
                    uint8_t ok = 1; // ramane 1 cat timp valorile sunt la fel
                    for(uint16_t iB=iA;iB<(iA + sizeB);iB++) {
                        for(uint16_t jB=jA;jB<(jA + sizeB);jB++) { // trebuie sa parcurg sizeB pozitii incepand de la iA, de unde incepe si iB
                            if(a[iB][jB] != b[iB - iA][jB - jA]) { // iB - iA !
                                ok = 0;
                                break;
                            }
                        }
                        if(!ok) break;
                    }
                    if(ok) printf("(%hu, %hu) ", iA, jA);
                }
            }
        }
    }
    putchar('\n');
}

int main() {
    uint16_t n = 0, m = 0;
    TYPE **a = NULL, **b = NULL;

    scanf("%hu %hu", &n, &m);
    if(n < m) {
        fprintf(stderr, "m trebuie sa fie mai mic sau egal cu n\n");
        exit(-1);
    }

    a = allocMatrix(n, n);
    b = allocMatrix(m, m);

    readMatrix(n, a);
    readMatrix(m, b);

    inside(n, m, a, b);

    eliberare(n, a);
    eliberare(m, b);

    return 0;
}