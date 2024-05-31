#include <stdio.h>

/*
    Aplicatia 12.6: De-a lungul unei sosele trebuie amplasate una langa alta urmatoarele entitati:
    case, blocuri, gradini, ateliere. O entitate se poate invecina doar cu una de acelasi tip (ex:
    casa cu casa) sau conform urmatoarelor reguli (orice relatie o implica si pe cea inversa): un
    bloc poate avea ca vecini case; o casa sau un atelier poate avea ca vecini gradini. Se cer de
    la tastatura numerele c, b, g, a care reprezinta respectiv numarul de case, blocuri, gradini
    si ateliere. Sa se determine toate variantele in care acestea pot fi aranjate.
*/

#define ELEM_SIZE 4
#define MAX_SIZE 100

typedef enum {
    CASA,
    BLOC,
    GRADINA,
    ATELIER
}ENTITATE;

void scrieElemente(int element) {
    switch(element) {
        case CASA:
            printf("casa ");
            break;
        case BLOC:
            printf("bloc ");
            break;
        case GRADINA:
            printf("gradina ");
            break;
        case ATELIER:
            printf("atelier ");
            break;
    }
}

void genereazaMultime(int elem[], int set[], int *size) {
    int index = 0;
    int aux[ELEM_SIZE] = {elem[0], elem[1], elem[2], elem[3]};
    for(int i=0;i<ELEM_SIZE;i++) {
        while(aux[i]--) {
            set[index++] = i; // ex.: Daca apare CASA de 4 ori o sa o pun in vector una dupa alta de atatea ori
        }
    }
    *size = index;
}

void afisare(int array[], int size) {
    for(int i=0;i<size;i++) {
        // printf("%d ", array[i]);
        scrieElemente(array[i]);
    }
    putchar('\n');
}

int valid(int v[], int k) {
    if(k == 0) {
        return 1;
    } else {
        if(v[k - 1] == v[k]) return 1; // O entitate se poate invecina doar cu una de acelasi tip (ex: casa cu casa)
        if(v[k] == CASA && (v[k - 1] == BLOC || v[k - 1] == ATELIER)) return 1;
        if(v[k] == BLOC && v[k - 1] == CASA) return 1;
        if(v[k] == ATELIER && v[k - 1] == CASA) return 1;
        if(v[k] == GRADINA && v[k - 1] == ATELIER) return 1;
    }
    return 0;
}

int solutie(int k, int size) {
    return k == size - 1;
}

void back(int k, int v[], int set[], int size, int elem[]) {
    if(solutie(k, size)) {
        afisare(v, size);
        return;
    }
    
    for(int i=0;i<size;i++) {
        if(elem[set[i]]) {
            v[k] = set[i];
            // printf("%d %d\n", set[i], elem[set[i]]);
            if(valid(v, k)) {
                    elem[set[i]]--;
                    back(k + 1, v, set, size, elem);
                    elem[set[i]]++;
            }
        }
    }
}

int main() {
    // unsigned int casa = 0, bloc = 0, gradina = 0, atelier = 0;
    // scanf("%u %u %u %u", &casa, &bloc, &gradina, &atelier);

    int elem[4];
    scanf("%d %d %d %d", &elem[CASA], &elem[BLOC], &elem[GRADINA], &elem[ATELIER]);

    int size = 0;
    int set[MAX_SIZE];
    int v[MAX_SIZE];
    genereazaMultime(elem, set, &size);
    afisare(set, size);

    back(0, v, set, size, elem);

    return 0;
}