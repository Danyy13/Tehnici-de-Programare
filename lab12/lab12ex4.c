#include <stdio.h>

/*
    Aplicatia 12.4: Se dau urmatoarele 6 culori: alb, galben, rosu, verde, albastru si negru.
    Costruiti toate steagurile formate din 3 culori care indeplinesc urmatoarele conditii:
    - orice steag trebuie sa contina culoarea verde sau culoarea galben la mijloc.
    - culorile din fiecare steag trebuie sa fie distincte.

    nu se zice in ce ordine sa se afiseze steagurile si avem doar doua steaguri de ales pe
    pozitia din mijloc => putem genera modalitatile posibile de a permuta culorile de pe margine
    si sa le afisam o data cu galben la mijloc si o data cu verde la mijloc
*/

#define CULORI_STEAG 2 // doar doua culori merita stocate, cele de pe margine
#define CULORI_MARGINE 4

int steag[CULORI_STEAG]; // trei culori in steag

typedef enum { // excluden galben si verde
    ALB,
    ROSU,
    ALBASTRU,
    NEGRU,
    GALBEN,
    VERDE
}CULORI;

void scrieCuloare(int culoare) {
    switch(culoare) {
        case ALB:
            printf("alb ");
            break;
        case ROSU:
            printf("rosu ");
            break;
        case ALBASTRU:
            printf("albastru ");
            break;
        case NEGRU:
            printf("negru ");
            break;
        case GALBEN:
            printf("galben ");
            break;
        case VERDE:
            printf("verde ");
            break;
    }
}

void afisare(int culoareMijloc) {
    scrieCuloare(steag[0]);
    scrieCuloare(culoareMijloc);
    scrieCuloare(steag[1]);
    putchar('\n');
}

int valid(int k) {
    // avem doar culorile de margine de ales sa fie distincte, deci verificam doar cu k - 1
    if(steag[k] == steag[k - 1]) return 0;
    return 1;
}

int solutie(int k) {
    return k == 1;
}

void back(int k) {
    for(int i=0;i<CULORI_MARGINE;i++) { // doar 4 culori fara galben si verde
        steag[k] = i;
        if(valid(k))
            if(solutie(k)) {
                afisare(GALBEN);
                afisare(VERDE);
            }
            else
                back(k + 1);
    }
}

int main() {
    back(0);
    return  0;
}