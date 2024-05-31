#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 7.4: Pentru implementarea listei care memoreaza adresa ultimului element, sa se
    scrie o functie sterge(), care sterge din lista un element dat.
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
    ELEMENT *head = NULL, *tail = NULL;
    ELEMENT *p = NULL;

    int value = 0; // valoarea cautata
    printf("Valoarea nodului ce trebuie sters: ");
    scanf("%d", &value);
    printf("Lista:\n");
    readList(&head);

    afisare(head);

    for(p=head;p->next!=NULL;p=p->next);
    tail = p;
    // printf("tail: %d\n", tail->val);

    if(head->val == value) { // daca valaorea este prima
        ELEMENT *nod = head;
        head = head->next;
        free(nod);
    } else if(tail->val == value) { // daca valoarea este ultima
        for(p=head;p->next!=tail;p=p->next); // acum p->next este tail
        free(tail);
        tail = p;
        p->next = NULL;
    } else {
        for(p=head;p->next!=NULL;p=p->next) {
            if(p->next->val == value) {
                ELEMENT *nod = p->next;
                p->next = p->next->next;
                free(nod);
            }
        }
    }
    afisare(head);

    eliberare(head);

    return 0;
}