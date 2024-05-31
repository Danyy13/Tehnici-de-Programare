#include <stdio.h>

#define SIZE_MAX 100
int top = -1;
int stack[SIZE_MAX];

void push(int value) {
    if(top == SIZE_MAX - 1) {
        fprintf(stderr, "Stiva este plina\n");
        return;
    }
    stack[++top] = value;
}

int pop() {
    if(top == -1) {
        fprintf(stderr, "Stiva este goala\n");
        return 0;
    }
    return stack[top--];
}

int main() {
    push(10);
    push(20);
    push(30);
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    return 0;
}