#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
 
#define SOCKET_PATH "/tmp/socket"
 
int main() {
    int client_fd;
    struct sockaddr_un server_address;
    int number;
    char result[10];
 
    // Create socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
 
    // Clear server address structure
    memset(&server_address, 0, sizeof(struct sockaddr_un));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, SOCKET_PATH, sizeof(server_address.sun_path) - 1);
 
    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
 
    // Get number from user
    printf("Enter a 4-digit decimal number: ");
    scanf("%d", &number);
 
    // Send number to server
    if (send(client_fd, &number, sizeof(number), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
 
    // Receive result from server
    if (recv(client_fd, result, sizeof(result), 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }
 
    printf("Result received from server: %s\n", result);
 
    // Close socket
    close(client_fd);
 
    return 0;
}
