#include <stdio.h>

void printChar() {
    char ch = 0;
    if((ch = getchar()) != EOF) { // conditia de oprire este cand nu mai avem un caracter de citit
        putchar(ch); // printeaza caracterele in ordine deoarece este inainte de apelul recursiv
        printChar();
        putchar(ch); // dupa apelul recursiv => printeaza caracterele in ordine inversa
    } else {
        putchar('\n'); // se pune '\n' dupa afisarea cuvantului in ordine
    }
}

int main() {
    printChar();
    putchar('\n');
    return 0;
}