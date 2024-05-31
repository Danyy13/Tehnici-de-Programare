#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
    Aplicatia 6.10: Sa se scrie un program denumit criptare, care cripteaza/decripteaza un text
    primit in linia de comanda. Programul va fi apelat in felul urmator:

    ./criptare operatie cheie cuvant1 cuvant2 ...

    Operatia poate fi enc pentru criptare sau dec decriptare. Cheia este un numar intreg.
    Algoritmul de criptare este urmatorul: pentru fiecare litera din cuvinte se considera codul
    sau ASCII, la care se aduna cheia specificata, rezultand un nou cod ASCII, cel al literei
    criptate. Adunarea este circulara, adica 'z' incrementat cu 1 devine 'a'.
    Decriptarea este inversa: din cuvintele criptate se scade circular cheia specificata.
    Literele mari se transforma la inceput in litere mici.
    Exemple:
    ./criptare enc 1 zaraza -> absbab
    ./criptare dec 1 bcfdfebs -> abecedar
    ./criptare enc 10 vine VINE primavara PRImaVAra -> fsxo fsxo zbswkfkbk zbswkfkbk
*/

#define OPERATION argv[1]
#define KEY argv[2]

uint8_t isUpper(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

void crypt(char *string, unsigned int key) {
    unsigned int stringSize = strlen(string);
    for(unsigned int i=0;i<stringSize;i++) {
        if(isUpper(string[i])) {
            string[i] += 32; // il facem litera mica
        }

        // poate produce depasirea tipului char (ex.: v = 118, +10 = 128 deci depaseste char => simboluri ciudate)l, problema asemanatoare cu cea de la cautarea binara
        // string[i] += key;
        // verificam daca am depasit intervalul a-z in ambele parti, deoarece decriptand scadem cu key
        // if(string[i] > 'z') string[i] -= 'z';
        // else if(string[i] < 'a') string[i] += 'a'; 

        if(string[i] + key > 'z') {
            string[i] = 'a' + (key - ('z' - string[i])) - 1; // adaug lui a cat ramane din cheie daca aceasta trece de 'z'
        } else if(string[i] + key < 'a') {
            // in cazul acesta key este cu minus
            string[i] = 'z' + (key + (string[i] - 'a')) + 1;
        } else {
            string[i] += key;
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc < 4) {
        fprintf(stderr, "Eroare la numarul de argumente\n");
        exit(-1);
    }

    int8_t key = atoi(KEY) % 26; // sunt 26 de litere in alfabet, deci un shift cu 27 e acelasi cu un shift cu 1
    if(strcmp(OPERATION, "dec") == 0) {
        key = -key; // facem scadere din adunare daca trebuie sa decriptam
    }

    for(unsigned int i=3;i<argc;i++) {
        crypt(argv[i], key);
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}