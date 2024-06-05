#include <stdio.h>
#include <stdlib.h>
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
 
    // Get the message queue ID
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
 
    // Read message type 2
    msgrcv(msgid, &message, sizeof(message), 2, 0);
 
    printf("Received message: %s\n", message.msg_text);
 
    return 0;
}
