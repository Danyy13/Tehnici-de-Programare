#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
    Aplicatia 7.1: Sa se scrie o functie care primeste doua liste si returneaza 1 daca ele sunt
    identice, altfel 0.
*/

typedef struct element {
    int val;
    struct element *next;
}ELEMENT;

void eliberare(ELEMENT *lista) {
    ELEMENT *p = NULL;
    while(lista) {
        p = lista->next;
        free(lista);
        lista = p;
    }
}

void afisare(ELEMENT *lista) {
    ELEMENT *p = NULL;
    for(p=lista;p != NULL;p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}

ELEMENT *new(int val, ELEMENT *next) {
    ELEMENT *elem = NULL;
    if((elem = malloc(sizeof(ELEMENT))) == NULL) { // aloc memorie pentru elementul ce trebuie adaugat in lista
        printf("Eroare la alocare\n");
        exit(EXIT_FAILURE);
    }
    elem->val = val;
    elem->next = next;
    return elem;
}

ELEMENT *addStart(int val, ELEMENT *lista) {
    return new(val, lista);
}

void reverseList(ELEMENT **lista) {
    // este mai eficient sa adaugam nodurile la inceputul listei decat la final deoarece o
    // astfel de adaugare este O(ct) (fata de O(n) de fiecare data cand adaugam un nod)
    // adaugand nodurile la inceput da o lista in ordine inversa, deci trebuie inversata
    ELEMENT *previous = NULL, *current = NULL, *next = NULL;
    current = *lista;
    while(current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *lista = previous;
}

void readList(ELEMENT **lista, unsigned int size) { // presupunem ca se citesc exact size elemente 
    int number = 0;
    for(uint i=0;i<size;i++) {
        scanf("%d", &number);
        *lista = addStart(number, *lista);
    }
    reverseList(lista); // valorile se adauga la inceputul listei
}

uint8_t checkLists(ELEMENT *lista1, ELEMENT *lista2) {
    ELEMENT *p = lista1, *q = lista2;
    while(p != NULL && q != NULL) {
        if(p->val != q-> val) return 0;
        p = p->next;
        q = q->next;
    }
    if(p != NULL || q != NULL) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    ELEMENT *lista1 = NULL, *lista2 = NULL;
    unsigned int size1 = 0, size2 = 0;

    scanf("%d %d", &size1, &size2);

    // citire liste
    readList(&lista1, size1);
    readList(&lista2, size2);

    afisare(lista1);
    afisare(lista2);

    // verificam daca listele sunt aceleasi
    if(checkLists(lista1, lista2)) printf("Listele sunt la fel\n");
    else printf("Listele sunt diferite\n");

    eliberare(lista1);
    eliberare(lista2);

    return 0;
}