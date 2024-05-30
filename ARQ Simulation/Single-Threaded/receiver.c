#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
typedef struct {
	unsigned int seq_num;
	char data[256];
}Frame;

void main(int argc,char** argv){
	srand(time(NULL));
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in server;
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi(argv[1]));
	
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	
	int seq_num=0,ack_num=0;
	Frame f;
	int i=0;
	while(i<5){
		recv(sockfd,&f,sizeof(f),0);
		if(f.seq_num==seq_num){
			printf("\nFrame %d received..\n",seq_num);
			int delay=rand()%7+1;
			printf("will send ack after %d seconds\n",delay);
			sleep(delay);
			ack_num=f.seq_num+1;
			send(sockfd,&ack_num,sizeof(int),0);
			seq_num++;
			seq_num%=2;
			i++;
		}else{
			printf("Duplicate frame %d received..\n",f.seq_num);
			ack_num=f.seq_num+1;
			send(sockfd,&ack_num,sizeof(int),0);
		}
	}
}
