/* LICENSE: GPLv2 */
#include <stdio.h>
#include <unistd.h>

int abc(int local_abc) {
    //lets  loop and get debugged by the tracer
    printf("Addeess of local_abc: %p\n", &local_abc);
    while(1) {
    }
    return(local_abc);
}

int main() {
    int local_main = 0x12345;
    int pid = getpid();
    printf("Tracee PID: %d\n", getpid());
    abc(local_main);
    return 0;
}

