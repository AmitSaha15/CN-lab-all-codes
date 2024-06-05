#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
 
#define SOCKET_PATH "unix_socket"
 
int count_ones(char *bitstream) {
    int count = 0;
    while (*bitstream) {
        if (*bitstream == '1') count++;
        bitstream++;
    }
    return count;
}
 
int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr;
    char bitstream[1024];
 
    // Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
 
    // Bind socket to an address
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    unlink(SOCKET_PATH);
 
    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
 
    // Listen for connections
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
 
    // Accept a connection
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
 
    // Read the bitstream from the client
    read(client_fd, bitstream, sizeof(bitstream));
    bitstream[strcspn(bitstream, "\n")] = '\0';
 
    // Add parity bit
    int ones_count = count_ones(bitstream);
    char parity_bit = (ones_count % 2 == 0) ? '1' : '0';
 
    strcat(bitstream, &parity_bit);
 
    // Send the modified bitstream back to the client
    write(client_fd, bitstream, strlen(bitstream) + 1);
 
    // Close the sockets
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);
 
    return 0;
}
