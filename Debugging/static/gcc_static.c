#include <stdio.h>
#include <stdlib.h>

int risky(int x) {
    int y = 1000000;

    // -Wshadow: this 'x' shadows the parameter 'x'
    for (int x = 0; x < 3; x++) {
        printf("shadowed x = %d\n", x);
    }

    // -Wconversion: implicit narrowing conversion (double → int)
    double d = 3.9;
    int n = d;  // conversion loses fractional part

    // -Wstrict-overflow: possible signed overflow
    if ((x + y) > x) {
        printf("overflow-prone condition\n");
    }

    // -fanalyzer: use-after-free
    int *p = malloc(sizeof(int));
    *p = 42;
    free(p);
    return *p;  // analyzer will warn about use-after-free
}

int main(void) {
    int result = risky(5);
    printf("result = %d\n", result);
    return 0;
}

