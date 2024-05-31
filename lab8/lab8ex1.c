#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Exemplul 1: Sa se implementeze o propozitie folosind o lista dublu inlantuita. Fiecare element
    din lista este un cuvant de maxim 15 caractere sau un semn de punctuatie. Programul va avea un
    meniu cu urmatoarele optiuni: 1-propozitie noua (introducere cuvinte pana la punct, exclusiv);
    2-afisare; 3-sterge cuvant; 4-iesire:

    Aplicatia 8.1: Sa se modifice exemplul 1 astfel incat el sa numere de cte ori apare fiecare
    cuvant in propozitie. Pentru aceasta, cuvintele vor fi adaugate doar cu litere mici si fiecare
    cuvant va avea asociat un contor. Daca un cuvant nou nu exista in propozitie, el va fi adaugat.
    Altfel, daca el exista deja, doar se va incrementa contorul cuvantului existent. La afisare,
    pentru fiecare cuvant se va afisa si contorul sau.
*/

#define SIZE_WORD 16

typedef struct word {
    unsigned int counter;
    char string[SIZE_WORD];
    struct word *previous;
    struct word *next;
}WORD;

typedef struct lista {
    WORD *head;
    WORD *tail;
}LISTA;

WORD *newWord(const char *string) {
    WORD *word = (WORD *)malloc(sizeof(WORD));
    if(!word) {
        fprintf(stderr, "Eroare la alocare dinamica\n");
        exit(-1);
    }
    word->counter = 1; // daca cuvantul este generat inseamna ca apare o data
    strcpy(word->string, string);
    return word;
}

void addToList(LISTA *lista, WORD *word) {
    word->previous = lista->tail;
    if(!lista->tail) {
        lista->head = word;
    } else {
        lista->tail->next = word;
    }
    lista->tail = word;
    word->next = NULL;
}

void initList(LISTA *lista) {
    lista->head = lista->tail = NULL;
}

void printList(LISTA lista) {
    while(lista.head) {
        printf("%s %d\n", lista.head->string, lista.head->counter);
        lista.head = lista.head->next;
    }
}

void freeList(LISTA *lista) {
    WORD *p = NULL, *nextP = NULL;
    for(p=lista->head;p;p=nextP) {
        nextP = p->next;
        free(p);
    }
    initList(lista);
}

WORD *getWordAddress(LISTA lista, char *string) {
    for(WORD *p=lista.head;p!=NULL;p=p->next) {
        if(!strcmp(p->string, string)) return p;
    }
    return NULL;
}

void delete(LISTA *lista, WORD *word) {
    if(word->previous) {
        word->previous->next = word->next;
    } else {
        lista->head = word->next;
    }
    if(word->next) {
        word->next->previous = word->previous;
    } else {
        lista->tail = word->previous;
    }
    free(word);
}

enum options {
    PROPOZITIE_NOUA = 1,
    AFISARE,
    STERGERE,
    IESIRE
};

int main() {
    LISTA lista;
    enum options option = PROPOZITIE_NOUA;

    initList(&lista);
    // !!! citirea se termina citind string-ul "."

    do {
        printf("1 - propozitie noua\n");
        printf("2 - afisare\n");
        printf("3 - stergere cuvant\n");
        printf("4 - iesire\n");
        printf("optiune: "); scanf("%d", (int *)&option); // citeste un intreg care este valoarea enum-ului
        switch(option) {
            case PROPOZITIE_NOUA:
                freeList(&lista);
                while(1) {
                    char text[SIZE_WORD] = "";
                    scanf("%s", text);
                    if(!strcmp(text,".")) break;
                    WORD *word = newWord(text);
                    WORD *searchWord = getWordAddress(lista, word->string); 
                    if(searchWord) {
                        searchWord->counter++;
                        free(word); // cuvantul nu este adaugat in lista si daca nu este eliberat acum se va pierde adresa lui
                    }
                    else addToList(&lista, word);
                }
                break;
            case AFISARE:
                printList(lista);
                break;
            case STERGERE:
                char text[SIZE_WORD] = "";
                printf("cuvant de sters: "); scanf("%s", text);
                WORD *word = getWordAddress(lista, text); // cauta adresa cuvatului in lista
                if(word == NULL) {
                    printf("Nu s-a gasit cuvantul %s\n", text);
                    break;
                } else {
                    delete(&lista, word);
                }
                break;
            case IESIRE:
                break;
        }
    }while(option != 4);

    freeList(&lista);
    return 0;
}