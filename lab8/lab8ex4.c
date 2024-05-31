#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Aplicatia 8.4: Sa se scrie un program care implementeaza o lista de categorii, fiecare
    categorie avand asociata o lista de produse. O categorie se defineste prin numele sau. Un
    produs se defineste prin nume si pret. Programul va prezenta utilizatorului un meniu cu
    urmatoarele optiuni: 1-adauga categorie; 2-adauga produs (prima oara cere o categorie si apoi
    un produs pe care il adauga la acea categorie); 3-afisare categorii (afiseaza doar numele
    tuturor categoriilor); 4-afisare produse (cere o categorie si afiseaza toate produsele din ea);
    5-iesire
*/

#define SIZE_WORD 16

typedef struct produs {
    struct produs *previous;
    struct produs *next;
    char numeProdus[SIZE_WORD];
    unsigned int pret;
}PRODUS;

typedef struct p_list {
    PRODUS *head;
    PRODUS *tail;
}P_LIST;

typedef struct categorie {
    struct categorie *previous;
    struct categorie *next;
    char numeCategorie[SIZE_WORD];
    P_LIST pList;
}CATEGORIE;

typedef struct c_list {
    CATEGORIE *head;
    CATEGORIE *tail;
}C_LIST;

enum options {
    ADAUGA_CATEGORIE = 1,
    ADAUGA_PRODUS,
    AFISARE_CATEGORIE,
    AFISARE_PRODUS,
    IESIRE
};

void freeList(C_LIST *cList) {
    CATEGORIE *p = cList->head;
    while(p) {
        cList->head = cList->head->next;
        free(p);
        p=cList->head;
    }
}

void categorie_print(C_LIST cList) {
    while(cList.head) {
        printf("%s ", cList.head->numeCategorie);
        cList.head = cList.head->next;
    }
    putchar('\n');
}

void produs_print(P_LIST pList) {
    while(pList.head) {
        printf("%s %d\n", pList.head->numeProdus, pList.head->pret);
        pList.head = pList.head->next;
    }
    putchar('\n');
}

CATEGORIE *categorie_noua(const char *string) {
    CATEGORIE *categorie = (CATEGORIE *)malloc(sizeof(CATEGORIE));
    if(!categorie) {
        fprintf(stderr, "Eroare la alocare dinamica\n");
        exit(-1);
    }
    strcpy(categorie->numeCategorie, string);
    return categorie;
}

PRODUS *produs_nou(const char *string, const unsigned int pret) {
    PRODUS *produs = (PRODUS *)malloc(sizeof(PRODUS));
    if(!produs) {
        fprintf(stderr, "Eroare la alocare dinamica\n");
        exit(-1);
    }
    strcpy(produs->numeProdus, string);
    produs->pret = pret;
    return produs;
}

void categorie_adauga(C_LIST *cList, CATEGORIE *categorie) {
    categorie->previous = cList->tail;
    if(!cList->tail) {
        cList->head = categorie;
    } else {
        cList->tail->next = categorie;
    }
    cList->tail = categorie;
    categorie->next = NULL;
}

void produs_adauga(P_LIST *pList, PRODUS *produs) {
    produs->previous = pList->tail;
    if(!pList->tail) {
        pList->head = produs;
    } else {
        pList->tail->next = produs;
    }
    pList->tail = produs;
    produs->next = NULL;
}

CATEGORIE *categorie_adresa(C_LIST cList, const char *string) {
    // returneaza adresa categoriei cu numele string daca aceasta se gaseste in lista cList
    for(CATEGORIE *p=cList.head;p!=NULL;p=p->next) {
        if(!strcmp(p->numeCategorie, string)) return p;
    }
    return NULL;
}

int main() {
    enum options option;
    C_LIST cList;
    CATEGORIE *categorie = NULL;

    do {
        printf("1 - Adauga categorie\n");
        printf("2 - Adauga produs\n");
        printf("3 - Afiseaza categorie\n");
        printf("4 - Afiseaza produs\n");
        printf("5 - Iesire\n");
        printf("optiune: "); scanf("%d", (int *)&option); // citeste un intreg care este valoarea enum-ului
        char textCategorie[SIZE_WORD];
        switch(option) {
            case ADAUGA_CATEGORIE:
                char text[SIZE_WORD] = "";
                scanf("%s", text);
                categorie = categorie_noua(text);
                categorie_adauga(&cList, categorie);
                break;
            case ADAUGA_PRODUS:
                // la adaugare produs se cere intai o categorie in care sa se adauge produsul
                printf("Nume categorie: "); scanf("%s", textCategorie);
                categorie = categorie_noua(textCategorie);
                categorie = categorie_adresa(cList, textCategorie);
                if(!categorie) printf("Nu exista categoria cautata\n");
                else {
                    char textProdus[SIZE_WORD] = ""; unsigned int pret = 0;
                    printf("nume produs: "); scanf("%s", textProdus);
                    printf("pret produs: "); scanf("%d", &pret);
                    PRODUS *produs = produs_nou(textProdus, pret);
                    produs_adauga(&categorie->pList, produs);
                }
                break;
            case AFISARE_CATEGORIE:
                categorie_print(cList);
                break;
            case AFISARE_PRODUS:
                printf("Nume categorie: "); scanf("%s", textCategorie);
                categorie = categorie_noua(textCategorie);
                categorie = categorie_adresa(cList, textCategorie);
                if(!categorie) printf("Nu exista categoria cautata\n");
                else produs_print(categorie->pList);
                break;
            case IESIRE:
                break;
            default:
                printf("Optiune nevalida\n");
        }
    }while(option != IESIRE);

    freeList(&cList);

    return 0;
}