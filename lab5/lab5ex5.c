#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 5.5: Sa se scrie un program similar cu hexdump, care primeste un nume de fisier in
    linia de comanda, citeste cate 16 octeti din el si ii afiseaza pe cate o linie. Fiecare linie
    incepe cu offsetul ei in fisier, afisat in hexazecimal pe 8 cifre cu 0 in fata, dupa care
    valorile hexa ale celor 16 octeti pe cate 2 cifre si in final caracterele. Daca codul unui
    caracter este in intervalul 32-255 se va afisa ca atare, altfel se va afisa un punct in locul
    sau. Daca ultima linie este incompleta, se va completa cu octeti de 0.

    nu e exact hexdump, scrie in Big Endian
*/

#define CHUNK 16

void displayHex(char *fileName) {
    FILE *file = NULL;
    if((file = fopen(fileName, "rb")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier\n");
        exit(-1);
    }

    fseek(file, 0, SEEK_END); // mut cursorul la final
    unsigned int size = ftell(file); // size are numarul de octeti din fisier
    size %= CHUNK; // in size retin cat ramane de citit la final, dupa while()
    fseek(file, 0, SEEK_SET); // mut cursorul inapoi la inceput

    unsigned int offset = 0;
    char buffer[CHUNK];
    while(fread(buffer, sizeof(char), CHUNK, file) == CHUNK) {
        // citesc din fisier si afisez la stdout
        // printf("%s\n", buffer); // verificare la ce citesc din fisierul binar - functioneaza bine daca sunt scrise caractere ASCII
        
        // 1. printez offset-ul in hex pe 8 biti
        printf("%08x ", offset);
        offset += CHUNK;

        // 2. afisez octetii in hex
        for(int i=0;i<CHUNK;i++) { 
            // scriem echivalentul fiecarui octet in hex 
            printf("%02x", buffer[i]); // scrie in Big Endian
            if((i & 1) == 1) printf(" ");
        }
    
        // 3. afisez caracterele printabile
        for(int i=0;i<CHUNK;i++) { 
            if(buffer[i] < 32 || buffer[i] > 255) putchar('.'); // pentru caractere neprintabile
            else putchar(buffer[i]);
        }
        putchar('\n');
    }

    // afisam si caracterele ramase, intr-un numar mai mic de CHUNK
    fread(buffer, sizeof(char), size, file);
    // 1
    offset += size;
    printf("%08x ", offset);

    // 2
    for(int i=0;i<size;i++) { 
        // scriem echivalentul fiecarui octet in hex 
        printf("%02x", buffer[i]); // scrie octetii in Big Endian
        if((i & 1) == 1) putchar(' ');
    }
    putchar(' ');
    
    // 3
    for(int i=0;i<size;i++) { 
        if(buffer[i] < 32 || buffer[i] > 255) putchar('.'); // pentru caractere neprintabile
        else putchar(buffer[i]);
    }
    putchar('\n');

    fclose(file);
}

int main(int argc, char *argv[]) {
    displayHex(argv[1]);
    return 0;
}