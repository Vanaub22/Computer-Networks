// AIM: To receive the binary, octal and hexadecimal representations of numbers sent via message queue and display them
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX_DIGITS 100
typedef struct {
    long type;
    char mssg[MAX_DIGITS];
} my_msg;
int main() {
    int msgid=msgget((key_t)1234,0666);
    if(msgid==-1) {
        printf("Message queue could not be created.");
        exit(0);
    }
    my_msg bin_msg,oct_msg,hex_msg;
    bin_msg.type=1;
    oct_msg.type=2;
    hex_msg.type=3;
    printf("THIS IS THE RECEIVER SIDE:\n");
    msgrcv(msgid,&bin_msg,sizeof(bin_msg),1,0);
    printf("Binary representation: %s\n",bin_msg.mssg);
    msgrcv(msgid,&oct_msg,sizeof(oct_msg),2,0);
    printf("Octal representation: %s\n",oct_msg.mssg);
    msgrcv(msgid,&hex_msg,sizeof(hex_msg),3,0);
    printf("Hexadecimal representation: %s\n", hex_msg.mssg);
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}
