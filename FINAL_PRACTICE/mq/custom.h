#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<string.h>
typedef struct {
	long type;
	char mssg[20];
}my_msg;
