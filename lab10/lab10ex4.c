#include <stdio.h>
#include <stdint.h>

uint64_t fibo(uint8_t n) {
    if(n == 0 || n == 1) return 1;
    return fibo(n - 1) + fibo(n - 2);
}

int main() {
    uint8_t n = 0;
    scanf("%hhu", &n);
    printf("%lu\n", fibo(n));
    return 0;
}