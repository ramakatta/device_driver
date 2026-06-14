#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variable (discouraged by many coding standards)
int counter = 0;

// Function with poor practices
char *bad_copy(const char *src) {
    char buf[10];                   // fixed buffer size (risk of overflow)
    strcpy(buf, src);               // unsafe function (security issue)
    return buf;                     // returning pointer to local variable
}

// Function with shadowing, magic numbers, and bad types
int calc(int x) {
    int counter = 42;               // shadows global "counter"
    double d = 3.14;
    int y = d;                      // implicit narrowing conversion
    if ((x + 1000000) > x) {        // strict-overflow check
        printf("always true?\n");
    }
    return y;
}

// Memory leak and use-after-free
void leak_and_crash() {
    int *p = malloc(sizeof(int));
    *p = 10;
    free(p);
    *p = 20;                        // use-after-free
}

int main(void) {
    char *msg = bad_copy("This string is too long for the buffer!");
    printf("msg = %s\n", msg);

    int result = calc(5);
    printf("result = %d\n", result);

    leak_and_crash();

    return 0;
}

