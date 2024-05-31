#include <stdio.h>

#define GOLDEN_RATIO 1.6180339

/*
    Aplicatia 10.6: Se poate demonstra (v. Knuth) ca limita raportului a doi termeni invers
    consecutivi din sirul lui Fibbonaci este egala cu Phi (proportia de aur). 
    Implementati o functie (recursiva) care sa determine Phi cu o anumita precizie.
*/

double absoluteValue(double x) {
    if(x < 0) return -x;
    return x;
}

unsigned int fibo(unsigned int n) {
    // calculez fibonacci nerecursiv deoarece este mai rapid si ocupa mai putin spatiu
    if(n == 0 || n == 1) return 1;
    unsigned int c = 0, p = 1, a = 1;
    for(unsigned int i=2;i<n;i++) {
        c = a + p;
        a = p;
        p = c;
    }
    return c;
}

double phi(unsigned int n, double tolerance) {
    double golden = (double)fibo(n)/fibo(n-1);
    // printf("%lg %lg\n", golden - GOLDEN_RATIO, tolerance);
    if(absoluteValue(golden - GOLDEN_RATIO) < tolerance) return golden;
    return phi(n + 1, tolerance);
}

int main() {
    double tolerance = 0.000001;
    printf("%lf\n", phi(2, tolerance)); // incepem de la 1, adica de la a doua valoare posibila a lui n
    // in primul apel fibo(n) = fibo(1) = 1 si fibo(n - 1) = fibo(0) = 1
    return 0;
}