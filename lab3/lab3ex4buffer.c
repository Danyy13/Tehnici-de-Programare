#include <stdio.h>
#include <string.h>

/*
    Aplicatia 3.4 Sa se implementeze cu ajutorul unei cozi un buffer care retine temporar
    informatiile primite de la diversi transmitatori (informatia este adaugata in coada) si le
    transmite mai apoi catre un receptor (informatia este eliminata din coada). Informatia primita
    in buffer are urmatoare structura: numar identificare transmitator (int), mesaj (sir de
    caractere de maxim 256 caractere).

    buffer folosind coada
*/

#define SIZE_MAX 100
#define CHAR_MAX 256

typedef struct {
    int id;
    char message[CHAR_MAX + 1];
}BUFFER;

int front = 0, rear = -1;
BUFFER buffer[SIZE_MAX]; 

void printQueue() {
    if(rear == -1 || front > rear) {
        fprintf(stderr, "Coada este goala\n");
    }
    for(int i=front;i<=rear;i++) {
        printf("%d %s", buffer[i].id, buffer[i].message);
    }
    putchar('\n');
}

void enqueue(BUFFER item) {
    if(rear == SIZE_MAX - 1) {
        fprintf(stderr, "Coada este plina\n");
        return;
    }
    buffer[++rear] = item;
}

BUFFER dequeue() {
    if(rear == -1 || front > rear) {
        fprintf(stderr, "Coada este goala\n");
        // creez un item BUFFER care sa aiba o valoare generica pentru a putea fi returnat in caz de eroare
        BUFFER item;
        item.id = 0;
        strcpy(item.message, "");
        return item;
    }
    return buffer[front++];
}

int main() {
    BUFFER item;
    char option[8] = ""; // add, pop, clear, end

    printf("Optiuni: add, pop, clear, display, end\n");

    while(1) {
        scanf("%s", option);
        getchar(); // citeste '\n'
        if(strcmp(option, "add") == 0) {
            // citim informatia
            scanf("%d", &item.id);
            fgets(item.message, CHAR_MAX + 1, stdin);
            enqueue(item);
        } else if(strcmp(option, "pop") == 0) {
            item = dequeue();
        } else if(strcmp(option, "clear") == 0) {
            for(int i=front;i<=rear;i++) {
                item = dequeue();
            }
        } else if(strcmp(option, "display") == 0) {
            printQueue();
        } else if(strcmp(option, "end") == 0) break;
        else printf("Optiunea nu exista\n");
    }
    return 0;
}