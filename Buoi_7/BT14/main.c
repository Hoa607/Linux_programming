#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_FILE "myfifo"

int main() {
    char buffer[BUFSIZ];
    int fd;

    // Tạo FIFO
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for writers...\n");

    // Mở FIFO để đọc
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Got a writer\n");

    // Đọc dữ liệu từ FIFO
    ssize_t numRead;
    while ((numRead = read(fd, buffer, BUFSIZ)) > 0) {
        write(STDOUT_FILENO, buffer, numRead);
    }
    
    close(fd);
    unlink(FIFO_FILE); // Xóa FIFO

    return 0;
}
