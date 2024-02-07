#include "custom.h"
// Merge Sort Logic for sorting the student records in ascending order of roll numbers
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
    if(left<right) {
		int mid=left+(right-left)/2;
        merge_sort(stud_arr,left,mid);
        merge_sort(stud_arr,mid+1,right);
        merging(stud_arr,left,mid,right);
    }
}
void main() {
    int i,msgid=msgget((key_t)1234,0666);
	stud_info s;
	msgrcv(msgid,&s,sizeof(s),3,0);
	int n=s.roll;
	stud_info* stud_arr=(stud_info*)malloc((n+1)*sizeof(stud_info));
	stud_arr[0]=s;
	for(int i=1;i<=n;i++) msgrcv(msgid,&stud_arr[i],sizeof(stud_arr[i]),3,0);
	printf("PROCESS-3: The data received from Process-2 (Sorted in lexicographical order of names) is as follows: \n");
	for(i=1;i<=n;i++) printf("Student: %s | Roll: %d\n",stud_arr[i].name,stud_arr[i].roll);
	merge_sort(stud_arr,1,n);
	printf("Student records have been sorted in ascending order of roll numbers\n");
	for(i=0;i<=n;i++) {
		stud_arr[i].type=1; // Meant for Process-1
		msgsnd(msgid,&stud_arr[i],sizeof(stud_arr[i]),0);
	}
	printf("PROCESS-3: All the data has been sent to the message queue from Process-3...\n");
}
