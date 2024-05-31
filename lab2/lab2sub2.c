#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
    Subiectul 2.2 Se citesc mai multe cuvinte din linia de comanda. Cu ajutorul pointerilor la
    functii (un vector de pointeri la functii) sa se apeleze intr-o structura repetitiva
    urmatoarele functii. Sa se afiseze rezultatele pentru fiecare cuvant pe ecran si in fisierul
    text CUVINTE.TXT.
    a) Primeste parametru un sir de caractere si returneza lungimea sirului.
    b) Primeste parametru un sir de caractere si returneza numarul de vocale din text.
    c) Primeste parametru un sir de caractere si returneza numarul de litere mari din text.
    d) Primeste parametru un sir de caractere si returneza diferenta codurilor ASCII ale primului
    caracter si al ultimului caracter
*/

#define NUMBER 4
#define SIZE 50
#define OUTPUT_FILE "CUVINTE.TXT"

void printToScreen(char *word, int (*func[])(char *)) {
    printf("lungime: %d\n", func[0](word));
    printf("numar vocale: %d\n", func[1](word));
    printf("numar litere mari: %d\n", func[2](word));
    printf("diferenta in ASCII dintre prima si ultima litera: %d\n", func[3](word));
}

void printToFile(FILE *file, char *word, int (*func[])(char *)) {
    fprintf(file, "lungime: %d\n", func[0](word));
    fprintf(file, "numar vocale: %d\n", func[1](word));
    fprintf(file, "numar litere mari: %d\n", func[2](word));
    fprintf(file, "diferenta in ASCII dintre prima si ultima litera: %d\n", func[3](word));
}

int len(char *string) {
    int counter = -1;
    while(string[++counter] != '\0');
    return counter;
}

int numarVocale(char *string) {
    int stringLen = len(string);
    char vocale[] = "aeiouAEIOU";
    int counter = 0;
    for(uint8_t i=0;i<stringLen;i++) {
        if(strchr(vocale, string[i]) != NULL) counter++;
    }
    return counter;
}

int litereMari(char *string) {
    int counter = 0;
    while(string[0] != '\0') {
        if(string[0] >= 'A' && string[0] <= 'Z') counter++;
        string++;
    }
    return counter;
}

int lastMinusFirst(char *string) {
    int stringLen = len(string);
    return string[stringLen - 1] - string[0];
}

int main() {
    char word[SIZE];
    memset(word, 0, SIZE * sizeof(char));
    
    int (*func[4])(char *);
    func[0] = len;
    func[1] = numarVocale;
    func[2] = litereMari;
    func[3] = lastMinusFirst;

    FILE *output = NULL;
    output = fopen(OUTPUT_FILE, "w");

    while(scanf("%s", word) == 1) { // se citeste cate un cuvant
        printToScreen(word, func);
        fprintf(output, "%s\n", word);
        printToFile(output, word, func);
    }

    fclose(output);
    return 0;
}