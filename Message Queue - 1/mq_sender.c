// AIM: To accept a decimal number from the user, convert it to 3 different bases (2, 8 and 16) and send them to the message queue
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#define MAX_DIGITS 50
// Structure for message
typedef struct {
    long type;
    char mssg[MAX_DIGITS];
} my_msg;
// Helper fn. to simply reverse a string
void reverse(char* arr) {
    int i,n=strlen(arr);
    for(int i=0;i<n/2;i++) {
        char tmp=arr[i];
        arr[i]=arr[n-i-1];
        arr[n-i-1]=tmp;
    }
}
// Helper fn. to convert decimal no. to binary string
void decimalToBinary(int x, char* bin) {
    int i=0;
    while(x>0) {
        bin[i]=(x%2)+'0';
        x/=2;
        i++;
    }
    bin[i]='\0';
    reverse(bin);
}
// Helper fn. to convert decimal no. to octal string
void decimalToOctal(int x, char* oct) {
    int i=0;
    while(x>0) {
        oct[i]=(x%8)+'0';
        x/=8;
        i++;
    }
    oct[i]='\0';
    reverse(oct);
}
// Helper fn. to convert decimal no. to hexadecimal string
void decimalToHexadecimal(int x, char* hex) {
    int i=0;
    while(x>0) {
        hex[i]=x%16<10?x%16+'0':(x%16)-10+'A';
        x/=16;
        i++;
    }
    hex[i]='\0';
    reverse(hex);
}
void main() {
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    char hex[MAX_DIGITS],oct[MAX_DIGITS],bin[MAX_DIGITS];
    printf("The user-input number is %d\n",n);
    decimalToBinary(n,bin);
    decimalToOctal(n,oct);
    decimalToHexadecimal(n,hex);
    printf("Converting to binary, we get: %s\n",bin);
    printf("Converting to octal, we get: %s\n",oct);
    printf("Converting to hexadecimal, we get: %s\n",hex);
    int msgid=msgget((key_t)1234,0666|IPC_CREAT);
    if(msgid==-1) {
        printf("Message queue could not be created.");
        exit(0);
    }
    my_msg bin_msg,oct_msg,hex_msg;
    // Assigning types for identification
    bin_msg.type=1;
    oct_msg.type=2;
    hex_msg.type=3;
    strcpy(bin_msg.mssg,bin);
    strcpy(oct_msg.mssg,oct);
    strcpy(hex_msg.mssg,hex);
    msgsnd(msgid,&bin_msg,sizeof(bin_msg),0);
    msgsnd(msgid,&oct_msg,sizeof(oct_msg),0);
    msgsnd(msgid,&hex_msg,sizeof(hex_msg),0);
    printf("\nALL DATA SENT...\n");
}
