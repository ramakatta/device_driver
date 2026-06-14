#include <stdio.h>

int main(void)
{
    int n = 10;

    if (n % 2 == 0) {
        printf("Even number\n");
    } else {
        printf("Odd number\n");
    }

    for (int i = 0; i < 3; i++) {
        printf("%d\n", i);
    }

    return 0;
}
