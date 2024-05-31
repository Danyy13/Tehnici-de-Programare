#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
    Aplicatia 8.6: Se citeste un numar n<=10 de persoane, fiecare persoana fiind identificata
    printr-un numar intre 0..n-1. O persoana poate fi prietena cu oricare alte persoane. Dupa
    ce s-a citit n, se vor citi pentru fiecare persoana prietenii ei pe rand. Sa se afiseze
    pentru fiecare persoana cati prieteni are.

    1) o persoana poate avea mai multi prieteni decat alta => alegem o valoare pe care sa o ignoram
    2) daca valoarea nu este in intervalul [0, n-1], nu se trece
    3) presupunem ca o persoana nu se poate trece pe ea insasi ca prieten => m[i][j] != i
    4) presupunem ca nu se poate trece de doua ori acelasi prieten la o persoana
    ex: persoana 1 : 4 4 5 1 4
*/

#define IGNORE_VALUE -1

void readMatrix(uint8_t size, int8_t *matrix) {
    uint8_t i = 0;
    for(i=0;i<size;i++) {
        for(uint8_t j=0;j<size;j++) {
            if(scanf("%hhd", matrix + (i * size) + j) != 1) {
                fprintf(stderr, "Eroare la citire\n");
                exit(-2);
            }
        }
    }
}

void showFriends(uint8_t size, int8_t matrix[][size]) {
    for(uint8_t i=0;i<size;i++) {
        uint8_t friends = 0;
        for(uint8_t j=0;j<size;j++) {
            if(matrix[i][j] >= 0 && matrix[i][j] <= 10) friends++;
        }
        printf("Persoana %d are %d prieteni\n", i + 1, friends);
    }
}

// void initMatrix(uint8_t size, int8_t *matrix) {
//     memset(matrix, -1, size * size);
// }

int main() {
    uint8_t n = 0;
    int8_t matrix[10][10]; // are valori doar intre 0 si n-1 si -1 daca ignoram valoarea

    scanf("%hhd", &n);
    if(n > 10) { // verific doar in dreapta deoarece n este unsigned
        fprintf(stderr, "Marimea matricei depaseste valoarea maxima\n");
        exit(-1);
    }

    // initMatrix(n, *matrix);
    readMatrix(n, *matrix);
    showFriends(n, matrix);
    return 0;
}