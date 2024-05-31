#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Exemplul 1: Sa se implementeze o propozitie folosind o lista dublu inlantuita. Fiecare element
    din lista este un cuvant de maxim 15 caractere sau un semn de punctuatie. Programul va avea un
    meniu cu urmatoarele optiuni: 1-propozitie noua (introducere cuvinte pana la punct, exclusiv);
    2-afisare; 3-sterge cuvant; 4-iesire:

    Aplicatia 8.2: La exemplul 1 sa se adauge operatia de inserare a unui cuvant. Pentru aceasta
    se cere un cuvant de inserat si un cuvant succesor. Daca succesorul exista in propozitie,
    cuvantul de inserat va fi inserat inaintea sa. Daca succesorul nu exista in lista, cuvantul
    de inserat va fi adaugat la sfarsitul listei.
*/

#define SIZE_WORD 16

typedef struct word {
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
        printf("%s ", lista.head->string);
        lista.head = lista.head->next;
    }
    putchar('.'); 
    putchar('\n');
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

void addBeforeNode(LISTA *lista, WORD *nodeToAdd, WORD *succesor) {
    if(lista) {
        if(succesor == NULL) addToList(lista, nodeToAdd); // daca nu s-a gasit un succesor adaugam nodul la final
        else {
            if(!succesor->previous) { // adaugam la inceput
                succesor->previous = nodeToAdd;
                nodeToAdd->next = succesor;
                lista->head = nodeToAdd;
            } else {
                nodeToAdd->previous = succesor->previous;
                succesor->previous->next = nodeToAdd;
                nodeToAdd->next = succesor;
                succesor->previous = nodeToAdd;
            }
        }
    }
}

enum options {
    PROPOZITIE_NOUA = 1,
    AFISARE,
    STERGERE,
    ADAUGARE,
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
        printf("4 - adaugare\n");
        printf("5 - iesire\n");
        printf("optiune: "); scanf("%d", (int *)&option); // citeste un intreg care este valoarea enum-ului
        switch(option) {
            case PROPOZITIE_NOUA:
                freeList(&lista);
                while(1) {
                    char text[SIZE_WORD] = "";
                    scanf("%s", text);
                    if(!strcmp(text,".")) break;
                    WORD *word = newWord(text);
                    addToList(&lista, word);
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
            case ADAUGARE:
                char insertionText[SIZE_WORD] = "", succesorText[SIZE_WORD] = "";
                printf("Cuvant de inserat: "); scanf("%s", insertionText);
                printf("Cuvant succesor: "); scanf("%s", succesorText);
                // functia adauga insertion inainte de succesor daca succesor exista in propozitie, altfel adauga insertion la final
                WORD *insertion = newWord(insertionText);
                WORD *succesor = getWordAddress(lista, succesorText);
                addBeforeNode(&lista, insertion, succesor);
                break;
            case IESIRE:
                break;
            default:
                printf("Optiune invalida\n");
        }
    }while(option != IESIRE);

    freeList(&lista);
    return 0;
}