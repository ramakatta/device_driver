#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include "shared_defs.h"

int main() {
    // Create shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Writer: shm_open failed");
        return EXIT_FAILURE;
    }

    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("Writer: ftruncate failed");
        close(shm_fd);
        return EXIT_FAILURE;
    }

    int *shared_data = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("Writer: mmap failed");
        close(shm_fd);
        return EXIT_FAILURE;
    }

    // Create or open named semaphore (initial value = 0)
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if (sem == SEM_FAILED) {
        perror("Writer: sem_open failed");
        munmap(shared_data, SHM_SIZE);
        close(shm_fd);
        return EXIT_FAILURE;
    }

    // Write data
    *shared_data = 1234;
    printf("Writer: Wrote %d to shared memory.\n", *shared_data);

    // Signal reader
    sem_post(sem);
    printf("Writer: Semaphore posted.\n");

    // Cleanup
    munmap(shared_data, SHM_SIZE);
    close(shm_fd);
    sem_close(sem);

    return EXIT_SUCCESS;
}

