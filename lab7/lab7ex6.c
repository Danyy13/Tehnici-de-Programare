#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Aplicatia 7.6: Sa se scrie o functie care primeste ca parametri o lista (posibil vida) de
    elemente sortate si un element. Functia va insera in lista noul element, astfel incat lista
    sa ramana sortata. Folosind aceasta functie, sa se scrie o functie de sortare a unei liste,
    care primeste ca parametru o lista nesortata si returneaza una sortata.
    Programul nu va folosi niciun vector.

    Vom face intai algoritmul de sortare si apoi pe cel de adaugare
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
    ELEMENT *elem = malloc(sizeof(ELEMENT));
    if(!elem) {
        fprintf(stderr, "Eroare la alocare\n");
        exit(EXIT_FAILURE);
    }
    elem->val = val;
    elem->next = next;
    return elem;
}

ELEMENT *addStart(int val, ELEMENT *next) {
    return new(val, next);
}

void readList(ELEMENT **lista) { // putem citi si o lista nesortata pe care sa o sortam dupa
    int number = 0;
    while(scanf("%d", &number) == 1) {
        *lista = addStart(number, *lista);
    }        
    // in cazul acestei probleme nu folosim reverse deoarece vom modifica oricum lista pentru a fi in ordine crescatoare
    // reverseList(lista); - valorile se adauga la inceputul listei
}

void swap(ELEMENT *lista, ELEMENT *p, ELEMENT *q) {
    // functie care muta pozitia elementului q la dreapta lui p (deoarece valoarea lui q este mai mare) si face elementul q inceputul listei
    ELEMENT *aux = q->next;
    q->next = lista;
    p->next = aux;
}

void moveToStart(ELEMENT **lista, ELEMENT *p, ELEMENT **q) {
    // functie care muta pozitia elementului q la dreapta lui p (deoarece valoarea lui q este mai mare) si face elementul q inceputul listei
    p->next = (*q)->next;
    (*q)->next = *lista;
    *lista = *q;
}

void simplerMoveToStart(ELEMENT *lista, ELEMENT *p, ELEMENT *q) {
    p->next = q->next;
    q->next = lista;
}

ELEMENT *sortList(ELEMENT *lista) {
    ELEMENT *previous = NULL, *current = NULL;
    int sorted = 0;

    if(lista == NULL) return lista;

    while(!sorted) {
        int swapped = 0;

        for(previous=lista;previous->next!=NULL;previous=previous->next) {
            current = previous->next; // previous si current sunt cate doua elemente una dupa alta pe care le vom compara, previous este mereu elementul de dinintea lui current
            
            // debug
            // printf("%d %d\n", previous->val, current->val);
            // afisare(lista);

            // caz particular pentru ultimul nod
            if(current->next == NULL) {
                if(current->val < previous->val) {
                    current->next = lista; // mut pointer ultimul nod la inceput, inainte de lista
                    lista = current; // lista incepe acum de la current
                    previous->next = NULL; // nodul previous devine ultimul nod
                    swapped = 1;
                    break; // ies din loop pentru a nu se mai face verificarea previous->next == NULL care ar da Segmentation Fault
                }
            }

            // de ce while si nu if? -> nodul current se muta la inceput si astfel dupa previous apare alt nod care poate fi mai mic. de asta se muta current pe previous->next la finalul while-ului
            while(current->next != NULL && current->val < previous->val) {
                // alte metode de a face schimbarea
                // swap(lista, previous, current); // swap retuneaza elementul curent, adica cel cu valoare mai mica iar acesta este pus la inceputul listei
                // simplerMoveToStart(lista, previous, current); lista = current; // daca nu vreau sa transmit lista si current prin adresa linia aceasta functioneaza
                // 
                moveToStart(&lista, previous, &current);
                swapped = 1;
                current = previous->next;
            }

            //cu if
            // if(current->val < previous->val) {
            //     moveToStart(&lista, previous, &current);
            //     swapped = 1;
            // }
        }

        if(!swapped) sorted = 1; // daca nu s-au mai efectuat schimbari lista e sortata 
    }

    return lista;
}

ELEMENT *insert(ELEMENT *lista, ELEMENT *element) {
    // verificare pentru lista nula
    if(lista == NULL) {
        lista = element;
    } else if(lista->val >= element->val) { // verificare pentru primul element
        element->next = lista;
        lista = element;
    } else {
        ELEMENT *p = NULL;
        for(p=lista;p->next!=NULL;p=p->next) {
            if(p->next->val >= element->val) {
                // inseram nodul in aceasta pozitie
                element->next = p->next;
                p->next = element;
                return lista; // fara return aici intra in loop infinit si nu imi dau seama de ce, dar oricum este mai eficient cu return decat fara
            }
        }
        // cazul in care trebuie sa inseram la final
        // dupa for p ajunge pe ultimul element al listei, deci daca valoarea nodului ce trebuie inserat este mai mare decat valoarea lui p
        // inseram astfel nodul nou la final
        p->next = element;
        element->next = NULL;
    }

    return lista;
}

ELEMENT *sortListInsert(ELEMENT *lista) {
    // sortare prin selectarea unui element si mutarea lui la dreapta daca se gaseste un alt element mai mic decat el
    // sortare cum se cere in cerinta din laborator

    // scot primul nod din lista (capul listei) si il inserez in lista sortata
    // complexitate O(n^2) - pentru fiecare element din lista nesortata pot parcurge fiecare element din lista sortata
    ELEMENT *sortedList = NULL;
    while(lista) {
        ELEMENT *node = lista; // node devine capul listei
        lista=lista->next; // trec mai departe in coada listei
        node->next = NULL; // scot nodul (capul listei) din lista
        sortedList = insert(sortedList, node); // inserez capul listei in lista sortata
    }

    // duplicare de noduri
    // ELEMENT *sortedList = NULL;
    // for(ELEMENT *p=lista;p!=NULL;p=p->next) { // parcurg toate nodurile
        // ELEMENT *node = new(p->val, NULL); // creez un nou nod, deci aloc memorie pentru a duplica un nod => ineficient deoarece folosesc dubla memorie
        // sortedList = insert(sortedList, node); // inserez nodul creat in lista sortata
    // }
    // eliberare(lista); // eliberez memoria pentru lista nesortata

    return sortedList;
}

void sortTime(ELEMENT **lista) {
    clock_t startTime = clock();

    *lista = sortList(*lista); // schimba aici algoritmul

    clock_t endTime = clock();
    double timeSpent = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("timp: %lf\n", timeSpent);
}

int main() {
    ELEMENT *lista = NULL;

    readList(&lista);
    // afisare(lista);

    // cod sortare
    // lista = sortList(lista);
    // afisare(lista);

    // inserare element in lista
    // ELEMENT *input = new(66, NULL);
    // lista = insert(lista, input);

    // cod sortare prin inserare
    // lista = sortListInsert(lista);
    // afisare(lista);

    sortTime(&lista); // sorteaza lista si afiseaza timpul pentru sortare in secunde 
    
    // concluzii
    // !!!!!!! readList citeste lista din fisier in prin adaugare la inceput, deci lista care se sorteaza are defapt elementele in ordine inversa fata de cele din fisier
    // pare ca sortListInsert este mai rapid decat sortList pe cazuri generale
    // sortListInsert pare mai lent pe cazuri care tind sa fie mai mult descrescatoare sau pentru liste aproape sortate

    // caz favorabil sortList -> cand elementele de aranjat sunt deja in ordine crescatoare => doar o parcurgere de lista => O(n)
    // caz favorabil sortListInsert -> cand elementele de aranjat sunt in ordine descrescatoare => inserarea in noua lista se face la inceput unde se pun doar valori mai mici decat cea precedenta => O(n)

    eliberare(lista);
    return 0;
}