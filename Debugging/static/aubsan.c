#include <stdio.h>

int main(void) {
    int x = 2147483647;  // INT_MAX
    int y = x + 1;       // signed integer overflow

    int shift = 40;
    int z = 1 << shift;  // shift count too large for int

    int *p = NULL;
    *p = 123;            // null pointer dereference

    printf("%d %d\n", y, z);
    printf("Hello");
    return 0;
}

