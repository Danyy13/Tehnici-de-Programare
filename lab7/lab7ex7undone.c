#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 7.7: Pentru implementarea listei care memoreaza ultimul element, sa se scrie o
    functie care primeste doua liste sortate si returneaza lista sortata care contine toate
    elementele lor. Pentru lista rezultata se va folosi doar operatia de adaugare la sfarsit de
    lista.
    Exemplu: {1, 2, 7, 8} si {2, 9} -> {1, 2, 2, 7, 8, 9}
*/

typedef struct elem {
    int val;
    struct elem *next;
}ELEMENT;

void eliberare(ELEMENT *lista) {
    ELEMENT *p = NULL;
    while(lista) {
        p = lista->next;
        free(lista);
        lista = p;
    }
}

ELEMENT *new(int val, ELEMENT *next) {
    ELEMENT *elem = NULL;
    if((elem = (ELEMENT *)malloc(sizeof(ELEMENT))) == NULL) {
        fprintf(stderr, "Eroare la alocarea dinamica\n");
        exit(-1);
    }
    elem->val = val;
    elem->next = next;
    return elem;
}

ELEMENT *addEnd(int val, ELEMENT *lista) {
    ELEMENT *node = new(val, NULL); // NULL pentru ca va fi adaugat la final
    if(!lista) return node;
    ELEMENT *p = NULL;
    for(p=lista;p->next!=NULL;p=p->next) {}
    // p este acum pe ultimul element
    p->next = node;
    return lista;
}

void afisare(ELEMENT *lista) {
    while(lista!=NULL) {
        printf("%d ", lista->val);
        lista=lista->next;
    }
    putchar('\n');
}

void reverseList(ELEMENT **lista) {
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

void readList(ELEMENT **lista, unsigned int size) { // citire cu adaugare la final
    int number = 0;
    for(uint i=0;i<size;i++) {
        scanf("%d", &number);
        *lista = addEnd(number, *lista);
    }
}

int main() {
    ELEMENT *lista1 = NULL, *lista2 = NULL;
    unsigned int size1 = 0, size2 = 0;
    scanf("%u %u", &size1, &size2);

    readList(&lista1, size1);
    afisare(lista1);

    readList(&lista2, size2);
    afisare(lista2);

    eliberare(lista1);
    eliberare(lista2);
    return 0;
}