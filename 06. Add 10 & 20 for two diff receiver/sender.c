#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;
 
int main() {
    key_t key;
    int msgid;
 
    // Generate unique key
    key = ftok("progfile", 65);
 
    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
 
    int number;
    printf("Enter a decimal number: ");
    scanf("%d", &number);
 
    // Send (number + 10)
    message.msg_type = 1;
    sprintf(message.msg_text, "%d", number + 10);
    msgsnd(msgid, &message, sizeof(message), 0);
 
    // Send (number + 20)
    message.msg_type = 2;
    sprintf(message.msg_text, "%d", number + 20);
    msgsnd(msgid, &message, sizeof(message), 0);
 
    printf("Messages sent to queue\n");
 
    return 0;
}
