#include <stdio.h>
#include <stdarg.h>
#include <math.h>

/*
    Aplicatia 6.3: Sa se scrie o functie absN(int n,...) care primeste un numar n de adrese de
    tip float si seteaza la fiecare dintre aceste adrese valoarea absoluta de la acea locatie.
    Exemplu: absN(2,&x,&y); // echivalent cu x=fabs(x); y=fabs(y);
*/

void absN(int n, ...) {
    va_list adress;
    va_start(adress, n);

    while(n--) {
        float *x = va_arg(adress, float *);
        *x = fabs(*x);
        printf("%g\n", *x);
    }

    va_end(adress);
}

int main() {
    float x,y,z;
    x = 1.7;
    y = -10.2;
    z = -11.2;

    absN(3, &x, &y, &z);
    return 0;
}