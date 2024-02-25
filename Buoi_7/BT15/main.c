#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char *data = "Hello, FIFO!";
    
    // Tạo FIFO
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    // Mở FIFO để ghi
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Gửi dữ liệu
    ssize_t bytes_written = write(fd, data, strlen(data) + 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Data sent to receiver: %s\n", data);

    close(fd);

    return 0;
}
