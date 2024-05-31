#include <stdio.h>

#define EULER_NUMBER 2.71828

/*
    Aplicatia 10.7: Serii de puteri. Calculati, cu o precizie data, valoarea lui ex dupa
    dezvoltarea in serie Taylor: e^x = 1 + x^1/1! + x^2/2! + x^3/3! + ...
    
    Calculati suma pana cand termenul curent devine mai mic decat o valoare data (de ex. 10-6).
    Pentru a evita recalcularea lui n! transmiteti ca parametru si termenul curent, si calculati-l
    pe urmatorul dupa relatia: x^n/n! = x^(n-1)/(n-1)! * x/n.
*/

double absoluteValue(double x) {
    if(x < 0) return -x;
    return x;
}

double power(double number, int times) {
    double aux = 1; // elementul neutru la inmultire
    if(times == 0) return 1;
    if(times < 0) {
        number = 1 / number;
        times = -times; // times devine pozitiv
    }
    while(times--) {
        aux *= number;
    }
    return aux;
}

double eulerPower(int x, int xPower, unsigned int n, double factorial, double previous, double target, double precizie) {
    int powX = xPower * x; // inmultesc la fiecare pas pe x cu el insusi pentru a retine puterea
    unsigned int fact = factorial * n; // retin factorialul la fiecare pas
    double current = previous + (double)powX/fact;
    // printf("%lf\n", current);
    if(absoluteValue(current - target) < precizie) return current;
    return eulerPower(x, powX, n + 1, fact, current, target, precizie);
}

int main() {
    int x = 0;
    scanf("%d", &x); // puterea la care se ridica e ~= 2.7
    double precizie = 0.001;
    double target = power(EULER_NUMBER, x);
    printf("%lg\n", eulerPower(x, 1, 1, 1, 1.0, target, precizie)); // suma incepe de la 1 (1 + ...)
    return 0;
}