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
	int i,n;
	printf("THIS IS PROCESS-1:\nEnter the number of students: ");
	scanf("%d",&n);
	stud_info* stud_arr=(stud_info*)malloc(n*sizeof(stud_info));
	for(i=0;i<n;i++) scanf("%d %[^\n]s",&stud_arr[i].roll,stud_arr[i].name);
	printf("The data is as follows: \n");
	for(i=0;i<n;i++) printf("Student: %s -> Roll: %d\n",stud_arr[i].name,stud_arr[i].roll);
	int msgid=msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid==-1) {
		printf("The message queue could not be created.\n");
		exit(0);
	}
	for(i=0;i<n;i++) {
		stud_arr[i].type=1;
		msgsnd(msgid,&stud_arr[i],sizeof(stud_arr[i]),0);
	}
	printf("ALL DATA SENT...");
}
