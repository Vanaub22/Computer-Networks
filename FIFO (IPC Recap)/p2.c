// AIM: Process-1 will send n integers to Process-2, which will sort the integers and send back to Process-1. Process-1 will display the result.
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#define MYFIFO "/tmp/FIFO"
void merging(int*a, int left, int mid, int right) {
	int i,j,aux[30],k=0;
	for(i=left,j=mid+1;i<=mid && j<=right;k++) {
		if(a[i]>a[j]) aux[k]=a[i++];
		else aux[k]=a[j++];
	}
	for(;i<=mid;i++) aux[k++]=a[i];
	for(;j<=right;j++) aux[k++]=a[j];
	for(i=0;i<k;i++) a[left++]=aux[i];
}
void merge_sort(int *a, int left, int right) {
	int mid;
	if(left!=right) {
		mid=(left+right)/2;
		merge_sort(a,left,mid);
		merge_sort(a,mid+1,right);
		merging(a,left,mid,right);
	}
}
void main() {
	int i,n,x[20],fd=open(MYFIFO,O_RDONLY);
	n=read(fd,x,sizeof(x));
	close(fd);
	n/=sizeof(int);
	merge_sort(x,0,n-1);
	fd=open(MYFIFO,O_WRONLY);
	write(fd,x,sizeof(int)*(n));
	close(fd);
	printf("This is Process-2: I have performed my tasks...\n");
}