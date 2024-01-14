#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void signalHandler(int signum) {
    if (signum == SIGINT) {
        printf("Received SIGINT (Ctrl+C).\n");
        // Xử lý tín hiệu SIGINT
    } else if (signum == SIGUSR1) {
        printf("Received SIGUSR1.\n");
    
    } else if (signum == SIGUSR2) {
        printf("Received SIGUSR2.\n");
    }
    //exit(signum);
}

int main(int argc, char **argv)
{
    pid_t myPid = getpid();
    printf("My Pid: %d\n", myPid);
    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        perror("Cannot register signal handler for SIGINT");
        return 1;
    }

    if (signal(SIGUSR1, signalHandler) == SIG_ERR) {
        perror("Cannot register signal handler for SIGTERM");
        return 1;
    }

    if (signal(SIGUSR2, signalHandler) == SIG_ERR) {
        perror("Cannot register signal handler for SIGTERM");
        return 1;
    }

    while (1) {
        sleep(1);  // Giữ chương trình chạy để chờ tín hiệu
    }
    return 0;
}