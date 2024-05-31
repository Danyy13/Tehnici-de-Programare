#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
    Aplicatia 8.7: Se citeste un numar n <= 10 de orase si apoi pentru fiecare 2 orase se citeste
    distanta directa dintre ele. Daca distanta este 0, inseamna ca intre acele orase nu exista
    drum direct. Sa se afiseze perechea de orase cele mai apropiate intre ele in mod direct.

    voi citi valorile intrr-o matrice triunghiulara cu valori deasupra diagonalei secundare,
    deci fiecare oras n va avea drumurile de la orasele n+1, n+2, ...
    elimin astfel nevoia de a face o matrice simetrica si elimin cateva operatii
*/

void checkSize(uint8_t size) {
    if(size < 2) {
        fprintf(stderr, "Nu exista drum de citit\n");
        exit(-2);
    }
    if(size > 10) {
        fprintf(stderr, "Marimea matricei depaseste valoarea maxima\n");
        exit(-3);
    }
}

void readMatrixTriangle(uint8_t size, unsigned int matrix[][size]) {
    // citeste o matrice triunghi cu valori deasupra diagonalei secundare
    // nu se vor citi n * n elemente, ci se vor pune in fisier in forma de "triunghi"
    // ex
    // 1 2 3
    // 1 2
    // 1

    uint8_t i = 0;
    uint8_t n = size;
    for(i=0;i<size;i++) {
        for(uint8_t j=0;j<n;j++) {
            if(scanf("%u", &matrix[i][j]) != 1) {
                fprintf(stderr, "Eroare la citire\n");
                exit(-1);
            }
        }
        n--;
    }
}

void closest(uint8_t size, unsigned int matrix[][size]) { // opereaza pe o matrice triunghiulara cu valori deasupra diagonalei secundare
    uint8_t n = size;
    unsigned int min = 0xFFFF; // maximul unsigned int
    uint8_t city1 = 0, city2 = 0;
    for(uint8_t i=0;i<size;i++) {
        for(uint8_t j=0;j<n;j++) {
            if(matrix[i][j] != 0)
                if(matrix[i][j] < min) {
                    min = matrix[i][j];
                    city1 = i + 1;
                    city2 = city1 + j + 1; // fiecare linie i contine (pe pozitiile j) lungimea drumului la cele i+1 orase de dupa orasul i
                    // pentru i = 2 si j = 2 inseamna ca am gasit drumul [i,j] = [2,4] din cauza ca nu retinem dubluri pentru fiecare drum intr-o matrice simetrica, ci doar o singura valoare intr-o matrice triunghiulara
                }
        }
    }
    printf("Orasele %d si %d sunt cele mai apropiate\n", city1, city2);
}

int main() {
    uint8_t n = 0;
    unsigned int matrix[10][10]; // aare valori doar intre 0 si n-1 

    scanf("%hhd", &n);
    checkSize(n); //  verificam daca n convine

    readMatrixTriangle(n, matrix);
    closest(n, matrix);

    return 0;
}