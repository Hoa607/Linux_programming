#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_address;
    char buffer[BUF_SIZE] = {0};

    // Tạo socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    
    // Chuyển đổi địa chỉ IPv4 và IPv6 từ chuỗi sang dạng nhị phân
    if(inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Kết nối tới server
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Gửi và nhận tin nhắn
    send(client_fd, "Hello from client!", strlen("Hello from client!"), 0);
    int bytes_read = read(client_fd, buffer, BUF_SIZE);
    buffer[bytes_read] = '\0';
    printf("Received: %s\n", buffer);

    close(client_fd);
    return 0;
}
