#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/*
*   sigemptyset:
    Chức năng: Tạo một tập hợp rỗng, không có tín hiệu nào.
    Sử dụng: int sigemptyset(sigset_t *set);

*   sigfillset:
    Chức năng: Tạo một tập hợp chứa tất cả các tín hiệu.
    Sử dụng: int sigfillset(sigset_t *set);

*   sigaddset:
    Chức năng: Thêm một tín hiệu vào tập hợp.
    Sử dụng: int sigaddset(sigset_t *set, int signum);

*   sigdelset:
    Chức năng: Loại bỏ một tín hiệu khỏi tập hợp.
    Sử dụng: int sigdelset(sigset_t *set, int signum);

*   sigismember:
    Chức năng: Kiểm tra xem một tín hiệu có nằm trong tập hợp hay không.
    Sử dụng: int sigismember(const sigset_t *set, int signum);

*   sigprocmask:
    Chức năng: Đặt hoặc nhận signal mask của tiến trình.
    Sử dụng: int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
    how: SIG_BLOCK, SIG_UNBLOCK, hoặc SIG_SETMASK.
    set: Tập hợp mới của tín hiệu.
    oldset: Tập hợp cũ của tín hiệu (nếu cần).
    Ex: int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
    how: 
    @   Gom SIG_BLOCK (Them cac signals trong set vao tien trinh hien tai)   
    @   Gom SIG_UNBLOCK (Xoa cac signals trong set vao tien trinh hien tai.) 
    @   Gom SIG_SETMASK (Đặt signal mask của tiến trình thành set.)

    sigset_t set;

    // Tạo một tập hợp có tất cả các tín hiệu
    sigfillset(&set);

    // Chặn tín hiệu SIGINT
    sigdelset(&set, SIGINT);

    // Đặt signal mask của tiến trình
    if (sigprocmask(SIG_SETMASK, &set, NULL) == -1) {
        perror("sigprocmask");
        return 1;
    }
    Neu set == NULL thi oldset se nhan trang thai Mask hien tai
*/

void checkSigintStatus() {
    sigset_t currentMask;
    if (sigprocmask(SIG_BLOCK, NULL, &currentMask) == -1) {
        perror("Failed to get signal mask");
        return;
    }

    if (sigismember(&currentMask, SIGINT)) {
        printf("SIGINT is currently blocked.\n");
    } else {
        printf("SIGINT is not blocked.\n");
    }
}

void signalHandler(int signum) {
    printf("Received signal INT:%d\n", signum);
}


int main(int argc, char **argv)
{
    pid_t myPid = getpid();
    printf("My Pid: %d\n", myPid);

    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        perror("Cannot register signal handler for SIGINT");
        return 1;
    }

    checkSigintStatus();

    sigset_t blockMask;
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &blockMask, NULL) == -1) {
        perror("Failed to block SIGINT");
        return 1;
    }

    checkSigintStatus();

    if (sigprocmask(SIG_UNBLOCK, &blockMask, NULL) == -1) {
        perror("Failed to unblock SIGINT");
        return 1;
    }

    checkSigintStatus();

    while (1) {
        sleep(1);
    }

    return 0;
}