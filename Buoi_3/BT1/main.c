#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Tạo một tiến trình con

    if (pid < 0) {
        // Fork thất bại
        fprintf(stderr, "Không thể tạo tiến trình con\n");
        return 1;
    } else if (pid == 0) {
        // Tiến trình con
        printf("Tiến trình con - PID: %d, PPID: %d\n", getpid(), getppid());
    } else {
        // Tiến trình cha
        printf("Tiến trình cha - PID: %d, PPID: %d\n", getpid(), getppid());
    }

    return 0;
}
