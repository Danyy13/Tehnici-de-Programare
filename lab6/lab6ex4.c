#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

/*
    Aplicatia 6.4: Sa se scrie o functie crescator(int n, char tip, ...) care primeste un numar
    n de valori si returneaza 1 daca ele sunt in ordine strict crescatoare, altfel 0. Caracterul
    tip indica tipul valorilor si poate fi 'd' - int, 'f' - double.
    Exemplu: printf("%d",crescator(3, 'd', -1,7,9));
*/

uint8_t crescator(int n, char tip, ...) {
    va_list args;
    va_start(args, tip);

    switch(tip) { // switch pentru scalabilitate
        case 'd':
            int number = va_arg(args, int);
            while(--n) {
                int next = va_arg(args, int);
                if(next < number) return 0;
                number = next;
            }
            break;
        case 'f':
            double number1 = va_arg(args, double); // va_arg converteste oricum float in double by default
            while(--n) {
                double next = va_arg(args, double);
                if(next < number1) return 0;
                number1 = next;
            }
            break;
    }

    va_end(args);
    return 1;
}

int main() {
    printf("%d\n", crescator(4, 'f', -9.1, -2.3, 5.1, 9.2));
    return 0;
}