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
	printf("Enter the number of students: ");
	scanf("%d",&n);
	stud_info* stud_arr=(stud_info*)malloc(n*sizeof(stud_info));
	for(i=0;i<n;i++) {
		scanf("%d %[^\n]s",&stud_arr[i].roll,stud_arr[i].name);
		printf("\nData added...Student: %s -> Roll: %d\n",stud_arr[i].name,stud_arr[i].roll);
	}
	printf("The data is as follows: ");
	for(i=0;i<n;i++) printf("\nData added...Student: %s -> Roll: %d",stud_arr[i].name,stud_arr[i].roll);	
}
