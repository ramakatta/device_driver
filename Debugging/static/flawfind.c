#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vulnerable(const char *input) {
    char buf[8];

    // Insecure string handling
    strcpy(buf, input);       // buffer overflow risk
    strcat(buf, "X");         // unsafe strcat
    sprintf(buf, "%s", input); // unsafe sprintf
    gets(buf);                // dangerous (never safe)

    printf("Buffer = %s\n", buf);
}

int main(void) {
    char password[10];

    // Insecure input
    gets(password);           // deprecated & unsafe
    printf("Password = %s\n", password);

    vulnerable(password);
    return 0;
}

