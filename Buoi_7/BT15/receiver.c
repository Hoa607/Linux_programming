#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char buffer[BUFSIZ];

    fd = open(FIFO_FILE, O_RDONLY);
    read(fd, buffer, BUFSIZ);
    close(fd);

    printf("Data received from sender: %s\n", buffer);

    return 0;
}
