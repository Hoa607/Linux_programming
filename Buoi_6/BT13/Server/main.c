#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};
    
    // Tạo socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Gán địa chỉ và port cho socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind socket với địa chỉ đã chỉ định
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Waiting for connections...\n");
    
    // Chấp nhận kết nối từ client
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Đọc và gửi tin nhắn
    int bytes_read = read(client_fd, buffer, BUF_SIZE);
    buffer[bytes_read] = '\0';
    printf("Received: %s\n", buffer);
    send(client_fd, "Hello from server!", strlen("Hello from server!"), 0);
    
    close(client_fd);
    close(server_fd);
    return 0;
}
