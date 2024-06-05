#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define PORT 8080
#define BUFFER_SIZE 1024
 
int main() {
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(serv_addr);
 
    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
 
    // Server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
 
    // Get the bitstream from the user
    printf("Enter a bitstream: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove the trailing newline character
 
    sendto(client_fd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *) &serv_addr, addr_len);
 
    int n = recvfrom(client_fd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *) &serv_addr, &addr_len);
    buffer[n] = '\0';
 
    printf("Modified bitstream with even parity bit: %s\n", buffer);
 
    close(client_fd);
    return 0;
}
