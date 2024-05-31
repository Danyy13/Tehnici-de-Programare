#include <stdio.h>
#include <stdlib.h>

/*
    Aplicatia 7.3: Sa se scrie o functie care primeste ca parametri doua liste si returneaza o
    lista care reprezinta reuniunea elementelor lor, fiecare element aparand o singura data,
    chiar daca in listele originale el este duplicat.
*/

#define FREQ_SIZE 100

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

void readList(ELEMENT **lista, unsigned int size) { // presupunem ca se citesc exact size elemente 
    int number = 0;
    for(uint i=0;i<size;i++) {
        scanf("%d", &number);
        *lista = addStart(number, *lista);
    }
    reverseList(lista); // valorile se adauga la inceputul listei
}

// void init(int array[], unsigned int size) {

// }

ELEMENT *deleteDuplicates(ELEMENT *lista) {
    ELEMENT *p = NULL, *q = NULL, *prevQ = NULL;
    // tin minte nodul de dinainte de Q in prevQ pentru a putea elimina nodul Q prin modificarea adresei lui prevQ la q->next, astfel "ignorand" nodul q
    for(p=lista;p->next!=NULL;p=p->next) {
        prevQ = p;
        for(q=p->next;q!=NULL;q=q->next) {
            if(p->val == q->val) { // stergem nodul din lista
                // printf("p value: %d\n", p->val);
                // printf("q value: %d\n", q->val);
                
                if(q->next == NULL) { // daca nodul de scos este la final
                    free(q);
                    prevQ->next = NULL;
                    return lista;
                } else {
                    ELEMENT *nod = q;
                    q = q->next;
                    free(nod); // eliberam memoria nodului pe care il stergem
                    prevQ->next = q;
                }
            } else {
                prevQ = q;
            }
        }
    }
    return lista;
}

ELEMENT *reuniune(ELEMENT *lista1, ELEMENT *lista2) {
    ELEMENT *newList = NULL;
    ELEMENT *p = NULL;
    newList = lista1; // newList are acum acces la toate elementele listei 1
    for(p=newList;p->next!=NULL;p=p->next); // parcurg lista nou formata pana ajung cu p pe ultimul element
    // printf("val: %d\n", p->val); // verific linia de cod de mai sus
    p->next = lista2; // adaug lista 2 la finalul listei noi, deci am acces la toate elementele (chiar si duplicate)
    // afisare(newList);
    return newList;
}

int main() {
    ELEMENT *lista1 = NULL, *lista2 = NULL;

    unsigned int size1 = 0, size2 = 0;
    scanf("%d %d", &size1, &size2);

    readList(&lista1, size1);
    readList(&lista2, size2);

    // printf("lista 1: "); afisare(lista1);
    // printf("lista 2: "); afisare(lista2);

    ELEMENT *newList = NULL;
    newList = reuniune(lista1, lista2);
    newList = deleteDuplicates(newList);

    afisare(newList);

    eliberare(newList); // de ajuns sa eliberez doar lista nou formata deoarece am acces la toate elementele alocate

    return 0;
}