#include <stdio.h>

/*
    Aplicatia 5.4: Sa se modifice exemplul 4, astfel incat la inceputul fisierului sa fie scris
    numarul de produse. Citirea va fi modificata pentru a folosi aceasta informatie, in loc de a
    se testa sfarsitul de fisier.
*/
void citire() {
FILE *fis;
unsigned short nNume;
if((fis=fopen("produse.dat","rb"))==NULL)return; // iesire din functie in caz cu nu exista baza de date
// deoarece in fisier nu exista numarul de elemente
// se foloseste o bucla infinita, care continua atata timp cat se mai pot citi noi elemente
for(;;){
// se incearca citirea unui nou produs, care incepe cu dimensiunea numelui
// daca fread nu reuseste sa citeasca elementul dimensiune, inseamna ca s-a ajuns la sfarsit de fisier
// in acest caz se inchide fisierul si se iese din functie
if(fread(&nNume,sizeof(unsigned short),1,fis)==0){
fclose(fis);
return;
}
char *pNume=(char*)malloc((nNume+1)*sizeof(char)); // alocare memorie pentru nume si terminator
if(pNume==NULL){
printf("memorie insuficienta");
fclose(fis);
eliberare();
exit(EXIT_FAILURE);
}
fread(pNume,sizeof(char),nNume,fis); // citire caractere nume
pNume[nNume]='\0'; // deoarece in fisier nu exista terminatorul de sir, acesta se adauga separat
produse[nProduse].nume=pNume;
fread(&produse[nProduse].pret,sizeof(float),1,fis); // citeste pretul produsului
nProduse++;
}
}
int main()
{
int optiune;
citire(); // citirea bazei de date la inceputul programului
do{
printf("optiune: ");
scanf("%d",&optiune);
getchar();
switch(optiune){
case 1:adaugare();break;
case 2:afisare();break;
case 3:scriere();eliberare();break;
default:printf("optiune invalida\n");
}
}while(optiune!=3);
return 0;
}
int main() {
    
    return 0;
}