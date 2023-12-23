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
    fd = open(file_path, O_RDWR);
    if (fd == -1)
    {
        printf("Failed to open file!\n");
    }

    if (stat(file_path, &sb) == 0) 
    {
        printf("Thong tin cua file: %s\n", file_path);
        printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }
        printf("Kich thuoc: %ld bytes\n", sb.st_size);
        printf("Quyen truy cap: %o\n", sb.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        printf("Thoi gian chinh sua gan nhat: %s", ctime(&sb.st_mtime));
    } else 
    {
        printf("Failed to get an information from file\n");
    }
    return 0;
}