#include <stdio.h>
#include <stdlib.h>

int main() {
    int number = 1000;
    for(int i=1;i<number;i++) {
        printf("%d ", i);
        if(i % 20 == 0) putchar('\n');
    }

    while(number--) {
        printf("%d ", number);
        if(number % 20 == 0) putchar('\n');
    }

    return 0;
}