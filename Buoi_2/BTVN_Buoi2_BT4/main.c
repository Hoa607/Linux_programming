#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat sb;
    const char *file_path = argv[1];
    //File descriptor
    int fd; 
    //O_APPEND flag: Automatically positions the offset pointer to the file's end
    fd = open(file_path, O_RDWR | O_APPEND);
    if (fd == -1)
    {
        printf("Failed to open file!\n");
    }
    lseek(fd, 0, SEEK_SET);
    write(fd, argv[2], strlen(argv[2]));
    printf("Writen to the file: %s\n", argv[2]);
    close(fd);
    return 0;
}