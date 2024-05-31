#include <stdio.h>
#include <stdlib.h>

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

ELEMENT *shiftLeft(ELEMENT *lista, unsigned int k) {
    ELEMENT *p = lista;
    for(unsigned int i=0;i<k-1;i++) {
        // printf("%d\n", i);
        // if(p->next == NULL) {
        //     fprintf(stderr, "k mai mare decat numarul elementelor din lista\n");
        //     exit(EXIT_FAILURE);
        // }
        p = p->next;
    }
    // printf("val: %d\n", p->val);
    ELEMENT *aux = p->next;
    p->next = NULL;
    p = aux;
    while(p->next != NULL) {
        p = p->next;
    }
    p->next = lista;
    return aux;
}

int main() {
    ELEMENT *lista = NULL;

    readList(&lista);
    lista = shiftLeft(lista, 3);
    afisare(lista);

    eliberare(lista);
    return 0;
}