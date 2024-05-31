#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nume[28];
    float pret;
}Produs;

Produs produse[1000];
int nProduse;

void adaugare() {
    Produs p;
    printf("nume: ");
    fgets(p.nume,28,stdin);
    p.nume[strcspn(p.nume,"\r\n")]='\0';
    printf("pret: ");
    scanf("%g",&p.pret);
    produse[nProduse]=p;
    nProduse++;
}

void afisare() {
    int i;
    for(i=0;i<nProduse;i++){
        printf("%s: %g\n",produse[i].nume,produse[i].pret);
    }
}

void scriere() {
    FILE *fis;
    if((fis=fopen("produse.dat","wb"))==NULL){
    printf("nu se poate deschide fisierul\n");
    exit(EXIT_FAILURE);
    }
    fwrite(&nProduse, sizeof(int), 1, fis);
    fwrite(produse,sizeof(Produs),nProduse,fis);
    fclose(fis);
}

int main() {
    int optiune;
    do{
        printf("optiune: ");
        scanf("%d",&optiune);
        getchar();
        switch(optiune) {
            case 1:adaugare();break;
            case 2:afisare();break;
            case 3:scriere();break;
            default:printf("optiune invalida\n");
        }
    }while(optiune!=3);
    
    return 0;
}
