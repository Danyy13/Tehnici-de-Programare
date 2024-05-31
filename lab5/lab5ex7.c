#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Aplicatia 5.7: Un program primeste in linia de comanda un nume de fisier, un offset dat in
    hexazecimal si apoi o serie de octeti, specificati tot in hexazecimal. Programul va scrie in
    fisierul specificat, incepand de la offsetul dat toti octetii primiti in linia de comanda.
    Restul fisierului va ramane nemodificat.
    Exemplu: ./inlocuire 1.dat 4a0f 9e b0 51 -> scrie octetii {9e, b0, 51} in fisierul 1.dat,
    incepand cu pozitia 4a0f
*/

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if((file = fopen(argv[1], "wb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier\n");
        exit(-1);
    }

    long int offset = 0;
    offset = strtol(argv[2], NULL, 16); // transform argumentul din sir de caractere in numar un baza 16
    // printf("%ld\n", offset);

    fseek(file, offset, SEEK_SET); // mut cursorul la offset

    for(unsigned int i=3;i<argc;i++) {
        long int writeValue = strtol(argv[i], NULL, 16); // transform argumentul din sir de caractere in valoare pe care sa o pot scrie in binar
        fwrite(&writeValue, sizeof(char), 1, file);
    }

    fclose(file);
    return 0;
}