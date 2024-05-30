#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#include<stdbool.h>

#define MAX 50
#define ip "127.0.0.1"
#define PORT 8080

void* tcp_thread(void* args) {
	int client_fd=*((int*)args);
	char s[MAX];
	read(client_fd,s,sizeof(s));
	printf("Message received from client-%d: %s\n",client_fd,s);
	bzero(s,sizeof(s));
	strcpy(s,"Client Acknowledged...");
	write(client_fd,s,sizeof(s));
	// close(client_fd);
}

void main() {
	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(ip);
	server_addr.sin_port=htons(PORT);
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
	listen(sockfd,1);
	while(true) {
		int client_fd=accept(sockfd,NULL,NULL);
		if(client_fd>=0) printf("Client Accepted...\n");
		pthread_t t;
		pthread_create(&t,NULL,&tcp_thread,(void*)&client_fd);
	}
	close(sockfd);
}
