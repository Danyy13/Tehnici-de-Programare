#include <stdio.h>

/*
    Aplicatia 12.5: Se cere un 0 < n <= 100 si apoi n valori reale, fiecare reprezentand volumul
    unui obiect. In final se cere v, volumul unei cutii. Se cere sa se umple cutia cu unele dintre
    obiecte date, astfel incat volumul ei sa fie utilizat in mod optim.

    generam toate solutiile de obiecte care incap in cutie si retinem maximul pana la final sau
    pana cand cutia este umpluta la perfectie

    se va afisa care este volumul maxim ce poate fi ocupat
*/

#define SIZE 100

void citire(int *n, int array[], int *volum) {
    scanf("%d", n);
    for(int i=0;i<*n;i++) {
        scanf("%d", &array[i]);
    }
    scanf("%d", volum);
}

int valid(int k, int object[]) {
    // presupunem un array citit in care volumul obiectelor nu se schimba
    // daca s-ar schimba am putea implementa cu un vector de frecventa 
    for(int i=0;i<k;i++) {
        if(object[k] == object[i]) return 0;
    }
    return 1;
}

void back(int k, int volumOcupat, int volum, int n, int object[], int *vmax) {
    for(int i=0;i<n;i++) {
        if(volumOcupat + object[i] > volum) return; // valoarea e prea mare deci evit sa mai calculez mai departe
        if(valid(k, object) == 0) return; // valoarea se repeta
        
        volumOcupat += object[i];
        printf("volum ocupat: %d\n", volumOcupat);
        if(volumOcupat > *vmax && volumOcupat <= volum) {
            *vmax = volumOcupat;
        }
        if(volumOcupat < volum)
            back(k + 1, volumOcupat, volum, n, object, vmax);
    }
}

int main() {
    int n = 0, volum = 0; // n citit de la tastatura
    int object[SIZE];
    citire(&n, object, &volum);
    int vmax = 0;

    // printf("%d\n", volum);

    back(0, 0, volum, n, object, &vmax);
    printf("%d\n", vmax);
    return 0;
}