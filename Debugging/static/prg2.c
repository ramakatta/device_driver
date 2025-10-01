#include <stdio.h>

void greet(const char *msg, int unused_param) {  // unused_param → warning
    if (1) {  // condition always true
        printf("%s\n", msg);
    } else {  // redundant else
        printf("never happens\n");
    }
}

int main(void) {
    int x = -1;
    unsigned int y = 10;

    if (x < y) {  // signed/unsigned comparison
        printf("Comparison of signed and unsigned\n");
    }

    if (x);  // empty statement warning

    return 0;
}

