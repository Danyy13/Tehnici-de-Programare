#include <stdio.h>
#include <stdarg.h>

/*
    Aplicatia 6.5: Sa se implementeze o functie input(const char *fmt,...). In sirul fmt pot fi
    caractere obisnuite (orice in afara de %) si placeholdere (% urmat de o litera). Pentru
    fiecare placeholder posibil ( %d - int, %f -float, %c - char ), in lista de argumente
    variabile se va afla adresa unei variabile de tipul corespunzator. Functia afiseaza pe ecran
    caracterele obisnuite si citeste de la tastatura pentru placeholdere.
    Exemplu: input("n=%dch=%c", &n, &ch); // citeste o valoare de tip int in n si de tip char
    in ch
*/

void input(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while(*fmt != '\0') { // putem folosi fmt[0] sau *fmt
        if(*fmt == '%') { // verificam valoarea caracterului lui fmt si trecem mai departe ca sa verificam tipul de date ce trebuie citit (ex.: c - char, d - int)
            fmt++;
            // printf("fmt: %c\n", *fmt);
            switch(*fmt) {
                case 'd':
                    scanf("%d", va_arg(args, int *));
                    break;
                case 'f':
                    scanf("%g", va_arg(args, float *));
                    break;
                case 'c':
                    scanf(" %c", va_arg(args, char *)); // scanf(" %c", ) - cu spatiu inainte de %c inseamna ca va sari peste orice white space deja in buffer (cum ar fi '\n' care intra in buffer dupa ce dau Enter la citirile anterioare de int sau float)
                    break;
            }
        } else {
            printf("%c", *fmt);
        }
        fmt++;
    }

    va_end(args);
}

int main() {
    int n = 0;
    char ch = 0, c = 0;
    float f = 0.0;
    input("n = %dch = %cf = %fc = %c", &n, &ch, &f, &c);

    printf("n: %d\nch: %c\nf: %g\nc: %c\n", n, ch, f, c);
    return 0;
}