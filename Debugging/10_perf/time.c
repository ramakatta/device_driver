#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#define BUFFER_SIZE 50

int main() {

    // Capture the current time. 
    struct timespec now;
    timespec_get( &now, TIME_UTC );

    // We transform the part expressed in seconds into a character string. 
    char strNow[BUFFER_SIZE];
    strftime(strNow, BUFFER_SIZE, "%D %T" , gmtime(&now.tv_sec));

    // Display the time with nanosecond precision 
    printf( "Current time: %s.%09ld UTC\n" , strNow, now.tv_nsec);

    return EXIT_SUCCESS;
}
