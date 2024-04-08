#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX 100
#define PORT_NO 8081
#define ip "224.0.0.1"

int sockfd,reuse=1;
struct sockaddr_in multicast;
bool flag=false;
char buff[MAX];

void *receive(void *args) {
	while(true) {
		recvfrom(sockfd,buff,MAX,0,NULL,NULL);
		if(!flag) printf("Received : %s\n",buff);
		flag=false;
	}
	pthread_exit(NULL);
}

void *sender(void *args) {
	while(true) {
		scanf("%[^\n]",buff);
		getchar();
		flag=true;
		sendto(sockfd,input,strlen(input)+1,0,(struct sockaddr*)&multicast,sizeof(multicast));
	}
	pthread_exit(NULL);
}

void main() {
	struct ip_mreq req;
	pthread_t rthread,sthread;
	printf("Enter any messages:\n");
	multicast.sin_family=AF_INET;
	multicast.sin_addr.s_addr=inet_addr(ip);
	multicast.sin_port=htons(PORT_NO);
	multilen=sizeof(multicast);
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	bind(sockfd,(struct sockaddr*)&multicast,multilen);
	req.imr_multiaddr.s_addr=inet_addr(ip);
	req.imr_interface.s_addr=INADDR_ANY;
	setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&req,sizeof(req));
	pthread_create(&rthread,NULL,(void*)&receive,NULL);
	pthread_create(&sthread,NULL,(void*)&sender,NULL);
	pthread_join(sthread,NULL);
	pthread_join(rthread,NULL);
}
