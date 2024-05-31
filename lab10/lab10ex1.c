#include <stdio.h>

/*
    Aplicatia 10.1: Calculati recursiv cel mai mare divizor comun a doua numere.
    cmmdc(a, b) = 
    a, daca b = 0
    cmmdc(a, a%b), b > 0
*/

// void cmmdc(unsigned int a, unsigned int b) {
//     if(b == 0) printf("%d\n", a);
//     else cmmdc(b, a%b);
// }

unsigned int cmmdc(unsigned int a, unsigned int b) {
    if(b == 0) return a;
    else return cmmdc(b, a%b);
}

int main() {
    unsigned int a = 0, b = 0;
    scanf("%d %d", &a, &b);

    // cmmdc(a, b);

    printf("%d\n", cmmdc(a, b));

    return 0;
}