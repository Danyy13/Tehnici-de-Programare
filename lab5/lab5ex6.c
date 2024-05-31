#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 5.6: Sa se scrie un program care primeste 2 fisiere in linia de comanda si le
    compara intre ele. Pentru fiecare octet diferit gasit, se afiseaza offsetul acestuia si
    valorile sale din fiecare fisier, in hexazecimal, pe cate 2 cifre. Daca fisierele sunt de
    dimensiuni diferite, in final se vor afisa toti octetii din fisierul mai mare. Daca
    fisierele sunt identice, programul nu va afisa nimic.
*/

int main(int argc, char *argv[]) {
    FILE *file1 = NULL, *file2 = NULL;
    if((file1 = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "Eroare deschidere fisier 1\n");
        exit(-1);
    }
    if((file2 = fopen(argv[2], "rb")) == NULL) {
        fprintf(stderr, "Eroare deschidere fisier 2\n");
        exit(-2);
    }

    // citim octet cu octet din fiecare fisier si comparam
    unsigned char byte1 = 0, byte2 = 0;
    while(fread(&byte1, sizeof(unsigned char), 1, file1) && fread(&byte2, sizeof(unsigned char), 1, file2)) {
        // printf("%c %c\n", byte1, byte2);
        if(byte1 != byte2) {
            printf("%ld: %s: %02x, %s: %02x\n", ftell(file1), argv[1], byte1, argv[2], byte2);
        }
    }

    // verific pe rand daca au ramas date in fiecare fisier si daca da le afisez in format
    while(fread(&byte1, sizeof(unsigned char), 1, file1)) printf("%ld: %s: %02x\n", ftell(file1), argv[1], byte1); 
    while(fread(&byte2, sizeof(unsigned char), 1, file2)) printf("%ld: %s: %02x\n", ftell(file2), argv[2], byte2); 

    fclose(file1);
    fclose(file2);
    return 0;
}