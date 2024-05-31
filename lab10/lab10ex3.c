#include <stdio.h>
#include <stdint.h>

/*
    Aplicatia 10.3: Determinati recursiv cifra maxima a unui numar natural.
*/

uint8_t max(uint8_t a, uint8_t b) {
    if(a >= b) return a;
    return b;
}

uint8_t maxDigit(unsigned int n) {
    // if(n == 0) return 0;
    if(n < 10) return n % 10;
    return max(n % 10, maxDigit(n/10));
}

int main() {
    unsigned int n = 0;
    scanf("%u", &n);
    printf("%hhu\n", maxDigit(n));
    return 0;
}