#include "custom.h"
void merging(stud_info* arr, int left, int mid, int right) {
	int i,j,k=0;
	stud_info aux[30];
	for(i=left,j=mid+1;i<=mid && j<=right;k++) {
		if(arr[i].roll<arr[j].roll) aux[k]=arr[i++];
		else aux[k]=arr[j++];
	}
	for(;i<=mid;i++) aux[k++]=arr[i];
	for(;j<=right;j++) aux[k++]=arr[j];
	for(i=0;i<k;i++) arr[left++]=aux[i];
}
void merge_sort(stud_info *stud_arr, int left, int right) {
    if (left<right) {
		int mid=left+(right-left)/2;
        merge_sort(stud_arr,left,mid);
        merge_sort(stud_arr,mid+1,right);
        merging(stud_arr,left,mid,right);
    }
}
void main() {
    int i,msgid=msgget((key_t)1234,0666);
	stud_info s;
	s.type=1;
	msgrcv(msgid,&s,sizeof(s),1,0);
	int n=s.roll;
	stud_info* stud_arr=(stud_info*)malloc((n+1)*sizeof(stud_info));
	for(int i=1;i<=n;i++) msgrcv(msgid,&stud_arr[i],sizeof(stud_arr[i]),1,0);
	printf("PROCESS-3: The data received from the message queue is as follows: \n");
	for(i=1;i<=n;i++) printf("Student: %s -> Roll: %d\n",stud_arr[i].name,stud_arr[i].roll);
	merge_sort(stud_arr,1,n);
	printf("PROCESS-3: Data after sorting the student records according to roll number: \n");
	for(i=1;i<=n;i++) printf("Student: %s -> Roll: %d\n",stud_arr[i].name,stud_arr[i].roll);
	shmctl(1234,IPC_RMID,NULL);
}
