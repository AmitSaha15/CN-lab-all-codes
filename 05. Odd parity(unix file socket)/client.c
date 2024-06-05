#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
 
#define SOCKET_PATH "unix_socket"
 
int main() {
    int client_fd;
    struct sockaddr_un client_addr;
    char bitstream[1024];
 
    // Create socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
 
    // Connect to server
    memset(&client_addr, 0, sizeof(struct sockaddr_un));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, SOCKET_PATH, sizeof(client_addr.sun_path) - 1);
 
    if (connect(client_fd, (struct sockaddr *) &client_addr, sizeof(struct sockaddr_un)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
 
    // Get the bitstream from the user
    printf("Enter a bitstream: ");
    fgets(bitstream, sizeof(bitstream), stdin);
    bitstream[strcspn(bitstream, "\n")] = '\0'; // Remove the trailing newline character
 
    // Send the bitstream to the server
    write(client_fd, bitstream, strlen(bitstream) + 1);
 
    // Read the modified bitstream from the server
    read(client_fd, bitstream, sizeof(bitstream));
    printf("Modified bitstream with odd parity bit: %s\n", bitstream);
 
    // Close the socket
    close(client_fd);
 
    return 0;
}
