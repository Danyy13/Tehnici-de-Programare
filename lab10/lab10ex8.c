#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/*
    Aplicatia 10.8: Sa se implementeze cu o functie recursiva cautarea binara pe un vector ordonat
    (Binary Search - bsearch). Functia trebuie sa returneze daca numarul cautat exista sau nu in
    vector. Principiul dupa care functioneaza bsearch este ca vectorul se imparte la fiecare pas
    in 2 vectori de dimensiuni egale (sau aproximativ egale) si continua cautarea doar in unul
    dintre ei (apeleaza recursiv functia de cautare doar pe jumatate din vectorul initial), cel
    din partea stanga sau cel din partea dreapta, in functie de valoarea numarului cautat. 

    // citeste un vector ordonat crescator dintr-un fisier dat in linia de comanda 
*/

#define SIZE 1000

void printArray(int array[], unsigned int size) {
    for(unsigned int i=0;i<size;i++) {
        printf("%d ", array[i]);
    }
    putchar('\n');
}

void readArrayFromFile(char *pathname, int array[], unsigned int *size) {
    FILE *inputFile = NULL;
    if((inputFile = fopen(pathname, "r")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier\n");
        exit(EXIT_FAILURE);
    }

    unsigned int i = 0;
    while(fscanf(inputFile, "%d", &array[i]) == 1 && i < *size) {
        i++;
    }
    *size = i;

    fclose(inputFile);
}

uint8_t search(int array[], int value, unsigned int start, unsigned int end) {
    if(start == end) {
        if(value == array[start]) return 1;
        else return 0;
    }
    
    unsigned int mid = start + (end - start)/2;
    if(value < array[mid]) return search(array, value, start, mid - 1);
    else if(value > array[mid]) return search(array, value, mid + 1, end);
    else return 1;
}

int main(int argc, char *argv[]) {
    int array[SIZE];
    unsigned int size = SIZE;
    readArrayFromFile(argv[1], array, &size);
    printArray(array, size);

    int value = 0;
    printf("Valoarea cautata: ");
    scanf("%d", &value);

    if(search(array, value, 0, size - 1)) printf("am gasit valoarea\n");
    else printf("n-am gasit valoarea\n");

    return 0;
}