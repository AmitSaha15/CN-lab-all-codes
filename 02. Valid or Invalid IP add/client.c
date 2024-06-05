#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
// Driver code
int main() {
int sockfd;
char buffer[MAXLINE];
char ip[MAXLINE];
struct sockaddr_in servaddr;
// Creating socket file descriptor
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
// Filling server information
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
printf("Enter an IPv4 address: ");
scanf("%s", ip);
// Send IPv4 address to server
sendto(sockfd, (const char *)ip, strlen(ip), MSG_CONFIRM, (const struct sockaddr *)&servaddr,
sizeof(servaddr));
printf("IPv4 address sent.\n");
int n, len;
len = sizeof(servaddr);
n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr
*)&servaddr, &len);
buffer[n] = '\0';
// Print class name received from server
int dotcount=0;
for(int i=0;i<20;i++){
if(ip[i]=='.') 
dotcount++;
}
if (dotcount<3){
printf("NOT AN ADDRESS\n");
return 0;
}if(buffer[0]=='X')
printf("nOT Ip Address");
else
printf("Class of IP address %s is %c\n", ip, buffer[0]);
close(sockfd);
return 0;
}
