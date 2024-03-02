#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>
#include<sys/msg.h>
#define MAX_DIGITS 20
typedef struct {
	long type;
	char mssg[MAX_DIGITS];
} my_msg;
