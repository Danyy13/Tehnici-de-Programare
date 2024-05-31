#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

int diff(int a, int b) {
    return a - b;
}

int power(int a, int b) {
    int aux = a;
    for(int i=0;i<b-1;i++) {
        a *= aux;
    }
    return a;
}

int main() {
    // pointer la printf
    // int (*printPointer)(const char* restrict, ...) = &printf;
    // (*printPointer)("Hello World!\n");

    // vector de pointeri de functii
    // int (*v[3])(int, int);
    // int (*sumPointer)(int, int) = &sum;
    // int (*diffPointer)(int, int) = &diff;
    // int (*powPointer)(int, int) = &power;

    // v[0] = *sumPointer;
    // v[1] = *diffPointer;
    // v[2] = *powPointer;

    // for(int i=0;i<3;i++) {
    //     printf("%d\n", (*v[i])(3,5));
    // }

    return 0;
}