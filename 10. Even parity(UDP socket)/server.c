#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define PORT 8080
#define BUFFER_SIZE 1024
 
int count_ones(char *bitstream) {
    int count = 0;
    while (*bitstream) {
        if (*bitstream == '1') count++;
        bitstream++;
    }
    return count;
}
 
int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);
 
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
 
    // Bind socket to an address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
 
    if (bind(server_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
 
    while (1) {
        int n = recvfrom(server_fd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';
 
        // Add parity bit
        int ones_count = count_ones(buffer);
        char parity_bit = (ones_count % 2 == 0) ? '0' : '1';
        buffer[n] = parity_bit;
        buffer[n+1] = '\0';
 
        sendto(server_fd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *) &client_addr, addr_len);
    }
 
    close(server_fd);
    return 0;
}
