#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_SIZE 100

/*
    Aplicatia 12.5: Se cere un 0 < n <= 100 si apoi n valori reale, fiecare reprezentand volumul
    unui obiect. In final se cere v, volumul unei cutii. Se cere sa se umple cutia cu unele dintre
    obiecte date, astfel incat volumul ei sa fie utilizat in mod optim.

    cautam maximul volumului care poate fi ocupat de obiecte (fiind in acelasi timp mai mic decat
    capacitatea maxima a cutiei) si afisam obiectele care formeaza acest maxim
*/

void afisare(float array[], uint8_t size) {
    printf("afisare: ");
    for(uint8_t i=0;i<=size;i++) {
        printf("%.2f ", array[i]);
    }
    putchar('\n');
}

void citire(uint8_t *n, float object[], float *volum) {
    scanf("%hhu", n);
    for(uint8_t i=0;i<*n;i++) {
        scanf("%f", &object[i]);
    }
    scanf("%f", volum);
}

uint8_t valid(int k, float v[], float sumaVolume, float volum) {
    if(sumaVolume > volum) return 0;
    for(uint8_t i=0;i<k - 1;i++) {
        if(v[i] == v[k - 1]) return 0;
    }
    return 1;
}

void copyArray(float source[], float dest[], uint8_t size) {
    for(uint8_t i=0;i<size;i++) {
        dest[i] = source[i];
    }
}

void back(int k, float sumaVolume, float *max, uint8_t *done, float object[], float v[], uint8_t n, float volum, float solution[], uint8_t *solutionSize) {
    if(!*done && sumaVolume <= *max) {
        for(uint8_t i=0;i<n;i++) {
            v[k] = object[i];
            // printf("%f\n", v[k]);
            if(valid(k, v, sumaVolume, volum)) {
                if(sumaVolume + object[i] == volum) { // solutie
                    afisare(v, k); // daca am gasit o forma in care volumul ocupat este maxim o afisam
                    *done = 1; // nu mai incercam sa gasim alte solutii deoarece am gasit-o pe cea optima
                } else if(sumaVolume > *max) { // daca am gasit alt maxim 
                    if(k > *solutionSize) {
                        *solutionSize = k;
                        float *temp = NULL;
                        if((temp = (float *)realloc(solution, *solutionSize * sizeof(float))) == NULL) {
                            fprintf(stderr, "Eroare la alocare dinamica\n");
                            free(solution);
                            exit(-1);
                        }
                        solution = temp;
                        copyArray(v, solution, *solutionSize);
                    }
                    *max = sumaVolume;
                }
                else
                    back(k + 1, sumaVolume + object[i], max, done, object, v, n, volum, solution, solutionSize);
            }
        }
    }
}

int main() {
    uint8_t n = 0, solutionSize = 0;
    float object[MAX_SIZE], v[MAX_SIZE];
    float *solution = NULL;
    float volum = 0;
    float max = 0;
    uint8_t done = 0; // variabila care semnaleaza daca s-a gasit o repartizare perfecta pentru obiecte
    // avem nevoie de done in main() pentru a vedea daca alocam vectorul de solutie pentru numarul maxim (mai mic decat volum), sau daca am umplut la fix cutia 

    citire(&n, object, &volum);
    back(0, 0, &max, &done, object, v, n, volum, solution, &solutionSize);

    if(!done) { // daca nu s-a gasit solutia optima trebuie sa afisam solutia maxima
        afisare(solution, solutionSize);
    }

    free(solution);
    return 0;
}