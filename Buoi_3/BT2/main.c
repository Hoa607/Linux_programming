#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Tạo một tiến trình con
    int rv, status;

    if (pid < 0) {
        // Fork thất bại
        fprintf(stderr, "Không thể tạo tiến trình con\n");
        return 1;
    } else if (pid == 0) {
        // Tiến trình con
        printf("Tiến trình con - PID: %d, PPID: %d\n", getpid(), getppid());
        sleep(5);
        exit();
    } else {
        // Tiến trình cha
        printf("Tiến trình cha - PID: %d\n", getpid());
        //rv = wait(&status);
        rv = waitpid(pid, &status, 0);
            if (rv == -1) {
                printf("wait() unsuccessful\n");
            }

            printf("\nIm the parent process, PID child process: %d\n", rv);
    }

    return 0;
}