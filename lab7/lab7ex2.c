#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 7.2: Sa se scrie o functie care primeste o lista si returneaza lista respectiva
    cu elementele inversate. Functia va actiona doar asupra listei originare, fara a folosi
    vectori sau alocare de noi elemente.

    Voi citi de la tastatura pana cand nu mai sunt numere si le voi adauga la inceput pentru
    O(ct). Astfel, ca lista sa fie in ordinea citirii trebuie inversata. 
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
    ELEMENT *elem = (ELEMENT *)malloc(sizeof(ELEMENT));
    if(!elem) {
        printf("Eroare la alocare nod\n");
        exit(-1);
    }
    elem->val = val;
    elem->next = next;
    return elem;
}

ELEMENT *addStart(int val, ELEMENT *next) { // prepend = O(ct)
    return new(val, next);
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

void readList(ELEMENT **lista) { // presupunem ca se citesc exact size elemente 
    int number = 0;
    while(scanf("%d", &number) == 1) {
        *lista = addStart(number, *lista);
    }        
    reverseList(lista); // valorile se adauga la inceputul listei
}

int main() {
    ELEMENT *lista = NULL;

    readList(&lista);
    afisare(lista);

    eliberare(lista);

    return 0;
}