#include <stdio.h>
#include <stdint.h>

/*
    Aplicatia 10.2: Calculati recursiv suma cifrelor unui numar natural.
*/

uint8_t sumaCifre(uint64_t number) {
    if(number == 0) return 0;
    else return number % 10 + sumaCifre(number/10);
}

int main() {
    uint64_t number = 0;
    scanf("%lu", &number);
    printf("%hhu\n", sumaCifre(number));
    return 0;
}

// uint32_t max
// 4294967295
// 999999999

// uint64_t max
// 18446744073709551615
// 9999999999999999999