#include <stdio.h>

/*
    Aplicatia 11.5: Sa se scrie o functie care primeste un numar intreg 0 <= n < 1000 si il
    afiseaza in forma literara. Sa se apeleze functia pentru numere introduse de la tastatura,
    pana la aparitia valorii 1000.
    Exemple: 108 - o suta opt; 520 - cinci sute douazeci; 16 - saisprezece
*/

#define ZERO "zero"
#define UNU "unu"
#define DOI "doi"
#define TREI "trei"
#define PATRU "patru"
#define CINCI "cinci"
#define SASE "sase"
#define SAPTE "sapte"
#define OPT "opt"
#define NOUA "noua"

void printDigit(unsigned int d) {
    switch(d) {
        case 0:
            printf(ZERO);
            break;
        case 1:
            printf(UNU);
            break;
        case 2:
            printf(DOI);
            break;
        case 3:
            printf(TREI);
            break;
        case 4:
            printf(PATRU);
            break;
        case 5:
            printf(CINCI);
            break;
        case 6:
            printf(SASE);
            break;
        case 7:
            printf(SAPTE);
            break;
        case 8:
            printf(OPT);
            break;
        case 9:
            printf(NOUA);
            break;
    }
}

void printNumber(unsigned int n) {
    if(n < 10) {
        printDigit(n);
        putchar('\n');
    } else if(n >= 10 && n <= 100) {
        printDigit(n/10);
        printf(" zeci");
        if(n%10 != 0) {
            printf(" si ");
            printDigit(n%10);
        }
        putchar('\n');
    } else {
        printDigit(n/100);
        printf(" sute ");
        if(n/10%10 != 0) {
            printDigit(n/10%10);
            printf(" zeci");
        }
        if(n%10 != 0) {
            printf(" si ");
            printDigit(n%10);
        }
        putchar('\n');
    }
}

int main() {
    unsigned int n = 0;
    do {
        scanf("%d", &n);
        if(n != 1000) printNumber(n);
    }while(n != 1000);
    return 0;
}