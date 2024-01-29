#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#define MAX 50
typedef struct {
	long type;
	char name[MAX];
	int roll;
} stud_info;
void main() {
    int msgid=msgget((key_t)1234,0666);
    
}