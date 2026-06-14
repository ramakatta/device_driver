/* LICENSE: GPLv2 */
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

pid_t tracee_pid;
int status;
struct user_regs_struct regs;

long get_word(pid_t tracee_pid, void *addr) {
    long word;
    errno = 0;
    word = ptrace(PTRACE_PEEKTEXT, tracee_pid, addr, NULL);
    if (errno != 0) {
        perror("ptrace(PTRACE_PEEKTEXT)");
        ptrace(PTRACE_DETACH, tracee_pid, NULL, NULL);
        exit(1);
    }
    return word;
}

void set_word(pid_t tracee_pid, void *addr, long data) {
    errno = 0;
    if (ptrace(PTRACE_POKETEXT, tracee_pid, addr, data) == -1) {
        perror("ptrace(PTRACE_POKETEXT)");
        exit(1);
    }
}

int wait_and_dumpreg() {
    // wait for child/tracee to complete exec and stop in main
    waitpid(tracee_pid, &status, 0);

    if(!WIFSTOPPED(status)) {
        printf("Tracee error, did not stop");
        return(1);
    }

    if(ptrace(PTRACE_GETREGS, tracee_pid, NULL, &regs) == -1){
        printf("PTRACE_GETREGS Error..");
    } else {
        printf("RIP: 0x%llx RSP: 0x%llx \n",
               (unsigned long long)regs.rip,
               (unsigned long long)regs.rsp);
    }

    return(0);
}

int main(void){
    int rc = 0;
    long data;
    unsigned long addr;
    unsigned long txt;
    long original_data;

    tracee_pid = fork();
    if(tracee_pid == 0){
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("./tracee", "./tracee", NULL);
        perror("execl");
        _exit(1);
    }

    rc = wait_and_dumpreg();
    ptrace(PTRACE_CONT, tracee_pid, NULL, NULL);
    rc = wait_and_dumpreg();

    printf("Enter the memory address to read (in hexadecimal): ");
    if (scanf("%lx", &addr) != 1) {
        fprintf(stderr, "Invalid address format\n");
        ptrace(PTRACE_DETACH, tracee_pid, NULL, NULL);  // Detach from the target process
        return (1);
    }

    // Read data from the target process memory
    data = get_word(tracee_pid, (void *)addr);
    printf("Data at address 0x%lx: 0x%x\n", addr, data);

    data = 0x678910;
    printf("Write data 0x%lx at address 0x%lx\n", data, addr);
    set_word(tracee_pid, (void *)addr, data);

    data = get_word(tracee_pid, (void *)addr);
    printf("Read data back from address 0x%lx: 0x%x\n", addr, data);

    ptrace(PTRACE_CONT, tracee_pid, NULL, NULL);
    return (rc);
}
