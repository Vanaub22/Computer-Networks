#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define TIMEOUT 5
typedef struct {
	unsigned int seq_num;
	char data[256];
}Frame;

void main(int argc,char ** argv){
	if(argc<3){
		printf("Provide IP and PORT \n");
		exit(1);
	}
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in server,client;
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));
	int reuse=1;
	int res=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	
	struct timeval tv={
		.tv_sec=TIMEOUT,
		.tv_usec=0,
	};
	
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	
	listen(sockfd,1);
	socklen_t len=sizeof(client);
	int newfd=accept(sockfd,(struct sockaddr*)&client,&len);
	setsockopt(newfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
	printf("Accepted...\n");
	fflush(stdout);
	Frame f;
	char * data="Hello this is some data.";
	int seq_no=0,ack_no=0;
	int i=0;
	while(i<5){
		f.seq_num=seq_no;
		strcpy(f.data,data);
		printf("\nSending frame no %d\n",seq_no);
		fflush(stdout);
		send(newfd,&f,sizeof(f),0);
		setsockopt(newfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
		time_t t1=time(NULL);

		while(1){
			time_t cur;
			
			int bytesRead=recv(newfd,&ack_no,sizeof(int),0);
			time_t t2=time(NULL);
			if(bytesRead>0){
				if(ack_no==seq_no+1){
					printf("Acknowledgement for frame %d received\n",seq_no);
					seq_no++;i++;
					seq_no%=2;
					break;
				}else{
					time_t left=t1+TIMEOUT-t2;
					if(left>0){
						printf("Previous ack for %d received ignoring...\n",ack_no-1);
						struct timeval time_left={
							.tv_sec=left,
							.tv_usec=0,
						};
						setsockopt(newfd,SOL_SOCKET,SO_RCVTIMEO,&time_left,sizeof(struct timeval));
					}
					else{
						printf("Acknowledgement for frame %d not received.. Retransmitting...\n",seq_no);
						break;
					}
				}
			}else{
				printf("Acknowledgement for frame %d not received.. Retransmitting...\n",seq_no);
				break;
			}
			
		}
		printf("\n");
		fflush(stdout);
	}
}
