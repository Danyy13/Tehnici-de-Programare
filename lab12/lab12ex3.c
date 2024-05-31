#include <stdio.h>
#include <limits.h>

/*
    Aplicatia 12.3: Se citesc doua numere naturale n si k, k fiind mai mic decat numarul de cifre
    ale numarului n. Afisati cel mai mare numar care se poate forma eliminand k cifre din numarul
    n. Exemplu:
    n = 3452234
    k = 4
    numarul cautat este 534

    mod de rezolvare:
    1) se face un vector cu cifrele numarului n pentru a avea o multime din care alegem elementele
    2) se calculeaza diferenta dintre numarul de cifre ale lui n si k citit de la tastatura =>
    numarul de cifre dintr-o solutie
    3) apel functia back()
    4) daca s-a gasit o solutie se formeaza numarul de numarCifreSolutie cifre
    5) se verifica daca numarul este maxim 
*/

void vectorCifre(int n, int array[], int *size) {
    int aux = n, i = 1; // copiez numarul in aux si generez multimea cifrelor acestuia
    while(aux != 0) {
        array[i++] = aux % 10;
        aux /= 10;
    }
    *size = i - 1;
}

int buildNumberFromArray(int array[], int size) {
    int number = 0;
    for(int i=1;i<=size;i++) {
        number = number * 10 + array[i];
    }
    return number;
}

int solutie(int k, int numarCifreSolutie) {
    return k == numarCifreSolutie;
}

void back(int k, int start, int v[], int cifre[], int size, int numarCifreSolutie, int *vmax) {
    // parametrul start intra in functia back dupa o apelare cu valoarea i + 1, ceea ce inseamna ca nu mai verificam cifra de pe pozitia trecuta, deoarece toate cifrele sunt distincte
    for(int i=start;i<=size;i++) {
        v[k] = cifre[i];
        // if(valid(k)) // nu este nevoie de valid
            if(solutie(k, numarCifreSolutie)) {
                int number = buildNumberFromArray(v, k);
                if(*vmax < number) {
                    *vmax = number;
                }
            } else {
                back(k + 1, i + 1, v, cifre, size, numarCifreSolutie, vmax);
            }
    }
}

int main() {
    int n = 0, numarCifreEliminate = 0, v[20], cifre[20];
    scanf("%d %d", &n, &numarCifreEliminate);

    int size = 0;
    vectorCifre(n, cifre, &size);
    int numarCifreSolutie = size - numarCifreEliminate;
    int vmax = INT_MIN; // cea mai mica valoare din INT

    back(1, 1, v, cifre, size, numarCifreSolutie, &vmax);
    printf("%d\n", vmax);
    return 0;
}