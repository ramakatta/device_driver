#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "shared_defs.h"

int main() {
    // Open shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("Reader: shm_open failed");
        return EXIT_FAILURE;
    }

    int *shared_data = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("Reader: mmap failed");
        close(shm_fd);
        return EXIT_FAILURE;
    }

    // Open named semaphore
    sem_t *sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("Reader: sem_open failed");
        munmap(shared_data, SHM_SIZE);
        close(shm_fd);
        return EXIT_FAILURE;
    }

    // Wait for writer
    sem_wait(sem);
    printf("Reader: Semaphore acquired.\n");

    // Read and print value
    printf("Reader: Read %d from shared memory.\n", *shared_data);

    // Cleanup
    munmap(shared_data, SHM_SIZE);
    close(shm_fd);
    sem_close(sem);

    // Optional cleanup (only run by reader to avoid race conditions)
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);

    return EXIT_SUCCESS;
}

