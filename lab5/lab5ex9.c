#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
    Aplicatia 5.9: Sa se scrie un program care primeste o serie de n programe in linia de comanda
    si le concateneaza pe primele n-1 intr-un nou fisier avand numele specificat pe ultima pozitie
    din linia de comanda.
    Exemplu: ./concat 1.dat 2.dat 3.dat rez.dat -> concateneaza continutul fisierelor
    {1.dat, 2.dat, 3.dat} intr-un nou fisier, denumit rez.dat
*/

long int getFileSize(char *filepath) {
    FILE *file = NULL;
    if((file = fopen(filepath, "rb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier in getFileSize\n");
        exit(-3);
    }

    long int size = 0;
    fseek(file, 0, SEEK_END); // finalul fisierului
    size = ftell(file); // retin valoarea de la final
    fseek(file, 0, SEEK_SET); // ma intorc la inceputul fisierului
    
    fclose(file);
    return size;
}

// functia aloca de fiecare data o zona de memorie la fel de mare ca marimea fisierului si dupa o elibereaza
// alta metoda - retinem memoria alocata si o suprascriem la fiecare fisier, realocand memorie doar daca este nevoie de o zona mai mare de memorie la fisierele urrmatoare (daca fisierele sunt mai mici nu se mai aloca deloc)
char *getDataFromFile(char *filepath, unsigned int fileNumber) {
    FILE *file = fopen(filepath, "rb");
    if(file == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier %d\n", fileNumber + 1); // indexare de la 0
        exit(-100);
    }

    char *buffer = NULL; // string in care o sa stocam datele din fisier
    long int size = getFileSize(filepath);
    
    if((buffer = (char *)malloc(size * sizeof(char))) == NULL) {
        fprintf(stderr, "Eroare la alocare dinamica\n");
        exit(-2);
    }

    fread(buffer, sizeof(char), size, file);

    fclose(file);
    return buffer;
}

void concatenateFiles(char *finalFilePath, unsigned int fileNumber, ...) {
    va_list fileName;
    va_start(fileName, fileNumber); // lista, ultimul parametru inainte de ...

    FILE *finalFile = NULL;
    if((finalFile = fopen(finalFilePath, "wb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier de write\n");
        exit(-1);
    }

    char *buffer = NULL;
    for(unsigned int i=0;i<fileNumber;i++) {
        char *path = va_arg(fileName, char *);
        // copiem continutul din fisierele de intrare intr-un buffer alocat dinamic de marimea fisierului si apoi transmitem datele in fisierul out
        buffer = getDataFromFile(path, i);
        fwrite(buffer, sizeof(char), getFileSize(path), finalFile);
        free(buffer);
    }

    fclose(finalFile);
    va_end(fileName);
}

int main(int argc, char *argv[]) {
    // concatenateFiles(argv[4], argc - 2, argv[1], argv[2], argv[3]); // cu numar variabil de argumente

    FILE *finalFile = NULL;
    if((finalFile = fopen(argv[argc - 1], "wb")) == NULL) { // ultimul fisier transmis
        fprintf(stderr, "Eroare la deschidere fisier de write\n");
        exit(-1);
    }

    for(unsigned int i=1;i<argc-1;i++) { // celelalte fisiere
        char *buffer = getDataFromFile(argv[i], i);
        fwrite(buffer, sizeof(char), getFileSize(argv[i]), finalFile);
        free(buffer);
    }

    fclose(finalFile);
    return 0;
}