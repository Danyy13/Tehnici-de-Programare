#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Aplicatia 8.3: Sa se scrie un program care primeste un nume de fisier in linia de comanda.
    Programul va citi toate liniile din fisier intr-o lista care este mereu sortata in ordine
    alfabetica. O linie poate avea maxim 1000 de caractere. Pentru ca lista sa fie mereu
    sortata alfabetic, adaugarea unei linii noi se face prin inserarea ei la pozitia corecta
    din lista, astfel incat sa se mentina proprietatea de sortare. In final se va afisa lista.
*/

#define INPUT_FILE "date.in"
#define SIZE 1001

typedef struct line {
    char string[SIZE];
    struct line *previous;
    struct line *next;
}LINE;

typedef struct lista {
    LINE *head;
    LINE *tail;
}LISTA;

LINE *newLine(const char *string) {
    LINE *line = (LINE *)malloc(sizeof(LINE));
    if(!line) {
        fprintf(stderr, "Eroare la alocare dinamica\n");
        exit(-2);
    }
    strcpy(line->string, string);
    return line;
}

void initList(LISTA *lista) {
    lista->head = lista->tail = NULL;
}

void afisare(LISTA lista) {
    while(lista.head) {
        printf("%s", lista.head->string);
        lista.head = lista.head->next;
    }
}

LINE *getLineAddress(LISTA *lista, char *string) {
    for(LINE *p=lista->head;p!=NULL;p=p->next) {
        if(!strcmp(p->string, string)) return p;
    }
    return NULL;
}

LINE *getLine(LISTA *lista, LINE *line) {
    // elimina nodul line din lista si returneaza adresa lui
    if(!line->previous) {
        lista->head = line->next;
        line->next = NULL;
    } else {
        line->previous->next = line->next;
    }
    if(!line->next) {
        lista->tail = line->previous;
        line->previous = NULL;
    } else {
        line->next->previous = line->previous;
    }
    return line;
}

void addInOrder(const char *pathname, LISTA *lista) {
    FILE *file = NULL;
    if((file = fopen(pathname, "r")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier\n");
        exit(-1);
    }
    
    char text[SIZE] = "";
    while(fgets(text, SIZE, file) != NULL) {
        LINE *line = newLine(text); // alocam o linie de text
        if(!lista->tail) { // cazul cand lista este goala
            lista->head = line; lista->tail = line;
            line->next = NULL; line->previous = NULL;
        } else {
            // trebuie sa gasim locul unde adaugam linia
            if(strcmp(line->string, lista->head->string) < 0) { // linia este mai mica decat capul listei => devine capul listei
                line->next = lista->head;
                lista->head->previous = line;
                line->previous = NULL;
                lista->head = line;
            } else if(strcmp(line->string, lista->tail->string) > 0) { // linia este mai mare decat finalul listei => devine ultimul element
                lista->tail->next = line;
                line->previous = lista->tail;
                line->next = NULL;
                lista->tail = line;
            } else {
                LINE *p = lista->head;
                while(strcmp(text, p->next->string) > 0 && p->next->next != NULL) {
                    p=p->next;
                }
                line->next = p->next;
                p->next->previous = line;
                p->next = line;
                line->previous = p;
            }
        }
    }
    
    fclose(file);
}

void freeList(LISTA *lista) {
    LINE *p = lista->head;
    while(p) {
        lista->head = lista->head->next;
        free(p);
        p=lista->head;
    }
}

int main(int argc, char *argv[]) {
    LISTA lista;

    initList(&lista);
    addInOrder(argv[1], &lista);
    afisare(lista);

    // LINE *line = getLineAddress(&lista, "hubbo\n");
    // printf("linia este la adresa: %p\n", line);
    // line = getLine(&lista, line); // scot linia din lista
    // afisare(lista);
    // dupa asta se poate face orice cu linia, cum ar fi sa fie adaugata in alta lista
    // free(line);

    freeList(&lista);
    return 0;
}