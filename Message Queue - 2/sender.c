#include "custom.h"
void main() {
	int i,n;
	printf("PROCESS-1: Enter the number of students: ");
	scanf("%d",&n);
	stud_info* stud_arr=(stud_info*)malloc((n+1)*sizeof(stud_info));
	stud_arr[0].roll=n;
	strcpy(stud_arr[0].name,"Size");
	printf("Enter the Roll numbers and corresponding names of the students separated by spaces:\n");
	for(i=1;i<=n;i++) scanf("%d %[^\n]s",&stud_arr[i].roll,stud_arr[i].name);
	printf("PROCESS-1: The user-input data is as follows: \n");
	for(i=1;i<=n;i++) printf("Student: %s -> Roll: %d\n",stud_arr[i].name,stud_arr[i].roll);
	int msgid=msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid==-1) {
		printf("PROCESS-1: The message queue could not be created.\n");
		exit(0);
	}
	for(i=0;i<=n;i++) {
	 	stud_arr[i].type=1;
	 	msgsnd(msgid,&stud_arr[i],sizeof(stud_arr[i]),0);
	}
	printf("PROCESS 1: All the data has been sent to the message queue from the Sender (Process-1)\n");
}
