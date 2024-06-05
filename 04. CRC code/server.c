#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<math.h>
#define MAXCLIENT 3
#define MAXSIZE 15
struct sockaddr_in server_address;
struct sockaddr_in client_address;
int temp;
void *serve(void *arg)
{
int client_sockfd,client_len;
char dat[MAXSIZE],tmp[MAXSIZE];
char val[MAXSIZE],div[MAXSIZE];
int i,j,end,start,dat_len=0,div_len=0;
int socket=*((int *)arg);
client_len=sizeof(client_address);
client_sockfd=accept(socket,(struct sockaddr
*)&client_address,&client_len);
read(client_sockfd,val,sizeof(val));
i=0;
while(val[i]!=10){
dat_len++;
i++;
}
strcpy(dat,val);
strcpy(tmp,val);
printf("Dataword Received!\n");
read(client_sockfd,val,sizeof(val));
i=0;
while(val[i]!=10){
div_len++;
i++;
}
strcpy(div,val);
i=dat_len;
dat_len=dat_len+div_len-1;
while(i<dat_len){
dat[i]='0';
i++;
}
dat[i]=10;
start=0;
end=div_len-1;
while(end<dat_len){
if(dat[start]=='1'){
for(i=start,j=0;i<=end,j<div_len;i++,j++){
if(dat[i]==div[j])
dat[i]='0';
else
dat[i]='1';
}
}
start++;
end++;
}
i=0;
end=div_len-1;
while(end){
tmp[dat_len-1-i]=dat[dat_len-1-i];
end--;
i++;
}
tmp[dat_len]=10;
printf("Codeword = %s",tmp);
write(client_sockfd,tmp,sizeof(tmp));
return NULL;
}
int main()
{
int server_sockfd,server_len;
pthread_t th[MAXCLIENT];
server_sockfd=socket(AF_INET,SOCK_STREAM,0);
server_address.sin_family=AF_INET;
server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
server_address.sin_port=9734;
server_len=sizeof(server_address);
bind(server_sockfd,(struct sockaddr *)&server_address,server_len);
listen(server_sockfd,MAXCLIENT);
while(1){
temp=0;
printf("Start..\n");
while(temp<MAXCLIENT){
int *pserver=malloc(sizeof(int));
*pserver=server_sockfd;
pthread_create(&th[temp],NULL,serve,(void *)pserver);
temp++;
}
temp=0;
while(temp<MAXCLIENT){
printf("Waiting...\n");
pthread_join(th[temp],NULL);
temp++;
}
}
return 0;
}
