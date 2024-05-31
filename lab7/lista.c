#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int val;
    struct element *next;
}ELEMENT;

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

int main(int argc, char *argv[]) {
    ELEMENT *lista = NULL;
    // ELEMENT *elem = NULL;

    unsigned int number = 0;
    do {
        if(scanf("%d", &number) == 1) {
            lista = addStart(number, lista);
        }
    }while(number != 0);

    reverseList(&lista);

    afisare(lista);

    return 0;
}