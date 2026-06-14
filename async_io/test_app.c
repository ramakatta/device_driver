#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

/* Global flag marked 'volatile sig_atomic_t' for safe access across contexts */
static volatile sig_atomic_t got_signal = 0;

void mysighndlr(int signo)
{
    /* 
     * FIX 1 & 2: Set a flag and exit. Do NOT call printf() or fcntl() here.
     * We use write() because it is natively async-signal-safe.
     */
    const char msg[] = "SIGIO Received!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    
    got_signal = 1;
}

int main(int argc, char *argv[])
{
    int fd;
    int flgs;
    struct sigaction sa;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <device_file>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Unable to open the device");
        exit(EXIT_FAILURE);
    }

    printf("Device opened successfully. fd = %d\n", fd);

    /* Modern sigaction setup - preferred over legacy signal() method */
    sa.sa_handler = mysighndlr;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 
    if (sigaction(SIGIO, &sa, NULL) < 0) {
        perror("Failed to register signal handler");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /* Own the file descriptor to receive signals destined for this PID */
    if (fcntl(fd, F_SETOWN, getpid()) < 0) {
        perror("Failed to set owner");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /* Enable asynchronous notification flag */
    flgs = fcntl(fd, F_GETFL);
    if (fcntl(fd, F_SETFL, flgs | FASYNC) < 0) {
        perror("Failed to set FASYNC flag");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for asynchronous events from driver... Press Ctrl+C to exit.\n");

    /* 
     * FIX 3: Instead of blocking on stdin via scanf, pause() cleanly sleeps 
     * the process until any signal (like our SIGIO) wakes it up.
     */
    while (1) {
      //  pause(); 

        if (got_signal) {
            printf("Main context: Processing driver event trigger.\n");
            
            /* 
             * NOTE: Real production test apps usually call read(fd, buf, size) 
             * here to pull the data out and clear the driver's pending state.
             */
            
             got_signal = 0; // Reset flag
        }
    }

    close(fd);
    return 0;
}
