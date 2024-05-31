#include <stdio.h>
#include <math.h>

/*
    Aplicatia 11.2: Se cere un n strict pozitiv si patru valori reale: ma, mb, m, d. ma si mb
    reprezinta masele a doua corpuri situate la distanta d unul de celalalt. m este masa unui
    corp care porneste din a si ajunge in b, din n pasi egali. Sa se calculeze in fiecare punct
    al traseului lui m forta F de atractie gravitationala care actioneaza asupra lui. F va fi cu
    semn: negativ inseamna ca m este atras catre ma, iar pozitiv catre mb. Formula atractiei
    gravitationale dintre doua corpuri m1 si m2, situate la distanta d unul de celalalt este:
    F=G*m1*m2/d2, unde G=6.674e-11. Masele sunt exprimate in kilograme, distantele in metri,
    iar fortele in newtoni.
*/

#define G 6.674e-11

double forceMax(double forceToA, double forceToB) {
    if(fabs(forceToA) >= fabs(forceToB)) return -forceToA; // daca e mai mare forta catre a trebuie afisata cu minus
    return forceToB;
}

int main() {
    unsigned int n = 0;
    double ma = 0, mb = 0, m = 0, d = 0;
    // double g = G;
    // printf("%e", g);

    scanf("%u", &n);
    scanf("%lf %lf %lf %lf", &ma, &mb, &m, &d);

    double step = d / n;
    double start = step;
    double end = d - step;
    for(float i=start;i<=end;i+=step) {
        double forceToA = G * m * ma / (i * i);
        double forceToB = G * m * mb / ((d - i) * (d - i));
        double maxForce = forceMax(forceToA, forceToB);
        // printf("%e %e\n", forceToA, forceToB);
        printf("%e\n", maxForce);
    }

    return 0;
}