// All necessary header files and structure definitionshave been included here
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/shm.h>
#define MAX 50
typedef struct {
	long type;
	char name[MAX];
	int roll;
} stud_info;