#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
    Subiect 8.2: Se citesc de la tastatura un numar n si o matrice patratica de dimensiune n
    continand litere din alfabet. Pe urma se citeste de la tastatura un cuvant. Verificati daca
    respectivul cuvant se poate construi parcurgand literele matricii pe verticala in sus sau in
    jos sau pe orizontala spre stanga sau spre dreapta. Afisati toate pozitiile de unde trebuie
    inceputa parcurgerea, precum si sensul de parcurgere necesar pentru a construi cuvantul.
    Spre exemplu, daca de la tastatura se introduce:
    
    5
    e r e m a
    h e r e b
    b m e r e
    b a m e r
    a e m r e
    mere

    pe ecran se va afisa:
    De la linia 0 coloana 3 spre stanga.
    De la linia 0 coloana 3 in jos.
    De la linia 2 coloana 1 spre dreapta.
    De la linia 3 coloana 2 in sus.
    Nu are importanta ordinea in care sunt afisate solutiile gasite. Daca nu exista solutie, se
    afiseaza "Nu exista solutie"

    1) verific daca numarul de litere din cuvantul dat depaseste marimea matricii
    2) poate fi implementat un vector de frecventa care imi spune daca toate literele din
    cuvantul cerut sunt prezente in matrice, altfel nu exista solutii
*/

// modific usor tipul de date cu care lucrez modificand tipul definit
// !! trebuie sa modific manual la string-ul din scanf daca modific tipul
typedef char TYPE; 
typedef uint8_t SIZE_TYPE;

void eliberare(SIZE_TYPE rows, TYPE **matrix) {
    for(SIZE_TYPE i=0;i<rows;i++) free(matrix[i]);
    free(matrix);
}

TYPE **allocMatrix(SIZE_TYPE rows, SIZE_TYPE cols) {
    TYPE **matrix = NULL;
    if((matrix = (TYPE **)malloc(rows * sizeof(TYPE *))) == NULL) {
        fprintf(stderr, "Eroare la alocare linii\n");
        exit(-10);
    }
    for(SIZE_TYPE i=0;i<rows;i++) {
        if((matrix[i] = (TYPE *)malloc(cols * sizeof(TYPE))) == NULL) {
            for(i--;i>=0;i--) free(matrix[i]);
            free(matrix);
            fprintf(stderr, "Eroare la alocare coloane\n");
            exit(-11);
        }
    }
    return matrix;
}

void afisare(SIZE_TYPE size, TYPE **matrix) {
    for(SIZE_TYPE i=0;i<size;i++) {
        for(SIZE_TYPE j=0;j<size;j++) {
            printf("%c ", matrix[i][j]);
        }
        putchar('\n');
    }
}

void readMatrix(SIZE_TYPE size, TYPE **matrix) {
    // functia generica
    for(SIZE_TYPE i=0;i<size;i++) {
        for(SIZE_TYPE j=0;j<size;j++) {
            if(scanf("%s[^ ]", &matrix[i][j]) != 1) { // [^ ] - ignora caracterul " " = space
                fprintf(stderr, "Eroare la citire\n");
                exit(-1);
            }
        }
    }

    // daca aveam literele fara spatii
    // for(SIZE_TYPE i=0;i<size;i++) {
    //     if(scanf("%s", matrix[i]) != 1) {
    //         fprintf(stderr, "Eroare la citire\n");
    //         exit(-1);
    //     }
    // }
}

uint8_t checkRight(SIZE_TYPE size, TYPE **litere, char *word, SIZE_TYPE i, SIZE_TYPE j, SIZE_TYPE wordLen) {
    SIZE_TYPE jWord = j;
    while(word[jWord - j + 1] != '\0') { // offset-ul intre jWord cu care verific cuvantul in matrice si i (pozitia de start a cuvantului) poate fi folosit ca sa accesez literelle cuvantului
        if(word[jWord - j] != litere[i][jWord]) 
            return 0;
        jWord++;
    }
    return 1;
}

uint8_t checkLeft(SIZE_TYPE size, TYPE **litere, char *word, SIZE_TYPE i, SIZE_TYPE j, SIZE_TYPE wordLen) {
    SIZE_TYPE jWord = j;
    while(word[j - jWord + 1] != '\0') { 
        if(word[j - jWord] != litere[i][jWord]) 
            return 0;
        jWord--;
    }
    return 1;
}

uint8_t checkUp(SIZE_TYPE size, TYPE **litere, char *word, SIZE_TYPE i, SIZE_TYPE j, SIZE_TYPE wordLen) {
    SIZE_TYPE iWord = i;
    while(word[iWord - i + 1] != '\0') { 
        if(word[iWord - i] != litere[iWord][j]) 
            return 0;
        iWord++;
    }
    return 1;
}

uint8_t checkDown(SIZE_TYPE size, TYPE **litere, char *word, SIZE_TYPE i, SIZE_TYPE j, SIZE_TYPE wordLen) {
    SIZE_TYPE iWord = i;
    while(word[i - iWord + 1] != '\0') { 
        if(word[i - iWord] != litere[iWord][j]) 
            return 0;
        iWord--;
    }
    return 1;
}

void findWord(SIZE_TYPE size, TYPE **litere, char *word) {
    SIZE_TYPE wordLen = strlen(word);
    char firstLetter = word[0];
    for(SIZE_TYPE i=0;i<size;i++) {
        for(SIZE_TYPE j=0;j<size;j++) {
            if(litere[i][j] == firstLetter) {
                // dreapta
                if(j + wordLen <= size)
                    if(checkRight(size, litere, word, i, j, wordLen))
                        printf("De la linia %d coloana %d spre dreapta\n", i, j);
                // stanga
                if(j - wordLen + 1 >= 0)
                    if(checkLeft(size, litere, word, i, j, wordLen))
                        printf("De la linia %d coloana %d spre stanga\n", i, j);
                // sus
                if(i + wordLen <= size)
                    if(checkUp(size, litere, word, i, j, wordLen))
                        printf("De la linia %d coloana %d in sus\n", i, j);
                // jos
                if(i - wordLen + 1 >= 0)
                    if(checkDown(size, litere, word, i, j, wordLen))
                        printf("De la linia %d coloana %d spre stanga\n", i, j);
            }
        }
    }
}

int main() {
    SIZE_TYPE n = 0;
    TYPE **litere = NULL;
    char cuvant[65];

    scanf("%hhu", &n);
    litere = allocMatrix(n, n); readMatrix(n, litere);
    scanf("%s", cuvant);

    // verific daca numarul de litere din cuvantul dat depaseste marimea matricii
    if(strlen(cuvant) > n) printf("Lungimea cuvantului este prea mare\nNu exista solutie\n");

    findWord(n, litere, cuvant);

    // afisare(n, litere);

    eliberare(n, litere);
    return 0;
}