#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
 
#define SOCKET_PATH "/tmp/socket"
 
int main() {
    int server_fd, client_fd, server_len, client_len;
    struct sockaddr_un server_address, client_address;
    int number;
 
    // Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
 
    // Clear server address structure
    memset(&server_address, 0, sizeof(struct sockaddr_un));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, SOCKET_PATH, sizeof(server_address.sun_path) - 1);
 
    // Bind socket to address
    server_len = sizeof(struct sockaddr_un);
    if (bind(server_fd, (struct sockaddr *)&server_address, server_len) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
 
    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
 
    printf("Server is waiting for connections...\n");
 
    while (1) {
        // Accept connection
        client_len = sizeof(struct sockaddr_un);
        client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
        if (client_fd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
 
        // Receive number from client
        if (recv(client_fd, &number, sizeof(number), 0) == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
 
        // Check if the number is odd or even
        char* result = (number % 2 == 0) ? "Even" : "Odd";
 
        // Send result to client
        if (send(client_fd, result, strlen(result) + 1, 0) == -1) {
            perror("send");
            exit(EXIT_FAILURE);
        }
 
        printf("Result sent to client.\n");
 
        // Close client connection
        close(client_fd);
    }
 
    // Close server socket
    close(server_fd);
 
    // Remove socket file
    unlink(SOCKET_PATH);
 
    return 0;
}
