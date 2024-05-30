#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<stdbool.h>
#include<pthread.h>

#define MAX 30
#define ip "224.0.0.1"
#define PORT 8080

char s[MAX];
int sockfd;
bool flag=false;
struct sockaddr_in maddr;

void* receiver(void* args) {
	while(true) {
		recvfrom(sockfd,s,sizeof(s),0,NULL,NULL);
		if(!flag) printf("Received Message: %s\n",s);
		flag=false;
	}
	pthread_exit(NULL);
}

void* sender(void* args) {
	while(true) {
		scanf(" %[^\n]s",s);
		flag=true;
		sendto(sockfd,s,sizeof(s),0,(struct sockaddr*)&maddr,sizeof(struct sockaddr_in));
	}
	pthread_exit(NULL);
}

void main() {
	printf("Welcome to the Group Chat...\n");
	int reuse=1;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	maddr.sin_port=htons(PORT);
	maddr.sin_addr.s_addr=inet_addr(ip);
	maddr.sin_family=AF_INET;
	struct ip_mreq req;
	req.imr_multiaddr.s_addr=inet_addr(ip);
	req.imr_interface.s_addr=INADDR_ANY;
	setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&req,sizeof(struct ip_mreq));
	bind(sockfd,(struct sockaddr*)&maddr,sizeof(struct sockaddr_in));
	pthread_t t1,t2;
	pthread_create(&t1,NULL,&sender,NULL);
	pthread_create(&t2,NULL,&receiver,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}
