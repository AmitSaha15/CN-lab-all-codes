#include <stdio.h>
#include <string.h>
 
char findClass(char str[]){
char arr[4];
int i = 0;
while (str[i] != '.'){
arr[i] = str[i];
i++;
}
i--;
int ip = 0, j = 1;
while (i >= 0){
ip = ip + (str[i] - '0') * j;
j = j * 10;
i--;
}
if (ip >= 1 && ip <= 126)
return 'A';
 
else if (ip >= 128 && ip <= 191)
return 'B';
 
else if (ip >= 192 && ip <= 223)
return 'C';
 
else if (ip >= 224 && ip <= 239)
return 'D';
 
else if(ip >= 240 && ip <= 255)
return 'E';
 
else
return 0;
}
 
void separate(char str[], char ipClass)
{
char network[12], host[12];
for (int k = 0; k < 12; k++)
network[k] = host[k] = '\0';
if (ipClass == 'A'){
int i = 0, j = 0;
while (str[j] != '.')
network[i++] = str[j++];
i = 0;
j++;
while (str[j] != '\0')
host[i++] = str[j++];
printf("Network ID: %s\n", network);
printf("Host ID: %s", host);
printf("Default subnet mask: 255.0.0.0\n");
printf("Broadcast ID:%s.255.255.255\n",network);
}
else if (ipClass == 'B'){
int i = 0, j = 0, dotCount = 0;
while (dotCount < 2){
network[i++] = str[j++];
if (str[j] == '.')
dotCount++;
}
i = 0;
j++;
while (str[j] != '\0')
host[i++] = str[j++];
printf("Network ID is %s\n", network);
printf("Host ID is %s", host);
printf("Default subnet mask is 255.255.0.0\n");
printf("Broadcast ID:%s.255.255\n",network);
}
else if (ipClass == 'C'){
int i = 0, j = 0, dotCount = 0;
while (dotCount < 3){
network[i++] = str[j++];
if (str[j] == '.')
dotCount++;
}
i = 0;
j++;
while (str[j] != '\0')
host[i++] = str[j++];
printf("Network ID is %s\n", network);
printf("Host ID is %s", host);
printf("Default subnet mask is 255.255.255.0\n");
printf("Broadcast ID:%s.255\n",network);
}
else if(ipClass=='D'||ipClass=='E')
printf("In this Class, IP address is not divided into Network and Host ID\n");
}
int main(){
char str[20];
printf("Please enter the IPV4 address: ");
fgets(str,20,stdin);
int dotcount=0;
for(int i=0;i<20;i++){
if(str[i]=='.') 
dotcount++;
}
if (dotcount<3){
printf("NOT AN ADDRESS\n");
return 0;
}
char ipClass = findClass(str);
if(ipClass!='\0')
printf("Given IP address belongs to Class %c\n", ipClass);
else
printf("ADDRESS DOESNOT EXIST");
separate(str, ipClass);
return 0;
}
