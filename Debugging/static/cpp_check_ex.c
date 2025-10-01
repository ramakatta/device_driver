#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variable (style issue)
int globalVar;

// Function never used (unused function)
void unused_function() {
    printf("I am never called\n");
}

// Dangerous function (security & bounds issues)
void unsafe_function(const char *input) {
    char buf[8];                     // too small buffer
    strcpy(buf, input);              // buffer overflow risk
    printf("Buffer = %s\n", buf);
}

int *bad_allocation() {
    int *p = malloc(sizeof(int));    // memory allocated
    *p = 42;
    return p;                        // not freed (leak warning)
}

int calc(int x) {
    int y;                           // uninitialized variable
    if (x > 10)
        return y;                    // use of uninitialized variable

    if (x == 5) { }
    else if (x == 5) {               // duplicate condition
        printf("Never executed\n");
    }

    if (x == x) {                    // always true condition
        printf("Always true\n");
    }

    int z = 0;
    if (z) {                         // always false condition
        printf("Never executed\n");
    }

    return x;
}

int main(void) {
    int *p = bad_allocation();
    free(p);
    free(p);                         // double free

    unsafe_function("This input is way too long and will overflow");

    int arr[3];
    arr[5] = 10;                     // out of bounds access

    int *nullPtr = NULL;
    *nullPtr = 123;                  // null pointer dereference

    int unusedVar = 99;              // unused variable

    calc(5);

    return 0;
}

