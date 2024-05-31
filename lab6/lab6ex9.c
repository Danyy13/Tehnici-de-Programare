#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

/*
    Aplicatia 6.9: Scrieti un program care calculeaza suma parametrilor primiti din linia de
    comanda (numere reale).
    Exemplu: executia fara parametri va afisa 0, iar executia cu parametrii 1.1 6.57 99.122 va
    afisa 106.792
*/

int main(int argc, char *argv[]) {
    double suma = 0;

    if(argc == 1) {
        // fprintf(stderr, "Nu exista argumente\n");
        printf("0\n"); // se cere ca executia fara parametri sa afiseze 0
        return 0;
    }

    // int intreg = 0;
    // float fractionar = 0;
    // for(uint8_t i = 1;i<argc;i++) { // argv[0] este numele programului, deci se incepe de la 1
    //     intreg = atoi(argv[i]); // iau partea intreaga a numarului
    //     while(argv[i][0] != '.') {
    //         argv[i]++;
    //     }
    //     argv[i]++; // trec peste cifre pana ajung la partea fractionara
    //     fractionar = atoi(argv[i]); // iau partea fractionara, insa acum este parte intreaga
    //     fractionar /= pow(10, strlen(argv[i])); // fac parte fractionara impartind la numarul de cifre
    //     // !gcc cu -lm din cauza lui pow() din math.h
    //     suma += (double)intreg + fractionar;        
    // }

    // am aflat ca exista atof
    for(uint8_t i=1;i<argc;i++) {
        suma += atof(argv[i]);
    }

    printf("%g\n", suma);

    return 0;
}

// cod Eric GitHub
// #include<stdio.h>
// 
// int main(int argc,char **argv)
// {
    // double suma=0;
    // for(int i=0;i<argc;i++)
    // {
        // float n=0;
        // sscanf(argv[i],"%g",&n);
        // suma+=n;
        // 
    // }
    // printf("Suma este:%g\n",suma);
    // return 0;
// }