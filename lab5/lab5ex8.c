#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Aplicatia 5.8: Sa se scrie un program care primeste in linia de comanda un nume de fisier si
    o serie de octeti, dati in hexazecimal. Programul va afisa toate pozitiile din fisier la care
    se afla secventa de octeti specificati.
    Exemplu: ./cautare 1.dat 01 aa b2 45 -> cauta in fisierul 1.dat secventa {01, aa, b2, 45} si
    afiseaza toate pozitiile la care o gaseste
*/

// functia nu merge pe cazuri de string in string
// ex.: seria cautata este 'ana', iar pentru input-ul 'anana' trebuie gasit de doua ori, insa functia gaseste o singura data deoarece nu am un while in while, parcurgerea este liniara
void cautaSerie(char *filePath, char *serie) {
    FILE *file = NULL;
    if((file = fopen(filePath, "rb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier\n");
        exit(-1);
    }

    unsigned int len = strlen(serie);
    unsigned int indexSerie = 0;
    char byte = 0; // citim cate un byte pe rand si verificam

    while(fread(&byte, sizeof(char), 1, file) == 1) {
        if(byte == serie[indexSerie]) { // daca se potriveste primul bit incrementez indexSerie si trec la urmatorul bit
            // printf("%02lx %d %02x %02x\n", ftell(file), indexSerie, byte, serie[indexSerie]);
            indexSerie++;
            if(indexSerie == len) { // in acest caz toti bitii din string sunt egali cu cei cititi
                printf("am gasit la %02lx\n", ftell(file)); // printez adresa 
                indexSerie = 0; // resetez pentru a gasi urmatoarea valoare
            }
        } else {
            indexSerie = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    // stocam seria de octeti intr-in sir de caractere alocat dinamic (va avea doar atati octeti cate argumente avem)
    char *serie = NULL;
    unsigned int size = argc - 2; // fara numele executabilului si numele fisierului
    if((serie = (char *)malloc((size + 1) * sizeof(char))) == NULL) {
        fprintf(stderr, "Eroare la alocare\n");
        exit(-2);
    }

    for(unsigned int i=2;i<argc;i++) {
        serie[i-2] = (char)strtol(argv[i], NULL, 16);
    }
    serie[argc - 2] = '\0';

    cautaSerie(argv[1], serie);

    return 0;
}