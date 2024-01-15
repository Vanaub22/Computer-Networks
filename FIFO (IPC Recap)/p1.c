// AIM: Process-1 will send n integers to Process-2, which will sort the integers and send back to Process-1. Process-1 will display the result.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define MYFIFO "/tmp/FIFO"
void main() {
	mkfifo(MYFIFO,0666);
	int fd,i,n,*x;
	printf("This is Process-1:\nEnter the value of n: ");
	scanf("%d",&n);	
	x=(int*)malloc(sizeof(int)*n);
	printf("Enter the n numbers separated by spaces: ");
	for(i=0;i<n;i++) scanf("%d",&x[i]);
	fd=open(MYFIFO,O_WRONLY);
	write(fd,x,sizeof(int)*(n));
	close(fd);
	fd=open(MYFIFO,O_RDONLY);
	read(fd,x,sizeof(int)*(n));
	close(fd);
	printf("The received array is as follows: ");
	for(i=0;i<n;i++) printf("%d ",x[i]);
	printf("\n");
} // end of main
