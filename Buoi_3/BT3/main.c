#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sigchld_handler(int signum) {
    pid_t pid;

    while ((pid = wait(NULL)) > 0) {
        printf("Tiến trình con với PID %d đã kết thúc.\n", pid);
    }
}

int main() {
    pid_t pid = fork(); // Tạo một tiến trình con
    //int rv, status;

    if (pid < 0) {
        // Fork thất bại
        fprintf(stderr, "Không thể tạo tiến trình con\n");
        return 1;
    } else if (pid == 0) {
        // Tiến trình con
        printf("Tiến trình con - PID: %d, PPID: %d\n", getpid(), getppid());
    } else {
        // Tiến trình cha
        signal(SIGCHLD, sigchld_handler);
        printf("Tiến trình cha - PID: %d\n", getpid());
        //rv = wait(&status);
        while(1);
    }

    return 0;
}