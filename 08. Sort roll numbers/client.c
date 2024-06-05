#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define PORT 8080
 
int main() {
    int client_fd;
    struct sockaddr_in serv_addr;
    int roll_numbers[6];
 
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
 
    printf("Enter roll numbers of six students: ");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &roll_numbers[i]);
    }
 
    send(client_fd, roll_numbers, sizeof(roll_numbers), 0);
    read(client_fd, roll_numbers, sizeof(roll_numbers));
 
    printf("Sorted roll numbers from server: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", roll_numbers[i]);
    }
    printf("\n");
 
    close(client_fd);
 
    return 0;
}
