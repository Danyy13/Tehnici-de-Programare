#include <stdio.h>

#define SIZE_MAX 100
int front = 0, rear = -1;
int queue[SIZE_MAX];

void enqueue(int value) {
    if(rear == SIZE_MAX - 1) {
        fprintf(stderr, "Coada este plina\n");
        return;
    }
    queue[++rear] = value;
    // if(-1 == front) front = 0;
}

int dequeue() {
    if(rear == -1 || front > rear) {
        fprintf(stderr, "Coada este goala\n");
        return 0;
    }
    return queue[front++];
}

int main() {
    printf("%d\n", dequeue());
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
    return 0;
}