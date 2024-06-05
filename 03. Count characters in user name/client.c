#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define PORT 8080
 
int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char name[1024] = {0};
    int name_length;
 
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character
 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
 
    // Send name to server
    send(sock, name, strlen(name), 0);
    printf("Name sent to server\n");
 
    // Receive length from server
    valread = read(sock, &name_length, sizeof(name_length));
    printf("Length of name received from server: %d\n", name_length);
 
    // Close socket
    close(sock);
    return 0;
}
