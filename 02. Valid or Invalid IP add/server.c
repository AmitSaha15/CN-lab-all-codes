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
// Function to determine the class of IPv4 address
char getClass(char *ip) {
char class;
int firstOctet = atoi(strtok(ip, "."));
if (firstOctet >= 1 && firstOctet <= 126)
class = 'A';
else if (firstOctet >= 128 && firstOctet <= 191)
class = 'B';
else if (firstOctet >= 192 && firstOctet <= 223)
class = 'C';
else if (firstOctet >= 224 && firstOctet <= 239)
class = 'D';
else if (firstOctet >= 240 && firstOctet <= 255)
class = 'E';
else 
class = 'X';
return class;
}
// Driver code
int main() {
int sockfd;
char buffer[MAXLINE];
struct sockaddr_in servaddr, cliaddr;
int len, n;
// Creating socket file descriptor
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
perror("socket creation failed");
exit(EXIT_FAILURE);
}
memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));
// Filling server information
servaddr.sin_family = AF_INET; // IPv4
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);
// Bind the socket with the server address
if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
perror("bind failed");
exit(EXIT_FAILURE);
}
len = sizeof(cliaddr); // len is value/result
n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr,
&len);
buffer[n] = '\0';
// Determine class of IP address
char ip[MAXLINE];
strcpy(ip, buffer);
char ipClass = getClass(ip);
// Send class name back to client
sendto(sockfd, (const char *)&ipClass, sizeof(ipClass), MSG_CONFIRM, (const struct sockaddr
*)&cliaddr, len);
int dotcount=0;
for(int i=0;i<20;i++){
if(ip[i]=='.') 
dotcount++;
}
if (dotcount<3){
printf("NOT AN ADDRESS\n");
return 0;
}
if(ipClass == 'X')
printf("not add");
else
printf("Class of IP address %s is %c\n", ip, ipClass);
return 0;
}
