#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 5.2: Scrieti un program care copiaza continutul unui fisier sursa intr-un fisier
    destinatie. Numele fisierelor se citesc din linia de comanda. Pentru eficienta copierii,
    programul va citi cate un bloc de maxim 4096 de octeti, pe care il va scrie in destinatie.
    Exemplu: ./copiere src.dat dst.dat -> copiaza src.dat in dst.dat
*/

#define CHUNK 4096

void copyChunk(FILE *src, FILE *dst, int size) { // fisierele au fost deja deschise
    size = size % CHUNK; // modulo imi spune cati octeti raman dupa ce copiez fisierul cate CHUNK octeti pana cand raman in fisier mai putin de CHUNK (caz in care trebuie sa scriu mai putini, adica size)
    char buffer[CHUNK];

    // transfer din src in dst cate CHUNK octeti
    while(fread(buffer, sizeof(char), CHUNK, src) == CHUNK) {
        fwrite(buffer, sizeof(char), CHUNK, dst);
    }

    // transfer ultimii octeti ramasi (un numar mai mic decat CHUNK)
    if(size) { // daca au mai ramas date in fisier 
        fread(buffer, sizeof(char), size, src);
        fwrite(buffer, sizeof(char), size, dst);
    }
}

int main(int argc, char *argv[]) {
    FILE *src = NULL, *dst = NULL;

    // deschidem fisierele
    if((src = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier sursa\n");
        exit(-1);
    }
    if((dst = fopen(argv[2], "wb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier destinatie\n");
        exit(-2);
    }

    fseek(src, 0, SEEK_END); // mut cursorul la finalul fisierului
    int size = ftell(src); // stochez in size offset-ul pana la final, adica numarul de octeti din fisier
    fseek(src, 0, SEEK_SET); // mut cursorul inapoi la inceput ca sa pot face copierea

    copyChunk(src, dst, size);

    fclose(src);
    fclose(dst);
    return 0;
}